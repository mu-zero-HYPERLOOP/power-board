######################################################################
# @author      : karl (karlsasssie@gmail.com)
# @file        : CMakeLists
# @created     : Friday Apr 07, 2023 15:39:05 CEST
######################################################################

cmake_minimum_required(VERSION 3.5)
project(power-board12 CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  mock/can.cpp
  mock/pdu.cpp
  mock/print.cpp
  src/canzero/canzero.cpp
  src/channel_control.cpp
  src/handle_heartbeat.cpp
  src/fsm/error_handling.cpp
  src/fsm/fsm.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/ mock/)

  

