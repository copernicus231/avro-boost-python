cmake_minimum_required(VERSION 3.10)
project(boost-python)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Boost 1.66 REQUIRED COMPONENTS system filesystem python)
set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(PythonLibs)
find_package(AvroCPP)
find_package(JNI)
include_directories("${PROJECT_SOURCE_DIR}/avro-module")
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${AVRO_INCLUDE_DIRS})
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})
include_directories("${PROJECT_SOURCE_DIR}/processor")
add_subdirectory(processor) 

add_executable(boost-python-main main.cpp)
target_link_libraries (boost-python-main processor ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${AVRO_LIBRARIES})
