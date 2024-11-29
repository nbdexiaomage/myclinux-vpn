cmake_minimum_required(VERSION 3.5.0)
project(demo01 VERSION 0.1.0 LANGUAGES C CXX)

aux_source_directory(./src SRC_LIST)

include_directories(./headfile)

add_executable(demo01 ${SRC_LIST})