cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS
        ${CMAKE_SOURCE_DIR}/components/bus
        ${CMAKE_SOURCE_DIR}/components/drivers/bno055_driver
        ${CMAKE_SOURCE_DIR}/components/drivers/ssd1306_driver
        ${CMAKE_SOURCE_DIR}/components/drivers/common
        ${CMAKE_SOURCE_DIR}/components/drivers/common/buffers
        ${CMAKE_SOURCE_DIR}/components/drivers/common/states
        ${CMAKE_SOURCE_DIR}/components/drivers/interfaces
        ${CMAKE_SOURCE_DIR}/components/drivers/utilities
)
project(Lean)