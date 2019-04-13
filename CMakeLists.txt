cmake_minimum_required(VERSION 3.4.1)

set(BUILD_PRC build-prc)
set(PILRC pilrc)

set(CMAKE_C_COMPILER m68k-palmos-gcc)
set(CMAKE_C_FLAGS "-O2 -I${SOURCE_DIR}/WristPDA_SDK_v1.3/Include")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/WristPDA_SDK_v1.3/Include)

add_executable(CrypticWatch
        ${SOURCE_DIR}/main.c
        ${SOURCE_DIR}/watch_face.h
        ${SOURCE_DIR}/watch_face.c
        ${SOURCE_DIR}/watch_face_internal.h
        ${SOURCE_DIR}/block_watch_face.h
        ${SOURCE_DIR}/block_watch_face.c)

add_custom_target(resources ${PILRC} ${SOURCE_DIR}/res.rcp
        SOURCES ${SOURCE_DIR}/res.rcp
        WORKING_DIRECTORY ${SOURCE_DIR})

add_custom_target(CrypticWatch_prc ALL ${BUILD_PRC} CrypticWatch.prc "CrypticWatch" Foss CrypticWatch ${SOURCE_DIR}/*.bin)

add_dependencies(CrypticWatch_prc CrypticWatch resources)
