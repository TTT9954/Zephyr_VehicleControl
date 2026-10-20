#include "speed_monitor.h"
bool speed_monitor_update(bool was_limited, uint16_t speed, uint16_t limit, uint16_t hysteresis)
{
    if (!was_limited) return speed >= limit;
    uint16_t release = (limit > hysteresis) ? (uint16_t)(limit - hysteresis) : 0U;
    return speed > release;
}
