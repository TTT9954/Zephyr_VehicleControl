#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H
#include "app_types.h"
vehicle_state_t vehicle_state_next(vehicle_state_t current, bool ignition, bool ready, bool fault);
const char *vehicle_state_name(vehicle_state_t state);
#endif
