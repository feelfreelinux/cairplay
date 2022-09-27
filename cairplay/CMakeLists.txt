cmake_minimum_required(VERSION 3.5)

project(cairplay)

# Configurable options
set(CAIRPLAY_EXTERNAL_BELL "" CACHE STRING "External bell library target name, optional")

# CMake options
set(CMAKE_CXX_STANDARD 17)

# Main library sources
file(GLOB SOURCES "src/*.cpp" "src/*.c")

# Use externally specified bell library or the submodule
if(CSPOT_EXTERNAL_BELL)
    list(APPEND EXTRA_LIBS ${CSPOT_EXTERNAL_BELL})
else()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bell)
    list(APPEND EXTRA_LIBS bell)
endif()

add_library(cairplay STATIC ${SOURCES})
# PUBLIC to propagate includes from bell to cairplay dependents
target_link_libraries(cairplay PUBLIC ${EXTRA_LIBS})
target_include_directories(cairplay PUBLIC "include" ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(cairplay PRIVATE -Wno-missing-field-initializers)
