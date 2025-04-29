cmake_minimum_required(VERSION 3.10)
project(EBS_Demo)

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

file(GLOB SRC_FILES src/*.cpp)
add_library(ebs_lib ${SRC_FILES})
target_include_directories(ebs_lib PUBLIC include)

add_executable(ebs_system src/ebs_system.cpp)
target_link_libraries(ebs_system ebs_lib)

add_executable(rtos_integration src/rtos_integration.cpp src/hal_can.cpp)
target_link_libraries(rtos_integration ebs_lib)

file(GLOB TEST_SRC tests/*.cpp)
foreach(testfile ${TEST_SRC})
    get_filename_component(testname ${testfile} NAME_WE)
    add_executable(${testname} ${testfile} ${SRC_FILES})
    target_link_libraries(${testname} GTest::gtest_main)
endforeach()

enable_testing()
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${TEST_SRC}
)