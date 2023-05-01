cmake_minimum_required(VERSION 3.5)

project(TOY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(TOY main.cpp command.h gui.h gui.cpp toy.h toy.cpp)
target_link_libraries(TOY ${CURSES_LIBRARIES})

install(TARGETS TOY
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
