#ifndef SPEED_MONITOR_H
#define SPEED_MONITOR_H
#include <stdbool.h>
#include <stdint.h>
bool speed_monitor_update(bool was_limited, uint16_t speed_kph, uint16_t limit_kph, uint16_t hysteresis_kph);
#endif
