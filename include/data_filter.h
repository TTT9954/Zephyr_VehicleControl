#ifndef DATA_FILTER_H
#define DATA_FILTER_H
#include <stdint.h>
uint16_t data_filter_iir_u16(uint16_t previous, uint16_t sample);
#endif
