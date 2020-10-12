cmake_minimum_required(VERSION 3.16)
project(task1)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -I ")

set(PROJECT_INCLUDE_DIR project/include)

#add_executable(task ./project/src/main.c ./project/src/utils.c)

include_directories(${PROJECT_INCLUDE_DIR})


file(GLOB SRC_FILES ./project/src/*.c)
file(GLOB TEST_SRC_FILES ./test/*.cpp)
list(REMOVE_ITEM SRC_FILES ./project/src/main.c)

add_library(lib ${SRC_FILES})
add_executable(task1 ./project/src/main.c)
target_link_libraries(task1 lib)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#                       'cmake -TESTING=ON'.
option(TESTING "Build all tests." OFF) # Makes boolean 'test' available.

if (TESTING)
    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # Link runTests with what we want to test and the GTest and DZ1 library
    add_executable(runTests ./test/main.cpp)
    target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
    target_link_libraries(runTests lib)
    gtest_discover_tests(runTests)

    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)

endif()


