enable_testing()

# Fetch dependencies (gtest, etc.)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(cmake/RandomEventsTestDependencies.cmake)

# adding the Google_Tests_run target
add_executable(RunUnitTest test_interval.cpp
                           test_set.cpp
                           test_variable.cpp
                           test_product_algebra.cpp)

include_directories(${SRC_DIR}/random_events/include)

# linking Google_Tests_run with random_events which will be tested
target_link_libraries(RunUnitTest random_events
                                  GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(RunUnitTest)
