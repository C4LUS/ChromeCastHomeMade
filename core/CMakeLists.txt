find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)
set(SOURCES greet.c)
add_library(cchm_core ${SOURCES} ${HEADER_FILES})
target_link_libraries(cchm_core
    PkgConfig::LIBAV
)
