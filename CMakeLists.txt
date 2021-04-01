cmake_minimum_required(VERSION 3.16)
project(ugc_node_agent)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/app/include)
include_directories(src/core/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core LIB_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app APP_CODE)
add_executable(ugc_node_agent main.cpp ${APP_CODE} ${LIB_CODE})