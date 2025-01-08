#set minimum require cmake ver
cmake_minimum_required(VERSION 3.30)

#setup project and language
project(fzfcpp VERSION 1.0 LANGUAGES CXX)

#specify c++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#grab all source files
file(GLOB SOURCES "src/*.cpp")

#make excutable
add_executable(fzfc ${SOURCES})

#link header files
#target_include_directories(fzfc PRIVATE include)

#link external libraries
#target_link_libraries(fzfc PRIVATE lib)


