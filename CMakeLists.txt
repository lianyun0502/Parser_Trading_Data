cmake_minimum_required(VERSION 3.0.0)
project(Trade_Data_parser VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) # set the output path of the executable file
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST) # find all source files in src directory
include_directories(/usr/include ${PROJECT_SOURCE_DIR}/include) # include the header files
add_compile_options(-std=c++20 -O2) # set the compile options

add_executable(main ${SRC_LIST} main.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
