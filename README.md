# MyContainer Iterator Project  
**Mail** – ariel.yaacobi@msmail.ariel.ac.il  

## Overview  
This project implements a generic container class `MyContainer<T>` in C++, along with six different iterators for traversing the elements in unique orders:

- Ascending order (`begin_ascending_order`)
- Descending order (`begin_descending_order`)
- Side-cross order (`begin_side_cross_order`)
- Reverse order (`begin_reverse_order`)
- Original insertion order (`begin_order`)
- Middle-out order (`begin_middle_out_order`)

The project demonstrates iterator behavior through:
- A comprehensive test suite using the doctest framework
- Sample usage in `Main.cpp` and `Demo.cpp`

## File Structure  
- `MyContainer.hpp`: Defines the generic container with dynamic element management and methods for accessing each iterator type.
- `AscendingOrderIterator.hpp`: Iterates elements in ascending numerical order.
- `DescendingOrderIterator.hpp`: Iterates elements in descending numerical order.
- `SideCrossOrderIterator.hpp`: Alternates between smallest and largest remaining values.
- `ReverseOrderIterator.hpp`: Iterates in reverse of insertion order.
- `OrderIterator.hpp`: Iterates in the original order of insertion.
- `MiddleOutOrderIterator.hpp`: Starts from the middle element and expands outward alternately.
- `tests.cpp`: Contains a full test suite for verifying correct iterator logic, comparison operators, exception handling, and traversal correctness.
- `Main.cpp`: Provides formatted output of all iterator types for two sample containers (odd and even-sized).
- `Demo.cpp`: A minimal example showcasing the functionality of all six iterator types.
- `doctest.h`: Testing framework used for writing and running unit tests.

## Class Design  

### MyContainer  
- Template class storing elements of type `T`.
- Provides `addElement`, `removeElement`, `size`, and accessor methods for each iterator type.
- Elements are stored in a dynamic internal vector.

### Iterators  
Each iterator is implemented as a separate class that:
- Stores a pointer to the container and manages its own index/order logic.
- Implements `operator*`, `operator++`, `==`, and `!=`.
- Throws `std::out_of_range` on dereferencing `end()`.

#### AscendingOrderIterator  
- Traverses elements in non-decreasing order.

#### DescendingOrderIterator  
- Traverses elements in non-increasing order.

#### SideCrossOrderIterator  
- Alternates between smallest and largest, progressing toward the center.

#### ReverseOrderIterator  
- Traverses elements in reverse of insertion.

#### OrderIterator  
- Traverses elements in original insertion order.

#### MiddleOutOrderIterator  
- Begins from the middle, moves outward alternately.

## Features  
- **Full STL-style iteration**: All iterators conform to forward-iterator behavior.
- **Custom logic per iterator**: Each one demonstrates a unique traversal pattern.
- **Robust exception safety**: Dereferencing `end()` throws a well-defined `std::out_of_range` exception.
- **Comprehensive unit testing**: All iterator behaviors, comparisons, and exception scenarios are covered.

## Usage  

### Run the Main Demo  
```bash
g++ -std=c++17 Main.cpp -o main
./main
```
Prints all six traversal patterns for two sample containers.

### Run the Tests  
```bash
g++ -std=c++17 tests.cpp -o tests
./tests
```
Runs all doctest-based unit tests and prints results for iterator correctness.

### Run Demo (Simplified Version)  
```bash
g++ -std=c++17 Demo.cpp -o demo
./demo
```
Demonstrates iterator output with a predefined container.

## Examples  
A 5-element container with values `{4, 9, 3, 11, 5}` will print:
```
Ascending Order: 3 4 5 9 11
Descending Order: 11 9 5 4 3
SideCross Order: 3 11 4 9 5
Reverse Order: 5 11 3 9 4
Order (original): 4 9 3 11 5
MiddleOut Order: 3 11 4 9 5
```

## Notes  
- No external libraries are used aside from `doctest.h`.
- Designed for educational and demonstration purposes.
- Template-based for generality (though most demos use `int`).

## Author & Date  
- Developed by: Ariel Ya'acobi  
- Assignment: Iterator Design Project  
- Date: June 2025  
