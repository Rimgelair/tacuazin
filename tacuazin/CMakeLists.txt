add_library(tacuazin_internal STATIC src/tz_app.c src/tz_string.c src/tz_stack_allocator.c)

add_library(Tacuazin::tacuazin ALIAS tacuazin_internal)

target_include_directories(tacuazin_internal 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(APPLE)
    target_sources(tacuazin_internal PRIVATE src/tz_window_cocoa.m)
    target_compile_definitions(tacuazin_internal PRIVATE TZ_OSX)
elseif(WIN32)
    target_sources(tacuazin_internal PRIVATE src/tz_window_win32.c src/tz_memory_win32.c)
    target_compile_definitions(tacuazin_internal PRIVATE 
      TZ_WIN32
      WIN32_LEAN_AND_MEAN
      NOMINMAX
    )
    target_link_libraries(tacuazin_internal PRIVATE 
      user32
      gdi32
    )
endif()
