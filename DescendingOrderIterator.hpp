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
        const MyContainer<T>* container;              // Pointer to the MyContainer instance
        std::vector<size_t> sorted_indices;           // Indices into container data in descending order
        size_t index;                                 // Current index into sorted indices
        size_t capturedVersion;                       // Version of the container at iterator creation

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // 🔹 Regular constructor
        DescendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0
            capturedVersion = container->getVersion(); // Capture version at construction

            const std::vector<T>& data = container->getData();  // Reference to container data
            sorted_indices.resize(data.size());                 // Allocate space for indices
            for (size_t i = 0; i < data.size(); ++i) {
                sorted_indices[i] = i;                          // Initialize with 0, 1, 2, ...
            }

            std::sort(sorted_indices.begin(), sorted_indices.end(),
                      [&](size_t a, size_t b) { return data[a] > data[b]; });  // Sort by actual values descending

            if (is_end) {  // Check if end iterator is requested
                index = sorted_indices.size();  // Set index to end of sorted indices
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access current element
        T operator*() const {  // Return current element
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return container->getData()[sorted_indices[index]];  // Access sorted value by index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        DescendingOrderIterator& operator++() {  // Increment iterator (prefix)
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {  // Check if increment would go beyond end
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
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= sorted_indices.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            DescendingOrderIterator temp = *this;  // Save current iterator state
            ++(*this);                             // Increment self
            return temp;                           // Return copy before increment
        }

        /**
         * @brief Equality comparison operator.
         * @param other Another iterator to compare.
         * @return True if both iterators are at the same position and container.
         */
        bool operator==(const DescendingOrderIterator& other) const { // Compare iterators for equality
            return index == other.index && container == other.container; // Return true if indices are equal
        }
        /**
         * @brief Inequality comparison operator.
         * @param other Another iterator to compare.
         * @return True if iterators are at different positions or containers.
         */
        bool operator!=(const DescendingOrderIterator& other) const { // Compare iterators for inequality
            return !(*this == other);// Return true if indices differ
        }
    };

} // Namespace ariel

#endif //DESCENDINGORDERITERATOR_HPP  // Header guard
