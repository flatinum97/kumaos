#ifndef INCLUDE_PAGE_TABLE_H
#define INCLUDE_PAGE_TABLE_H

#include "types.h"

typedef uint32_t * page_directory_t;
typedef uint32_t * page_table_t;

page_directory_t initialize_page_directory();

#endif
