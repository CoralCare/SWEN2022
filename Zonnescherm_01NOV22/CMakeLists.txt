cmake_minimum_required(VERSION 2.8)

project(Zonnescherm_01NOV22)
add_executable(${PROJECT_NAME}
    "main.cpp"
    "fsm.cpp"
    "binnensensor.h"
    "buitensensor.h"
    "events.h"
    "fsm.h"
    "states.h"
    "uvsensor.h"
    "zonnescherm.h")
