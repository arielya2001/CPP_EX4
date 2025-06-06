/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef REVERSEORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define REVERSEORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <stdexcept>   // Include stdexcept header for std::out_of_range

namespace ariel { // Namespace to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for ReverseOrderIterator
    class ReverseOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance
        size_t index;                     // Current index for iteration

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        ReverseOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0
            if (is_end) {  // Check if end iterator is requested
                index = container->getData().size();  // Set index to end of data
            }
        }

        /**
         * @return Current element pointed to by iterator in reverse order
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element // גישה לערך
            const std::vector<T>& data = container->getData();  // Get reference to container data
            if (index >= data.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return data[data.size() - 1 - index]; // Access element in reverse order
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        ReverseOrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (index >= container->getData().size()) {  // Check if increment would go beyond end
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
        ReverseOrderIterator operator++(int) {  // Increment iterator (postfix) // ++ (postfix)
            if (index >= container->getData().size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            ReverseOrderIterator temp = *this;  // Save current iterator state
            ++(*this);                          // Increment self using prefix ++
            return temp;                        // Return copy before increment
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at different positions, false otherwise
         */
        // Inequality comparison operator
        bool operator!=(const ReverseOrderIterator& other) const {  // Compare iterators for inequality
            return index != other.index;  // Return true if indices differ
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at same position, false otherwise
         */
        // Equality comparison operator
        bool operator==(const ReverseOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index;  // Return true if indices are equal
        }
    };

} // Namespace ariel

#endif //REVERSEORDERITERATOR_HPP  // Header guard