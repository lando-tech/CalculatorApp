cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(CalculatorApp VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add GTKMM package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.68)
pkg_check_modules(GIOMM REQUIRED giomm-2.68)

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${GLIBMM_INCLUDE_DIRS}
    ${GIOMM_INCLUDE_DIRS}
    include
)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${GLIBMM_LIBRARY_DIRS}
    ${GIOMM_LIBRARY_DIRS}
)

add_definitions(
    ${GTKMM_CFLAGS_OTHER}
    ${GLIBMM_CFLAGS_OTHER}
    ${GIOMM_CFLAGS_OTHER}
)

# Add the source files
add_executable(calc main.cpp src/calc.cpp src/window.cpp)

# Link libraries
target_link_libraries(calc
    ${GTKMM_LIBRARIES}
    ${GLIBMM_LIBRARIES}
    ${GIOMM_LIBRARIES}
)

# Enable more warnings
if (CMAKE_CXX_COMPILER_ID MATCHES 'GNU|Clang')
    target_compile_options(calc PRIVATE -Wall -Wextra -Wpedantic)
endif()
