cmake_minimum_required(VERSION 3.4)
project(Calendar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS date_time program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cc
        calendar.cc)

set(HEADERS
        calendar.h)

add_executable(Calendar ${SOURCE_FILES})
target_link_libraries(Calendar ${Boost_LIBRARIES})