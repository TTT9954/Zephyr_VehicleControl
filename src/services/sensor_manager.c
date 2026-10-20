#include "sensor_manager.h"
#include "adc_sensor.h"
#include "gpio_control.h"
#include "data_filter.h"
#include <zephyr/kernel.h>
static struct k_mutex sample_lock;
static sensor_sample_t sample;
static bool sample_valid;
void sensor_manager_init(void)
{
    k_mutex_init(&sample_lock);
    sample_valid = false;
}
void sensor_manager_poll(void)
{
    uint16_t raw = adc_sensor_read_speed_kph();
    k_mutex_lock(&sample_lock, K_FOREVER);
    sample.speed_kph = sample_valid ? data_filter_iir_u16(sample.speed_kph, raw) : raw;
    sample.ignition = gpio_control_ignition_on();
    sample.ready = gpio_control_vehicle_ready();
    sample.timestamp_ms = k_uptime_get_32();
    sample_valid = true;
    k_mutex_unlock(&sample_lock);
}
bool sensor_manager_get_latest(sensor_sample_t *out)
{
    if (!out) return false;
    k_mutex_lock(&sample_lock, K_FOREVER);
    bool valid = sample_valid;
    if (valid) *out = sample;
    k_mutex_unlock(&sample_lock);
    return valid;
}
