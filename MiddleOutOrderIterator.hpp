/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef MIDDLEOUTORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define MIDDLEOUTORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <stdexcept>   // Include stdexcept header for std::out_of_range

namespace ariel { // Namespace ariel to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for MiddleOutOrderIterator
    class MiddleOutOrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance // מצביע לקונטיינר
        std::vector<T> middle_out_data;   // Data arranged in middle-out order // Data in middle-out traversal order
        size_t index;                     // Current index into middle_out_data // Index into middle_out_data

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        MiddleOutOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0

            const std::vector<T>& data = container->getData();  // Get reference to container data
            size_t n = data.size();  // Get size of container data

            if (n == 0) {  // Check if container is empty
                middle_out_data = {};  // Initialize empty middle_out_data
            } else {  // Container is not empty
                int mid = n / 2;  // Calculate middle index
                int left = mid - 1;  // Set left index to one before middle
                int right = mid + 1;  // Set right index to one after middle

                // Add middle element first
                middle_out_data.push_back(data[mid]);  // Add middle element to middle_out_data // הוסף את האמצע קודם

                // Add alternately left and right
                while (left >= 0 || right < (int)n) {  // Continue until all elements are added // הוסף לסירוגין שמאלה וימינה
                    if (left >= 0) {  // Check if left index is valid
                        middle_out_data.push_back(data[left--]);  // Add left element and decrement left
                    }
                    if (right < (int)n) {  // Check if right index is valid
                        middle_out_data.push_back(data[right++]);  // Add right element and increment right
                    }
                }
            }

            if (is_end) {  // Check if end iterator is requested
                index = middle_out_data.size();  // Set index to end of middle_out_data
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element // גישה לערך
            if (index >= middle_out_data.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return middle_out_data[index];  // Return element at current index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        MiddleOutOrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (index >= middle_out_data.size()) {  // Check if increment would go beyond end
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
        MiddleOutOrderIterator operator++(int) {  // Increment iterator (postfix) // ++ (postfix)
            if (index >= middle_out_data.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            MiddleOutOrderIterator temp = *this;  // Save current iterator state // שומר את המצב הנוכחי
            ++(*this);                            // Increment self using prefix ++ // מפעיל את prefix ++
            return temp;                          // Return copy before increment // מחזיר את העותק הישן
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at different positions, false otherwise
         */
        // Inequality comparison operator
        bool operator!=(const MiddleOutOrderIterator& other) const {  // Compare iterators for inequality // השוואה
            return index != other.index;  // Return true if indices differ
        }

        /**
         * @param other Iterator to compare with
         * @return True if iterators are at same position, false otherwise
         */
        // Equality comparison operator
        bool operator==(const MiddleOutOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index;  // Return true if indices are equal
        }
    };

} // Namespace ariel

#endif // MIDDLEOUTORDERITERATOR_HPP  // Header guard