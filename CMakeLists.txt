cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(gb-emulator)

add_executable(gb-emulator 
  src/main.c 
  src/bus.c 
  src/cpu.c 
  src/ops/ld.c 
  src/ops/alu.c
  src/ops/bit.c
  src/tests/ld_test.c
)
