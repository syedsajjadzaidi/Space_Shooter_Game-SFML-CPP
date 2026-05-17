cmake_minimum_required(VERSION 3.10)
project(SpaceShooterSFML)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

file(GLOB SOURCES "Source/*.cpp")
add_executable(space_shooter ${SOURCES})
target_include_directories(space_shooter PRIVATE Source)
target_link_libraries(space_shooter sfml-graphics sfml-window sfml-system sfml-audio)