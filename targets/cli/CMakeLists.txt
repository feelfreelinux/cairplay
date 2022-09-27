cmake_minimum_required(VERSION 3.5)

project(cairplay-cli)

# Configurable options
option(USE_ALSA "Enable ALSA" OFF)
option(USE_PORTAUDIO "Enable PortAudio" OFF)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "CMake Build Type")

# CMake options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Main target sources
file(GLOB SOURCES "*.cpp")

if(USE_PORTAUDIO)
    add_definitions(-DCAIRPLAY_ENABLE_PORTAUDIO_SINK)
    set(BELL_SINK_PORTAUDIO ON)
endif(USE_PORTAUDIO)
unset(USE_PORTAUDIO CACHE)

if(USE_ALSA)
    add_definitions(-DCAIRPLAY_ENABLE_ALSA_SINK)
    set(BELL_SINK_ALSA ON)
endif(USE_ALSA)
unset(USE_ALSA CACHE)

# Import cairplay library
add_subdirectory("../../cairplay" ${CMAKE_CURRENT_BINARY_DIR}/cairplay)

# Configure the target
add_executable(cairplay-cli ${SOURCES})
target_link_libraries(cairplay-cli PUBLIC cairplay ${EXTRA_LIBS})
target_include_directories(cairplay-cli PRIVATE "." ${EXTRA_INCLUDES})
