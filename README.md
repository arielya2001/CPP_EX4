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
- `Demo.cpp`: A minimal example showcasing the functionality of all six iterator types(Given to us).
- `doctest.h`: Testing framework used for writing and running unit tests.
- `Makefile`: Automates build, test, demo, and cleanup tasks via make commands

## Class Design  

### MyContainer  
- Template class storing elements of type `T`.
- Provides `addElement`, `removeElement`, `size`, `getData`, `operator<<` and accessor methods for each iterator type.
- Elements are stored in a dynamic internal vector.

### Iterators  
Each iterator is implemented as a separate class that:
- Stores a pointer to the container and manages its own index/order logic.
- Implements `operator*`, `operator++`(prefix and postfix), `==`, and `!=`.
- Iterators throw `std::out_of_range` in the following cases:
    - When dereferencing an iterator equal to `end_*_order()`
    - When incrementing an iterator equal to or beyond `end_*_order()` (both prefix and postfix)
    - When the container was modified after the iterator was created (based on version tracking)


#### AscendingOrderIterator  
- Traverses the elements in non-decreasing (ascending) order — from the smallest to the largest. 
- Elements with equal values retain their original insertion order.

#### DescendingOrderIterator  
- Traverses the elements in non-increasing (descending) order — from the largest to the smallest.
- As with ascending, equal elements preserve the order they were added.

#### SideCrossOrderIterator  
- Traverses the elements in an alternating pattern from both ends:
  - Starts with the smallest, then the largest, then the second smallest, then the second largest, and so on — zigzagging toward the center.

#### ReverseOrderIterator  
- Traverses the elements in the reverse of insertion order. 
- The last inserted element is returned first, mimicking stack (LIFO) behavior.

#### OrderIterator  
- Traverses elements in the original insertion order — exactly the sequence in which elements were added to the container.

#### MiddleOutOrderIterator  
- For odd-sized containers, it begins at the exact middle element, then alternates between elements to the left and right of center.
- For even-sized containers, it starts at the element just right of center (i.e., index size/2), then alternates between elements to the left and right, moving outward from that point.


## Features  
- **Full STL-style iteration**: All iterators conform to forward-iterator behavior.
- **Custom logic per iterator**: Each one demonstrates a unique traversal pattern.
- **Robust exception safety**: Dereferencing `end()` throws a well-defined `std::out_of_range` exception.
- **Comprehensive unit testing**: All iterator behaviors, comparisons, and exception scenarios are covered.
- 

## Usage  

### Run the Main  
```bash
make main
```
Prints all six traversal patterns for two sample containers.

### Run the Tests  
```bash
make test
```
Runs all doctest-based unit tests and prints results for iterator correctness.

### Run Demo 
```bash
make demo
```
Demonstrates iterator output with a predefined container.

### Run with Valgrind
```bash
make valgrind
```

Runs both main.out and tests.out through Valgrind to check for memory leaks and access errors.

###  Clean Build Files
```bash
make clean
```

Removes all compiled binaries: demo.out, main.out, and tests.out.

## Examples  
A 5-element container with values `{4, 9, 3, 11, 5}` will print:
```
Ascending Order: 3 4 5 9 11
Descending Order: 11 9 5 4 3
SideCross Order: 3 11 4 9 5
Reverse Order: 5 11 3 9 4
Order (original): 4 9 3 11 5
MiddleOut Order: 3 9 11 4 5
```

## Notes  
- No external libraries are used aside from `doctest.h`.
- Template-based for generality (though most demos use `int`).
- Iterators access container data via reference (getData()), avoiding unnecessary copies.
- Index tracking is done with size_t for type safety and consistency.

## Author & Date  
- Developed by: Ariel Ya'acobi  
- Assignment: Iterator Design Project  
- Date: June 2025  
