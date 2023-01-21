cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -O4")

project(UniPD_BattagliaNavale)

include_directories(include)

add_library(${PROJECT_NAME}
src/Position.cpp
src/Entity.cpp
src/UnitSection.cpp
src/Unit.cpp
src/Battleship.cpp
src/MovableUnit.cpp
src/Submarine.cpp
src/Support.cpp
src/Controller.cpp

)

add_executable(main 
	src/main.cpp
	)


    
target_link_libraries(main ${PROJECT_NAME})
