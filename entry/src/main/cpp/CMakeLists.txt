# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(testgo)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)
add_library(gotest SHARED IMPORTED)
set_target_properties(gotest PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libgotest.so)
#set_target_properties(gotest PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})

add_library(entry SHARED napi_init.cpp)
target_link_libraries(entry PUBLIC libace_napi.z.so hilog_ndk.z gotest)