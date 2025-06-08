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
        const MyContainer<T>* container;         // Pointer to the MyContainer instance
        std::vector<size_t> cross_indices;       // Indices into container data in side-cross order
        size_t index;                            // Current index into cross_indices
        size_t capturedVersion;                  // Version of the container at iterator creation

    public:
        /**
         * @param cont Reference to the MyContainer to iterate over
         * @param is_end If true, initializes iterator to end position; default is false
         * @throws None
         */
        // Regular constructor
        SideCrossOrderIterator(const MyContainer<T>& cont, bool is_end = false)  // Constructor for iterator
            : container(&cont), index(0) {  // Initialize container pointer and index to 0
            capturedVersion = container->getVersion();  // Capture version at construction

            const std::vector<T>& data = container->getData();  // Get container data reference
            size_t size = data.size();  // Determine data size

            if (size == 0) {  // Check if container is empty
                cross_indices = std::vector<size_t>{};  // Initialize empty cross_indices
                if (is_end) {
                    index = 0;  // Set index to 0 for empty container
                }
                return;  // Exit constructor early
            }

            std::vector<size_t> indices(size);  // Prepare vector of indices
            for (size_t i = 0; i < size; ++i) {
                indices[i] = i;  // Fill with 0, 1, 2, ..., size-1
            }

            std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
                return data[a] < data[b];  // Sort indices based on actual values
            });

            size_t start = 0;  // Initialize start index to beginning
            size_t end = size - 1;  // Initialize end index to last element

            while (start <= end) {  // Continue until start meets or exceeds end
                if (start == end) {  // Check if only one element remains
                    cross_indices.push_back(indices[start]);  // Add single middle index
                } else {
                    cross_indices.push_back(indices[start]);  // Add index from start
                    cross_indices.push_back(indices[end]);    // Add index from end
                }
                ++start;  // Increment start index
                if (end > 0) --end;  // Decrement end index with underflow protection
            }

            if (is_end) {  // Check if end iterator is requested
                index = cross_indices.size();  // Set index to end of cross_indices
            }
        }

        /**
         * @return Current element pointed to by iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Dereference operator to access value
        T operator*() const {  // Return current element
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= cross_indices.size()) {  // Check if index is out of bounds
                throw std::out_of_range("Iterator out of range");  // Throw exception for invalid access
            }
            return container->getData()[cross_indices[index]];  // Return element at sorted cross index
        }

        /**
         * @return Reference to incremented iterator
         * @throws std::out_of_range If iterator is at or beyond end
         */
        // Prefix increment operator
        SideCrossOrderIterator& operator++() {  // Increment iterator (prefix) // ++
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= cross_indices.size()) {  // Check if increment would go beyond end
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
            if (capturedVersion != container->getVersion()) { // Ensure container was not modified since iterator creation
                throw std::runtime_error("Container modified during iteration");
            }
            if (index >= cross_indices.size()) {  // Check if increment would go beyond end
                throw std::out_of_range("Cannot increment beyond end.");  // Throw exception for invalid increment
            }
            SideCrossOrderIterator temp = *this;  // Save current iterator state
            ++(*this);                            // Increment self using prefix ++
            return temp;                          // Return copy before increment
        }

        /**
         * @brief Equality comparison operator.
         * @param other Iterator to compare with
         * @return True if iterators are at same position and same container
         */
        bool operator==(const SideCrossOrderIterator& other) const {  // Compare iterators for equality
            return index == other.index && container == other.container;  // Return true if indices and containers are equal
        }

        /**
         * @brief Inequality comparison operator.
         * @param other Iterator to compare with
         * @return True if iterators are at different positions or containers
         */
        bool operator!=(const SideCrossOrderIterator& other) const {  // Compare iterators for inequality
            return !(*this == other);  // Return true if not equal
        }
    };

} // Namespace ariel

#endif //SIDECROSSORDERITERATOR_HPP  // Header guard
