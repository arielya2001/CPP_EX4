/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef DESCENDINGORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define DESCENDINGORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <algorithm>   // Include algorithm header for std::sort and std::greater
#include <stdexcept>   // Include stdexcept header for std::out_of_range

namespace ariel { // Namespace to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for DescendingOrderIterator
    class DescendingOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance // מצביע לקונטיינר
        std::vector<T> sorted_data;       // Copy of container data in descending order // Sorted copy of container data
        size_t index;                     // Current index into sorted data // Index into sorted_data

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // 🔹 Regular constructor
        DescendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0
            sorted_data = container->getData();  // Copy container data into sorted_data
            std::sort(sorted_data.begin(), sorted_data.end(), std::greater<T>());  // Sort data in descending order
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
        DescendingOrderIterator& operator++() {  // Increment iterator (prefix)
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
        DescendingOrderIterator operator++(int) {  // Increment iterator (postfix)
            if (index >= sorted_data.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            DescendingOrderIterator temp = *this;  // Save current iterator state // שומר מצב נוכחי
            ++(*this);                             // Increment self // מעלה אינדקס (משתמש ב־prefix)
            return temp;                           // Return copy before increment // מחזיר עותק מהמצב הקודם
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at different positions, false otherwise
         */
        // Inequality comparison operator
        bool operator!=(const DescendingOrderIterator& other) const {  // Compare iterators for inequality
            return index != other.index;  // Return true if indices differ
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at same position, false otherwise
         */
        // Equality comparison operator
        bool operator==(const DescendingOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index;  // Return true if indices are equal
        }
    };

} // Namespace ariel

#endif //DESCENDINGORDERITERATOR_HPP  // Header guard