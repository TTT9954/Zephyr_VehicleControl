#include "vehicle_control.h"
#include "vehicle_state.h"
#include "speed_monitor.h"
#include "app_config.h"
vehicle_status_t vehicle_control_step(vehicle_status_t prev, sensor_sample_t input, bool fault)
{
    vehicle_status_t out = prev;
    out.state = vehicle_state_next(prev.state, input.ignition, input.ready, fault);
    out.speed_kph = input.speed_kph;
    out.fault_active = fault;
    out.speed_limited = (out.state == VEH_DRIVE) &&
        speed_monitor_update(prev.speed_limited, input.speed_kph,
                             SPEED_LIMIT_KPH, SPEED_HYSTERESIS_KPH);
    out.uptime_ms = input.timestamp_ms;
    return out;
}
