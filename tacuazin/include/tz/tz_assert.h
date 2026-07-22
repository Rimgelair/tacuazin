#pragma once

#include <stdlib.h>

#define TZ_ASSERT(Condition) do { if(!(Condition)) { abort();  } } while (0)
