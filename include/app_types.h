#ifndef APP_TYPES_H
#define APP_TYPES_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { VEH_OFF=0, VEH_PRE_DRIVE, VEH_DRIVE, VEH_POST_DRIVE } vehicle_state_t;
typedef struct { uint16_t speed_kph; bool ready; bool ignition; uint32_t timestamp_ms; } sensor_sample_t;
typedef struct { vehicle_state_t state; bool speed_limited; bool fault_active; uint16_t speed_kph; uint32_t uptime_ms; } vehicle_status_t;
#endif
