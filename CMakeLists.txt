cmake_minimum_required(VERSION 3.10)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(passmgr
  src/main.cpp
  src/include/helper.cpp
)
