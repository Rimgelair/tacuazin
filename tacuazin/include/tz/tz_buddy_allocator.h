#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct TzBuddyBlock TzBuddyBlock;
struct TzBuddyBlock {
  size_t size;
  bool is_free;
};

typedef struct {
  TzBuddyBlock *head;
  TzBuddyBlock *tail;
  size_t alignment;
} TzBuddyAllocator;
