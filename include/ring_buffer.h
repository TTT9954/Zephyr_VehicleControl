#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stdbool.h>
#include <stdint.h>
#define RING_CAPACITY 16U
typedef struct { uint16_t items[RING_CAPACITY]; uint8_t head; uint8_t count; } speed_ring_t;
void ring_buffer_push(speed_ring_t *r, uint16_t value);
bool ring_buffer_latest(const speed_ring_t *r, uint16_t *out);
#endif
