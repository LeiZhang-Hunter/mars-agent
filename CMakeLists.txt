cmake_minimum_required(VERSION 3.16)
project(mars-agent)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Add -O0 to remove optimizations when using gcc
IF (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
ENDIF (CMAKE_COMPILER_IS_GNUCC)

include_directories(src/app/include)
include_directories(src/app/include/function)
include_directories(src/lib-include)
include_directories(src/core/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core LIB_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core/event LIB_EVENT_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/core/os LIB_OS_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function LIB_OS_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/common COMMON_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function/http FUNCTION_HTTP_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function/health FUNCTION_HEALTH_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function/container FUNCTION_CONTAINER_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function/promethean FUNCTION_PROMETHEAN_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/function/skywalking FUNCTION_SKYWALKING_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app APP_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/config CONFIG_CODE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/app/module MODULE_CODE)

add_executable(mars main.cc ${APP_CODE} ${LIB_CODE} ${LIB_OS_CODE} ${LIB_EVENT_CODE}
        ${FUNCTION_HTTP_CODE} ${CONFIG_CODE} ${FUNCTION_HEALTH_CODE} ${FUNCTION_CONTAINER_CODE}
        ${MODULE_CODE} ${FUNCTION_PROMETHEAN_CODE} ${FUNCTION_SKYWALKING_CODE} ${COMMON_CODE})
target_link_libraries(mars
        yaml-cpp
        event
        prometheus-cpp-pull
        prometheus-cpp-push
        prometheus-cpp-core
        jsoncpp
        )