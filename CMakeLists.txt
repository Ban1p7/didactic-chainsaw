cmake_minimum_required(VERSION "3.25.1")

project("DidacticChainsaw")


find_package(SDL2 REQUIRED)
include_directories("DidacticChainsaw" ${SDL2_INCLUDE_DIRS})

add_executable("DidacticChainsaw" "src/main.cpp")
target_link_libraries("DidacticChainsaw" ${SDL2_LIBRARIES})
