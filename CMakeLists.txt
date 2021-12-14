project(graham_scan)
cmake_minimum_required(VERSION 3.17)

include_directories(src)

set(SOURCES src/main.cc src/point.cc src/heapsort.cc src/qsort.cc)

add_executable(graham_scan ${SOURCES})
