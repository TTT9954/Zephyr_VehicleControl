#include "ring_buffer.h"
void ring_buffer_push(speed_ring_t *r, uint16_t value)
{
    if (!r) return;
    r->items[r->head] = value;
    r->head = (uint8_t)((r->head + 1U) % RING_CAPACITY);
    if (r->count < RING_CAPACITY) r->count++;
}
bool ring_buffer_latest(const speed_ring_t *r, uint16_t *out)
{
    if (!r || !out || r->count == 0U) return false;
    *out = r->items[(r->head + RING_CAPACITY - 1U) % RING_CAPACITY];
    return true;
}
