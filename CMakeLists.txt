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
	./inc/job.hpp
	./inc/portability.hpp
	./inc/runnable.hpp
	./inc/thread.hpp
	)

###############setup source files###################################
set(SOURCE_FILES 
	./src/eventqueue.cpp
	./src/job.cpp
	./src/thread.cpp
	)

###############setup example source files###################################
set(EXAMPLE_FILES 
	./test/main.cpp
	)

add_library(OoT SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_executable(Example ${EXAMPLE_FILES})

target_link_libraries(Example OoT)
