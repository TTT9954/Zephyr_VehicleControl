#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "app_config.h"
#include "app_types.h"
#include "sensor_manager.h"
#include "vehicle_control.h"
#include "fault_manager.h"
#include "can_manager.h"
LOG_MODULE_REGISTER(vehicle_main, LOG_LEVEL_INF);
K_SEM_DEFINE(start_sem, 0, 3);
static void sensor_thread(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    k_sem_take(&start_sem, K_FOREVER);
    while (1) { sensor_manager_poll(); k_msleep(SENSOR_PERIOD_MS); }
}
static void control_thread(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    k_sem_take(&start_sem, K_FOREVER);
    vehicle_status_t status = {.state = VEH_OFF};
    while (1) {
        sensor_sample_t sample = {0};
        if (sensor_manager_get_latest(&sample)) {
            uint32_t age = k_uptime_get_32() - sample.timestamp_ms;
            bool fault = fault_manager_active() || age > SENSOR_TIMEOUT_MS;
            status = vehicle_control_step(status, sample, fault);
            can_manager_publish(status);
        }
        k_msleep(CONTROL_PERIOD_MS);
    }
}
static void fault_thread(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    k_sem_take(&start_sem, K_FOREVER);
    while (1) {
        sensor_sample_t sample = {0};
        bool valid = sensor_manager_get_latest(&sample);
        uint32_t age = valid ? k_uptime_get_32() - sample.timestamp_ms : UINT32_MAX;
        fault_manager_update(valid, age, sample.speed_kph);
        k_msleep(FAULT_PERIOD_MS);
    }
}
static void can_thread(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    while (1) can_manager_process();
}
K_THREAD_DEFINE(sensor_tid, 1024, sensor_thread, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(control_tid, 1024, control_thread, NULL, NULL, NULL, 4, 0, 0);
K_THREAD_DEFINE(fault_tid, 1024, fault_thread, NULL, NULL, NULL, 6, 0, 0);
K_THREAD_DEFINE(can_tid, 1024, can_thread, NULL, NULL, NULL, 7, 0, 0);
int main(void)
{
    sensor_manager_init();
    LOG_INF("Zephyr Vehicle Control demo starting");
    k_sem_give(&start_sem); k_sem_give(&start_sem); k_sem_give(&start_sem);
    return 0;
}
