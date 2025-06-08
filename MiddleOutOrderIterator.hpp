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
        const MyContainer<T>* container;              // Pointer to the MyContainer instance
        std::vector<size_t> middle_out_indices;       // Indices into container data in middle-out order
        size_t index;                                 // Current index into middle_out_indices
        size_t capturedVersion;                       // Version of the container at iterator creation

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        MiddleOutOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0

            capturedVersion = container->getVersion(); // Capture version at construction
            const std::vector<T>& data = container->getData();  // Get reference to container data
            size_t n = data.size();  // Get size of container data
            middle_out_indices.reserve(n);  // Pre-allocate index vector

            if (n != 0) {  // Container is not empty
                int mid = n / 2;  // Calculate middle index
                int left = mid - 1;  // Set left index to one before middle
                int right = mid + 1;  // Set right index to one after middle

                middle_out_indices.push_back(mid);  // Add middle index first

                while (left >= 0 || right < (int)n) {  // Add indices alternately from center
                    if (left >= 0) {
                        middle_out_indices.push_back(left--);  // Add left index
                    }
                    if (right < (int)n) {
                        middle_out_indices.push_back(right++);  // Add right index
                    }
                }
            }

            if (is_end) {  // Check if end iterator is requested
                index = middle_out_indices.size();  // Set index to end of middle_out_indices
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element // גישה לערך
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for invalid version
            }
            if (index >= middle_out_indices.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return container->getData()[middle_out_indices[index]];  // Return element at current index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        MiddleOutOrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for invalid version
            }
            if (index >= middle_out_indices.size()) {  // Check if increment would go beyond end
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
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for invalid version
            }
            if (index >= middle_out_indices.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            MiddleOutOrderIterator temp = *this;  // Save current iterator state
            ++(*this);                            // Increment self using prefix ++
            return temp;                          // Return copy before increment
        }

        /**
         * @brief Equality comparison operator.
         * @param other Another iterator to compare.
         * @return True if both iterators are at the same position and container.
         */
        bool operator==(const MiddleOutOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index && container == other.container;  // Return true if indices and containers match
        }

        /**
         * @brief Inequality comparison operator.
         * @param other Another iterator to compare.
         * @return True if iterators are at different positions or containers.
         */
        bool operator!=(const MiddleOutOrderIterator& other) const {  // Compare iterators for inequality
            return !(*this == other);  // Return negation of equality
        }
    };

} // Namespace ariel

#endif // MIDDLEOUTORDERITERATOR_HPP  // Header guard