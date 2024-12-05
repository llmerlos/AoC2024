cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AoC2024 CXX)

foreach(DAY RANGE 1 5)
    foreach(PART a b)
        add_executable(d${DAY}${PART} src/${DAY}${PART}.cpp)
    endforeach()
endforeach()