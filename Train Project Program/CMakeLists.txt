cmake_minimum_required(VERSION 3.12)
project(Project_OB)

set(CMAKE_CXX_STANDARD 11)

add_executable(Project_OB main.cpp vehicle.h train.h locomotive.h dieselLocomotive.h
        vehicle.cpp locomotive.cpp dieselLocomotive.cpp
        electricLocomotive.h electricLocomotive.cpp
        carriage.h carriage.cpp
        peopleCarriage.h peopleCarriage.cpp
        sleepCarriage.h sleepCarriage.cpp
        openCarriage.h openCarriage.cpp closedCarriage.h closedCarriage.cpp
        train.cpp simConst.h station.h station.cpp trainMap.h trainMap.cpp
        trainController.h trainController.cpp simulation.h simulation.cpp
        event.h event.cpp userInterface.h userinterface.cpp)