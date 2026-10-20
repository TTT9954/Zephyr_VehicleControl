#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H
#include <stdbool.h>
#include <stdint.h>
void fault_manager_update(bool have_sample, uint32_t sample_age_ms, uint16_t speed_kph);
bool fault_manager_active(void);
#endif
