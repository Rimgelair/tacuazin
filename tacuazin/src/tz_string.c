#include "tz/tz_string.h"

#include <string.h>

TzString tz_string_from_cstring(char *cstring){
  return (TzString){
  .buffer = cstring,
  .length = strlen(cstring),
};
}
