cmake_minimum_required(VERSION 3.28.3)
project(Game)
set(CMAKE_CXX_STANDART 23)
set(CMAKE_BUILD_TYPE Release)
file(GLOB CPP_SOURCE src/*.cpp)

#Установить путь для исполняемого файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME} ${CPP_SOURCE})

find_package(SFML COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)