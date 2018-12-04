cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 20)

project(async_notifier)
add_executable(${PROJECT_NAME} "main.cpp" "async_callback_caller.cpp")
