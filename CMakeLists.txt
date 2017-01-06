#############create a project#######################################
cmake_minimum_required(VERSION 2.8)

SET (CMAKE_C_COMPILER "gcc")
SET (CMAKE_CXX_COMPILER "g++")

project(OoT)

############setup head file path######################################
include_directories(${PROJECT_SOURCE_DIR}/inc)

###########setup head files #######################################
set(HEADER_FILES 
	./inc/event.hpp
	./inc/eventqueue.hpp
	./inc/worker.hpp
	./inc/portability.hpp
	./inc/runnable.hpp
	)

###############setup source files###################################
set(SOURCE_FILES 
	./src/worker.cpp
	./src/eventqueue.cpp
	)

###############setup example source files###################################
set(EXAMPLE_FILES 
	./test/main.cpp
	)

add_library(OoT SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_executable(Example ${EXAMPLE_FILES})

target_link_libraries(Example OoT)
