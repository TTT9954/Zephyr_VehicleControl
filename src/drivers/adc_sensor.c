#include "adc_sensor.h"
#include <zephyr/kernel.h>
/* Hardware abstraction demo: triangular speed profile, 0..110 km/h.
 * Replace with ADC / CAN input acquisition for physical hardware. */
uint16_t adc_sensor_read_speed_kph(void)
{
    uint32_t phase = (uint32_t)(k_uptime_get() / 200U) % 220U;
    return (uint16_t)((phase <= 110U) ? phase : 220U - phase);
}
