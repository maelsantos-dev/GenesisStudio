cmake_minimum_required(VERSION 3.16)

project(GenesisStudio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GenesisStudio
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    src/ui/ModuleWidget.h
    src/ui/ModuleWidget.cpp
    src/ui/SignalCanvas.h
    src/ui/SignalCanvas.cpp
)

target_link_libraries(GenesisStudio
    PRIVATE
    Qt6::Widgets
)