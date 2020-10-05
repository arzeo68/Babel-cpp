if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.5.1)
project(babel)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)
set(CMAKE_CXX_STANDARD 17)


if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS}")
else()
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -g3 -Wextra -Wfatal-errors")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STANDARD_UNIX_CXX_FLAGS}")
endif()

if (EXISTS conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
else()
    message(FATAL_ERROR "No conanbuildinfo.cmake file found")
endif()

#include(CMakeSources.cmake)

conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)


file(GLOB_RECURSE SOURCES_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} "client/*.cpp")

# UI.h  PATH
include_directories(test/build)

add_executable(babel_client ${SOURCES_CLIENT} client/main.cpp
        common/Protocol.hpp
        common/Log.cpp
        common/Log.hpp)

add_executable(babel_server
        server/src/DB/Database.cpp
        server/src/DB/Database.hpp
        server/src/DB/Exception.cpp
        server/src/API/Route/Route.cpp
        server/src/API/Route/Route.hpp
        server/src/API/Router/Router.cpp
        server/src/API/Router/Router.hpp
        server/src/User/User.cpp
        server/src/User/User.hpp
        server/src/Main.cpp
        server/src/Network/Client.cpp
        server/src/Network/Client.hpp
        server/src/Network/Exception.cpp
        server/src/Network/Network.cpp
        server/src/Network/Network.hpp
        server/src/API/Route/List/Listing.cpp
        server/src/API/Route/List/Listing.hpp
        server/src/User/Pool.cpp
        server/src/User/Pool.hpp
        common/Protocol.hpp
        common/Log.cpp
        common/Log.hpp
        server/src/API/Route/Arguments.hpp)

if (MSVC)
    set_target_properties(babel_client PROPERTIES LINK_FLAGS /MACHINE:X64)
    set_target_properties(babel_server PROPERTIES LINK_FLAGS /MACHINE:X64)
endif()

install(TARGETS babel_client DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS babel_server DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#############################################################
target_link_libraries(babel_client ${CONAN_LIBS})
target_link_libraries(babel_client Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)
target_include_directories(babel_client PRIVATE inc ../common/inc)

#############################################################
target_link_libraries(babel_server ${CONAN_LIBS})
#target_link_libraries(babel_server Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)
