#ifndef INCLUDE_GLOBAL_DESCRIPTOR_TABLE_H
#define INCLUDE_GLOBAL_DESCRIPTOR_TABLE_H

#include "types.h"

const uint16_t NULL_SEGMENT_SELECTOR;
const uint16_t KERNEL_CODE_SEGMENT_SELECTOR;
const uint16_t KERNEL_DATA_SEGMENT_SELECTOR;

void initialize_gdt();

#endif
