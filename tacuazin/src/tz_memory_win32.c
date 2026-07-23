#include "tz/tz_memory.h"

#include <Windows.h>

size_t get_platform_page_size() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);

    return info.dwPageSize;
}
