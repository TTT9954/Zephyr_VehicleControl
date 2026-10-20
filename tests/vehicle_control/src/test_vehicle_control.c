#include <zephyr/ztest.h>
#include "vehicle_control.h"
#include "vehicle_state.h"
#include "speed_monitor.h"
ZTEST(vehicle_logic, test_state_transitions)
{
    zassert_equal(vehicle_state_next(VEH_OFF, true, false, false), VEH_PRE_DRIVE);
    zassert_equal(vehicle_state_next(VEH_PRE_DRIVE, true, true, false), VEH_DRIVE);
    zassert_equal(vehicle_state_next(VEH_DRIVE, true, true, true), VEH_POST_DRIVE);
    zassert_equal(vehicle_state_next(VEH_POST_DRIVE, false, false, false), VEH_OFF);
}
ZTEST(vehicle_logic, test_speed_hysteresis)
{
    zassert_false(speed_monitor_update(false, 89, 90, 3));
    zassert_true(speed_monitor_update(false, 90, 90, 3));
    zassert_true(speed_monitor_update(true, 88, 90, 3));
    zassert_false(speed_monitor_update(true, 87, 90, 3));
}
ZTEST(vehicle_logic, test_control)
{
    vehicle_status_t previous = {.state = VEH_PRE_DRIVE};
    sensor_sample_t input = {.speed_kph = 100, .ignition = true, .ready = true, .timestamp_ms = 123};
    vehicle_status_t output = vehicle_control_step(previous, input, false);
    zassert_equal(output.state, VEH_DRIVE);
    zassert_true(output.speed_limited);
    zassert_false(output.fault_active);
}
ZTEST_SUITE(vehicle_logic, NULL, NULL, NULL, NULL, NULL);
