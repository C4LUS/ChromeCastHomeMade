set(SOURCES main.cpp)
add_executable(cchm_gui ${SOURCES} ${HEADER_FILES})
target_include_directories(cchm_gui PRIVATE ../core)
target_link_libraries(cchm_gui cchm_core)
