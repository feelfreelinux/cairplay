
cmake_minimum_required(VERSION 3.5)

# Configurable options
option(CAIRPLAY_TARGET_CLI "Enable ctube-cli target" OFF)
option(CAIRPLAY_TARGET_ESP32 "Enable ctube-esp32 target" OFF)

# Enable cairplay-cli target
if(CAIRPLAY_TARGET_CLI)
    add_subdirectory(targets/cli)
    project(cairplay-cli)
endif()

# Enable cairplay-esp32 target
if(CAIRPLAY_TARGET_ESP32)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    set(IDF_NO_INCLUDE ON)
    add_subdirectory(targets/esp32)
    project(cairplay-esp32)
endif()