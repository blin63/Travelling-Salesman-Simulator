cmake_minimum_required(VERSION 3.20)
project(lab1template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)

add_executable(assignment2template main.cpp city.cpp city.hpp tour.cpp tour.hpp genetic.cpp genetic.hpp population.cpp population.hpp SingletonFacade.cpp SingletonFacade.hpp)
