#ifndef VEHICLE_CONTROL_H
#define VEHICLE_CONTROL_H
#include "app_types.h"
vehicle_status_t vehicle_control_step(vehicle_status_t previous, sensor_sample_t input, bool fault);
#endif
