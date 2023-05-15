cmake_minimum_required(VERSION 3.25)

project(robot-tester VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_executable( ${PROJECT_NAME}
    main.cpp
    robot-tester.ui
    robot-tester.cpp
    robot-tester.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
