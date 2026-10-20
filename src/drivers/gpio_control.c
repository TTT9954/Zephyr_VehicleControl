#include "gpio_control.h"
#include <zephyr/kernel.h>
/* Simulated ignition and ready input; no GPIO hardware required. */
bool gpio_control_ignition_on(void)
{
    return ((uint32_t)(k_uptime_get() / 1000U) % 60U) < 50U;
}
bool gpio_control_vehicle_ready(void)
{
    uint32_t t = (uint32_t)(k_uptime_get() / 1000U) % 60U;
    return t >= 2U && t < 48U;
}
