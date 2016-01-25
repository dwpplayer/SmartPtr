cmake_minimum_required(VERSION 3.2)
project(SmartPtr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GMOCK_FILES  lib/gmock-gtest-all.cc)
set(SOURCE_FILES main.cpp src/ConcreteObj.cpp)

set(TEST_FILES UnitTest/AutoPtrTest.cpp  UnitTest/UniquePtrTest.cpp  UnitTest/SharedPtrTest.cpp UnitTest/MockConcreteObj.cpp UnitTest/SharePtrBidirectRefTest.cpp UnitTest/SmartPtrConverter.cpp)


add_executable(SmartPtr ${SOURCE_FILES}  ${TEST_FILES}  ${GMOCK_FILES} )