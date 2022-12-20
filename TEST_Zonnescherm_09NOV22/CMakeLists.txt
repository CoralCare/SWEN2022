cmake_minimum_required(VERSION 2.8)

project(TEST_Zonnescherm_09NOV22)
add_executable(${PROJECT_NAME}
    "main.cpp"
    "test.cpp"
    "test.h")

enable_testing()

include_directories("/home/student/Desktop/2022SWEN/SWEN_2022/Zonnescherm Software Ubuntu/TEST_zonnescherm_Catch2/Catch2/src/")
include_directories("/home/student/Desktop/2022SWEN/SWEN_2022/Zonnescherm Software Ubuntu/Zonnescherm_01NOV22/")
