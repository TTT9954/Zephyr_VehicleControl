#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H
#include "app_types.h"
void can_manager_publish(vehicle_status_t status);
void can_manager_process(void);
#endif
