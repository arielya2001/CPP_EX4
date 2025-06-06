cmake_minimum_required(VERSION 3.30)
project(CPP_EX4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPP_EX4
        Demo.cpp
        MyContainer.hpp
        AscendingOrderIterator.hpp
        DescendingOrderIterator.hpp
        SideCrossOrderIterator.hpp
        ReverseOrderIterator.hpp
        OrderIterator.hpp
        MiddleOutOrderIterator.hpp
        Main.cpp
        tests.cpp
)
