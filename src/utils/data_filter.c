#include "data_filter.h"
/* Simple integer IIR: 75% previous, 25% new sample. */
uint16_t data_filter_iir_u16(uint16_t previous, uint16_t sample)
{
    return (uint16_t)(((uint32_t)previous * 3U + sample + 2U) / 4U);
}
