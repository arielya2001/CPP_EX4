/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef ASCENDINGORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define ASCENDINGORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <algorithm>   // Include algorithm header for std::sort
#include <cstddef>     // Include cstddef header for size_t

namespace ariel { // Namespace to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for AscendingOrderIterator
    class AscendingOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance // מצביע לקונטיינר
        std::vector<T> sorted_data;       // Copy of container data in ascending order // Sorted copy of container data
        size_t index;                     // Current index into sorted data // Index into sorted_data

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // 🔹 Regular constructor
        AscendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0
            sorted_data = container->getData();  // Copy container data into sorted_data
            std::sort(sorted_data.begin(), sorted_data.end());  // Sort data in ascending order
            if (is_end) {  // Check if end iterator is requested
                index = sorted_data.size();  // Set index to end of sorted_data
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access current element
        T operator*() const {  // Return current element
            if (index >= sorted_data.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return sorted_data[index];  // Return element at current index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        AscendingOrderIterator& operator++() {  // Increment iterator (prefix)
            if (index >= sorted_data.size()) {  // Check if increment would go beyond end
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
        AscendingOrderIterator operator++(int) {  // Increment iterator (postfix)
            if (index >= sorted_data.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            AscendingOrderIterator temp = *this;  // Save current iterator state // Save current iterator state
            ++(*this);                            // Increment self // Increment self
            return temp;                          // Return old iterator state // Return copy before increment
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at different positions, false otherwise
         */
        // Inequality comparison operator
        bool operator!=(const AscendingOrderIterator& other) const {  // Compare iterators for inequality
            return index != other.index;  // Return true if indices differ
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at same position, false otherwise
         */
        // Equality comparison operator
        bool operator==(const AscendingOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index;  // Return true if indices are equal
        }
    };

} // Namespace ariel

#endif //ASCENDINGORDERITERATOR_HPP  // Header guard