#include "page_table.h"
#include "loader.h"

enum page_size_t {FOUR_KB, FOUR_MB};
enum page_privilege_t {SUPERVISOR, USER};
enum page_permissions_t {READ_ONLY, READ_WRITE};

struct page_directory_entry_t {
  uint32_t page_table_address;
} __attribute__((packed));

uint32_t make_page_directory_entry(
    uint32_t page_table_address,
    enum page_size_t page_size,
    bool cache_disabled,
    bool write_through,
    enum page_privilege_t privilege,
    enum page_permissions_t permissions,
    bool present
    )
{
  uint32_t entry = page_table_address;
  entry |= page_size << 7;
  entry |= cache_disabled << 4;
  entry |= write_through << 3;
  entry |= privilege << 2;
  entry |= permissions << 1;
  entry |= present;

  return entry;
}

uint32_t make_page_table_entry(
    uint32_t page_fram_address,
    bool global,
    bool cache_disabled,
    bool write_through,
    enum page_privilege_t privilege,
    enum page_permissions_t permissions,
    bool present
    )
{
  uint32_t entry = page_fram_address;
  entry |= global << 8;
  entry |= cache_disabled << 6;
  entry |= write_through << 3;
  entry |= privilege << 2;
  entry |= permissions << 1;
  entry |= present;

  return entry;
}

page_directory_t initialize_page_directory()
{
  page_directory_t pd = (page_directory_t) &boot_pagedir;
  page_table_t pt = (page_table_t) &boot_pagetab1;
  *pd = make_page_directory_entry(
      (uint32_t) pt,
      FOUR_KB,
      false,
      false,
      SUPERVISOR,
      READ_WRITE,
      true
      );
  for (int i = 0; i < 1024; i++) {
    pt[i] = make_page_table_entry(
        4096*i,
        false,
        false,
        false,
        SUPERVISOR,
        READ_WRITE,
        true
        );
  }
  return pd;
}
