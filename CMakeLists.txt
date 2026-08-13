cmake_minimum_required(VERSION 3.20)

cmake_policy(SET CMP0048 NEW)

project(GenesisStudio
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(GenesisStudio
    src/main.cpp
)

target_link_libraries(GenesisStudio
    PRIVATE
        Qt6::Widgets
)