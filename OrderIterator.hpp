/*
 * Mail - ariel.yaacobi@msmail.ariel.ac.il
 */

#ifndef ORDERITERATOR_HPP  // Header guard to prevent multiple inclusions of this file
#define ORDERITERATOR_HPP

#include <vector>      // Include vector header for vector operations
#include <stdexcept>   // Include stdexcept header for std::out_of_range

namespace ariel { // Namespace to encapsulate classes and functions

    template<typename T>
    class MyContainer;  // Forward declaration of MyContainer class template

    template<typename T> // Template class definition for OrderIterator
    class OrderIterator {
    private:
        const MyContainer<T>* container;  // Pointer to the MyContainer instance
        size_t index;                     // Current index into container data
        size_t capturedVersion;          // Version of the container at iterator creation

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        OrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer, index
            capturedVersion = cont.getVersion(); // Initialize captured version
            if (is_end) {  // Check if end iterator is requested
                index = container->getData().size();  // Set index to end of data
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         * @throws std::runtime_error If container was modified during iteration
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element // גישה לערך
            if (capturedVersion != container->getVersion()) {  // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for version mismatch
            }
            const std::vector<T>& data = container->getData();  // Get reference to container data
            if (index >= data.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return data[index];  // Return element at current index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         * @throws std::runtime_error If container was modified during iteration
         */
        // Prefix increment operator
        OrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (capturedVersion != container->getVersion()) {  // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for version mismatch
            }
            if (index >= container->getData().size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            ++index;  // Increment index
            return *this;  // Return reference to self
        }

        /**
         * @return Copy of iterator before increment
         * @throws std::out_of_range If iterator is at or beyond end
         * @throws std::runtime_error If container was modified during iteration
         */
        // Postfix increment operator
        OrderIterator operator++(int) {  // Increment iterator (postfix) // ++ (postfix)
            if (capturedVersion != container->getVersion()) {  // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");  // Throw exception for version mismatch
            }
            if (index >= container->getData().size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            OrderIterator temp = *this;  // Save current iterator state
            ++(*this);                   // Increment self using prefix ++
            return temp;                 // Return copy before increment
        }

        /**
         * @brief Equality comparison operator.
         * @param other Another iterator to compare.
         * @return True if both iterators are at the same position and container.
         */
        bool operator==(const OrderIterator& other) const {  // Compare iterators for equality
            return index == other.index && container == other.container;  // Return true if indices and containers are equal
        }

        /**
         * @brief Inequality comparison operator.
         * @param other Another iterator to compare.
         * @return True if iterators are at different positions or containers.
         */
        bool operator!=(const OrderIterator& other) const {  // Compare iterators for inequality
            return !(*this == other);  // Return true if not equal
        }
    };

} // Namespace ariel

#endif // ORDERITERATOR_HPP  // Header guard
