cmake_minimum_required(VERSION 3.30)
project(Polynomial)

set(CMAKE_CXX_STANDARD 20)

add_executable(Polynomial main.cpp
        polynomial.h
        polynomial.cpp
        calc.cpp
        calc.h
        term.cpp
        term.h
        util.cpp
        util.h
        mstack.hpp)
