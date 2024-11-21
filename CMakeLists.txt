include(CMakePrintHelpers)

cmake_minimum_required(VERSION 3.0)
project(ctest-example)

enable_testing()
include (ctests.cmake)

create_test_app(TestExample)