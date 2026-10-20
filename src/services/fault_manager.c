#include "fault_manager.h"
#include "app_config.h"
#include <zephyr/kernel.h>
static atomic_t fault_flag;
void fault_manager_update(bool have_sample, uint32_t age, uint16_t speed)
{
    bool fault = !have_sample || age > SENSOR_TIMEOUT_MS || speed > 250U;
    atomic_set(&fault_flag, fault ? 1 : 0);
}
bool fault_manager_active(void)
{
    return atomic_get(&fault_flag) != 0;
}
