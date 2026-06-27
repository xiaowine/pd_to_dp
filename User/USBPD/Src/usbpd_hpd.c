#include "usbpd_hpd.h"

#include "board_io.h"
#include "tim.h"

#define USBPD_HPD_IRQ_MIN_US       250u
#define USBPD_HPD_UNPLUG_MIN_US    2000u

static uint8_t s_enabled;
static uint8_t s_logical_high;
static uint8_t s_high_pending;
static uint16_t s_high_start_us;
static uint8_t s_low_pending;
static uint16_t s_low_start_us;
static uint8_t s_reported_valid;
static uint8_t s_reported_high;
static volatile uint8_t s_pending_high;
static volatile uint8_t s_pending_low;
static volatile uint8_t s_pending_irq_count;
static volatile uint16_t s_pending_irq_low_us[2];
static volatile uint16_t s_pending_low_us;
static uint8_t s_tx_pending_valid;
static USBPD_HPDEvent s_tx_pending_event;

static USBPD_HPDStatus USBPD_HPD_MakeStatus(uint8_t gpio_high, uint8_t irq_hpd, uint16_t low_us)
{
    return (USBPD_HPDStatus){
        .logical_high = s_logical_high ? 1u : 0u,
        .gpio_high = gpio_high ? 1u : 0u,
        .irq_hpd = irq_hpd ? 1u : 0u,
        .low_us = low_us,
    };
}

static USBPD_HPDStatus USBPD_HPD_MakeEventStatus(uint8_t logical_high, uint8_t gpio_high,
                                                 uint8_t irq_hpd, uint16_t low_us)
{
    return (USBPD_HPDStatus){
        .logical_high = logical_high ? 1u : 0u,
        .gpio_high = gpio_high ? 1u : 0u,
        .irq_hpd = irq_hpd ? 1u : 0u,
        .low_us = low_us,
    };
}

static void USBPD_HPD_ClearPendingEvents(void)
{
    s_pending_high = 0u;
    s_pending_low = 0u;
    s_pending_irq_count = 0u;
    s_pending_irq_low_us[0] = 0u;
    s_pending_irq_low_us[1] = 0u;
    s_pending_low_us = 0u;
    s_tx_pending_valid = 0u;
    s_tx_pending_event.type = USBPD_HPD_EVENT_NONE;
}

static void USBPD_HPD_ClearQueuedHighIrq(void)
{
    s_pending_high = 0u;
    s_pending_irq_count = 0u;
    s_pending_irq_low_us[0] = 0u;
    s_pending_irq_low_us[1] = 0u;
    s_high_pending = 0u;
}

static void USBPD_HPD_QueueIrq(uint16_t low_us)
{
    if (s_pending_irq_count >= 2u)
    {
        return;
    }

    s_pending_irq_low_us[s_pending_irq_count] = low_us;
    s_pending_irq_count++;
}

static void USBPD_HPD_CheckHighDebounce(void)
{
    if (!s_enabled || !s_high_pending)
    {
        return;
    }

    if (!DP_HPD_IsHigh())
    {
        s_high_pending = 0u;
        return;
    }

    if ((uint16_t)(USBPD_Tim_GetUs16() - s_high_start_us) >= USBPD_HPD_IRQ_MIN_US)
    {
        s_high_pending = 0u;
        s_logical_high = 1u;
        s_pending_high = 1u;
    }
}

static USBPD_HPDStatus USBPD_HPD_CheckLongLow(USBPD_HPDEventType* event_type)
{
    const uint8_t gpio_high = DP_HPD_IsHigh();
    const uint16_t now_us = USBPD_Tim_GetUs16();
    uint16_t low_us = 0u;

    *event_type = USBPD_HPD_EVENT_NONE;

    if (!s_enabled)
    {
        return USBPD_HPD_MakeStatus(gpio_high, 0u, 0u);
    }

    USBPD_HPD_CheckHighDebounce();

    if (gpio_high)
    {
        return USBPD_HPD_MakeStatus(gpio_high, 0u, 0u);
    }

    if (s_logical_high && s_low_pending)
    {
        low_us = (uint16_t)(now_us - s_low_start_us);
        if (low_us >= USBPD_HPD_UNPLUG_MIN_US)
        {
            s_low_pending = 0u;
            s_logical_high = 0u;
            USBPD_HPD_ClearQueuedHighIrq();
            *event_type = USBPD_HPD_EVENT_LOW;
        }
    }

    return USBPD_HPD_MakeStatus(gpio_high, 0u, low_us);
}

static uint8_t USBPD_HPD_PopPendingEvent(USBPD_HPDEvent* event)
{
    uint8_t event_found = 1u;
    const uint8_t gpio_high = DP_HPD_IsHigh();

    if (s_pending_low)
    {
        const uint16_t low_us = s_pending_low_us;

        event->type = USBPD_HPD_EVENT_LOW;
        event->status = USBPD_HPD_MakeEventStatus(0u, gpio_high, 0u, low_us);
        s_pending_low = 0u;
    }
    else if (s_pending_high)
    {
        event->type = USBPD_HPD_EVENT_HIGH;
        event->status = USBPD_HPD_MakeEventStatus(1u, gpio_high, 0u, 0u);
        s_pending_high = 0u;
    }
    else if (s_pending_irq_count)
    {
        const uint16_t low_us = s_pending_irq_low_us[0];

        event->type = USBPD_HPD_EVENT_IRQ;
        event->status = USBPD_HPD_MakeEventStatus(1u, gpio_high, 1u, low_us);
        s_pending_irq_low_us[0] = s_pending_irq_low_us[1];
        s_pending_irq_low_us[1] = 0u;
        s_pending_irq_count--;
    }
    else
    {
        event_found = 0u;
    }

    return event_found;
}

static uint8_t USBPD_HPD_PeekPendingEvent(USBPD_HPDEvent* event)
{
    uint8_t event_found = 1u;
    const uint8_t gpio_high = DP_HPD_IsHigh();

    if (s_pending_low)
    {
        event->type = USBPD_HPD_EVENT_LOW;
        event->status = USBPD_HPD_MakeEventStatus(0u, gpio_high, 0u, s_pending_low_us);
    }
    else if (s_pending_high)
    {
        event->type = USBPD_HPD_EVENT_HIGH;
        event->status = USBPD_HPD_MakeEventStatus(1u, gpio_high, 0u, 0u);
    }
    else if (s_pending_irq_count)
    {
        event->type = USBPD_HPD_EVENT_IRQ;
        event->status = USBPD_HPD_MakeEventStatus(1u, gpio_high, 1u, s_pending_irq_low_us[0]);
    }
    else
    {
        event_found = 0u;
    }

    return event_found;
}

void USBPD_HPD_Reset(void)
{
    DP_HPD_DisableInterrupt();
    s_enabled = 0u;
    s_logical_high = 0u;
    s_high_pending = 0u;
    s_high_start_us = 0u;
    s_low_pending = 0u;
    s_low_start_us = 0u;
    s_reported_valid = 0u;
    s_reported_high = 0u;
    USBPD_HPD_ClearPendingEvents();
}

void USBPD_HPD_EnterMode(void)
{
    DP_HPD_DisableInterrupt();
    s_enabled = 1u;
    s_logical_high = 0u;
    s_high_pending = DP_HPD_IsHigh() ? 1u : 0u;
    s_high_start_us = USBPD_Tim_GetUs16();
    s_low_pending = 0u;
    s_low_start_us = 0u;
    s_reported_valid = 0u;
    s_reported_high = 0u;
    USBPD_HPD_ClearPendingEvents();
    DP_HPD_EnableInterrupt();
}

void USBPD_HPD_Disable(void)
{
    USBPD_HPD_Reset();
}

uint8_t USBPD_HPD_IsEnabled(void)
{
    return s_enabled;
}

void USBPD_HPD_QueueHighIfAsserted(void)
{
    if (!s_enabled || !DP_HPD_IsHigh())
    {
        return;
    }

    s_high_pending = 1u;
    s_high_start_us = USBPD_Tim_GetUs16();
}

USBPD_HPDStatus USBPD_HPD_ReadStatus(void)
{
    USBPD_HPDEvent pending_event = {0};
    USBPD_HPDEventType long_low_event = USBPD_HPD_EVENT_NONE;
    const USBPD_HPDStatus current_status = USBPD_HPD_CheckLongLow(&long_low_event);

    if (long_low_event == USBPD_HPD_EVENT_LOW)
    {
        return current_status;
    }

    if (USBPD_HPD_PopPendingEvent(&pending_event))
    {
        return pending_event.status;
    }

    return current_status;
}

USBPD_HPDStatus USBPD_HPD_GetSnapshot(void)
{
    return USBPD_HPD_MakeStatus(DP_HPD_IsHigh(), 0u, 0u);
}

uint8_t USBPD_HPD_PollEvent(USBPD_HPDEvent* event)
{
    USBPD_HPDEventType long_low_event = USBPD_HPD_EVENT_NONE;

    event->type = USBPD_HPD_EVENT_NONE;
    event->status = USBPD_HPD_CheckLongLow(&long_low_event);
    if (long_low_event == USBPD_HPD_EVENT_LOW)
    {
        event->type = USBPD_HPD_EVENT_LOW;
        return 1u;
    }

    return USBPD_HPD_PopPendingEvent(event);
}

uint8_t USBPD_HPD_PeekEvent(USBPD_HPDEvent* event)
{
    USBPD_HPDEventType long_low_event = USBPD_HPD_EVENT_NONE;

    event->type = USBPD_HPD_EVENT_NONE;
    if (s_tx_pending_valid)
    {
        *event = s_tx_pending_event;
        return 1u;
    }

    event->status = USBPD_HPD_CheckLongLow(&long_low_event);
    if (long_low_event == USBPD_HPD_EVENT_LOW)
    {
        event->type = USBPD_HPD_EVENT_LOW;
        s_tx_pending_event = *event;
        s_tx_pending_valid = 1u;
        return 1u;
    }

    return USBPD_HPD_PeekPendingEvent(event);
}

void USBPD_HPD_CommitEvent(const USBPD_HPDEvent* event)
{
    if (event == NULL)
    {
        return;
    }

    if (s_tx_pending_valid && s_tx_pending_event.type == event->type)
    {
        s_tx_pending_valid = 0u;
        s_tx_pending_event.type = USBPD_HPD_EVENT_NONE;
        return;
    }

    switch (event->type)
    {
    case USBPD_HPD_EVENT_LOW:
        s_pending_low = 0u;
        s_pending_low_us = 0u;
        break;

    case USBPD_HPD_EVENT_HIGH:
        s_pending_high = 0u;
        break;

    case USBPD_HPD_EVENT_IRQ:
        if (s_pending_irq_count)
        {
            s_pending_irq_low_us[0] = s_pending_irq_low_us[1];
            s_pending_irq_low_us[1] = 0u;
            s_pending_irq_count--;
        }
        break;

    default:
        break;
    }
}

void USBPD_HPD_RecordReported(uint8_t logical_high)
{
    s_reported_valid = 1u;
    s_reported_high = logical_high ? 1u : 0u;
}

uint8_t USBPD_HPD_GetReportedValid(void)
{
    return s_reported_valid;
}

uint8_t USBPD_HPD_GetReportedHigh(void)
{
    return s_reported_high;
}

void DP_HPD_EdgeCallback(void)
{
    const uint8_t gpio_high = DP_HPD_IsHigh();
    const uint16_t now_us = USBPD_Tim_GetUs16();
    uint16_t low_us = 0u;

    if (!s_enabled)
    {
        return;
    }

    if (!gpio_high)
    {
        if (s_logical_high && !s_low_pending)
        {
            s_low_pending = 1u;
            s_low_start_us = now_us;
        }
        s_high_pending = 0u;
        return;
    }

    if (s_low_pending)
    {
        low_us = (uint16_t)(now_us - s_low_start_us);
        s_low_pending = 0u;

        if (low_us >= USBPD_HPD_IRQ_MIN_US && low_us < USBPD_HPD_UNPLUG_MIN_US)
        {
            s_logical_high = 1u;
            USBPD_HPD_QueueIrq(low_us);
            return;
        }

        if (low_us >= USBPD_HPD_UNPLUG_MIN_US)
        {
            s_logical_high = 0u;
            s_pending_low_us = low_us;
            USBPD_HPD_ClearQueuedHighIrq();
            s_pending_low = 1u;
        }
    }

    if (!s_logical_high)
    {
        s_high_pending = 1u;
        s_high_start_us = now_us;
    }
}
