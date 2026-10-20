#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H
#include "app_types.h"
#include <stdbool.h>
void sensor_manager_init(void);
void sensor_manager_poll(void);
bool sensor_manager_get_latest(sensor_sample_t *out);
#endif
