/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef SIDECROSSORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define SIDECROSSORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <algorithm>   // Include algorithm header for std::sort
#include <stdexcept>   // Include stdexcept header for std::out_of_range

namespace ariel { // Namespace to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for SideCrossOrderIterator
    class SideCrossOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance
        std::vector<T> cross_data;        // Data arranged in side-cross order
        size_t index;                     // Current index into cross_data

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        SideCrossOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0

            if (container->size() == 0) {  // Check if container is empty
                cross_data = std::vector<T>{};  // Initialize empty cross_data
                if (is_end) {  // Check if end iterator is requested
                    index = 0;  // Set index to 0 for empty container
                }
                return;  // Exit constructor early
            }
            std::vector<T> sorted = container->getData();  // Copy container data
            std::sort(sorted.begin(), sorted.end());  // Sort data in ascending order

            size_t start = 0;  // Initialize start index to beginning
            size_t end = sorted.size() - 1;  // Initialize end index to last element

            while (start <= end) {  // Continue until start meets or exceeds end
                if (start == end) {  // Check if only one element remains
                    cross_data.push_back(sorted[start]);  // Add single element
                } else {  // Add elements from both ends
                    cross_data.push_back(sorted[start]);  // Add element from start
                    cross_data.push_back(sorted[end]);  // Add element from end
                }
                ++start;  // Increment start index
                if (end > 0) --end; // Decrement end index with underflow protection
            }

            if (is_end) {  // Check if end iterator is requested
                index = cross_data.size();  // Set index to end of cross_data
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element
            if (index >= cross_data.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return cross_data[index];  // Return element at current index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        SideCrossOrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (index >= cross_data.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            ++index;  // Increment index
            return *this;  // Return reference to self
        }

        /**
         * @return Copy of iterator before increment
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Postfix increment operator
        SideCrossOrderIterator operator++(int) {  // Increment iterator (postfix) // ++ (postfix)
            if (index >= cross_data.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            SideCrossOrderIterator temp = *this;  // Save current iterator state
            ++(*this);                            // Increment self using prefix ++
            return temp;                          // Return copy before increment
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at different positions, false otherwise
         */
        // Inequality comparison operator
        bool operator!=(const SideCrossOrderIterator& other) const {  // Compare iterators for inequality
            return index != other.index;  // Return true if indices differ
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at same position, false otherwise
         */
        // Equality comparison operator
        bool operator==(const SideCrossOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index;  // Return true if indices are equal
        }
    };

} // Namespace ariel

#endif //SIDECROSSORDERITERATOR_HPP  // Header guard