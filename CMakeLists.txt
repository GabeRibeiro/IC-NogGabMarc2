cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(IC_project2 VERSION 1.0)

# add the librarys
add_library(bitstream src/BitStream/bitstream.cpp)
add_library(golomb src/Golomb/Golomb.cpp)
add_library(img src/jpeg/ImageCodec.cpp)
add_library(audio src/audio/AudioCodec.cpp)

# add the executable
add_executable(main ${CMAKE_SOURCE_DIR}/src/main_test.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(golomb bitstream)

target_link_libraries(audio golomb bitstream)

target_link_libraries(img golomb bitstream ${OpenCV_LIBS})

target_link_libraries(main PUBLIC bitstream golomb img audio)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)