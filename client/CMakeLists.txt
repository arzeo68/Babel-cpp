project(Babel)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel main.cpp src/Audio/Optus/Optus.cpp src/Audio/Optus/Optus.h src/Audio/PortAudio/PortAudio.cpp src/Audio/PortAudio/PortAudio.h src/GUI/GUI.cpp src/GUI/GUI.h ../server/src/Auth/Auth.cpp ../server/src/Auth/Auth.h ../server/src/DB/Db.cpp ../server/src/DB/Db.h ../server/src/User/User.cpp ../server/src/User/User.h)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)
