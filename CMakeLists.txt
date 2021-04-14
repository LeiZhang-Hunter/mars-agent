cmake_minimum_required(VERSION 3.16)
project(mars-agent)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Add -O0 to remove optimizations when using gcc
IF (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -event")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -event")
ENDIF (CMAKE_COMPILER_IS_GNUCC)

include_directories(src/app/include)
include_directories(src/core/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core LIB_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core/event LIB_EVENT_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core/os LIB_OS_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app APP_CODE)

link_libraries(event)
add_executable(mars main.cpp ${APP_CODE} ${LIB_CODE} ${LIB_OS_CODE} ${LIB_EVENT_CODE})