/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef MYCONTAINER_HPP  // Header guard to prevent multiple inclusions of this file
#define MYCONTAINER_HPP

#include <vector>      // Include vector header for storing container data
#include <iostream>    // Include iostream header for output streaming
#include <algorithm>   // Include algorithm header for std::remove
#include <stdexcept>   // Include stdexcept header for std::runtime_error
#include "AscendingOrderIterator.hpp"    // Include header for AscendingOrderIterator
#include "DescendingOrderIterator.hpp"   // Include header for DescendingOrderIterator
#include "ReverseOrderIterator.hpp"      // Include header for ReverseOrderIterator
#include "SideCrossOrderIterator.hpp"    // Include header for SideCrossOrderIterator
#include "OrderIterator.hpp"             // Include header for OrderIterator
#include "MiddleOutOrderIterator.hpp"    // Include header for MiddleOutOrderIterator

namespace ariel { // Namespace ariel to encapsulate classes and functions

    template<typename T> // Template class definition for MyContainer
    class MyContainer {
    private:
        std::vector<T> data;  // Vector to store container elements

    public:
        /**
         * @throws None
         */
        MyContainer() = default;  // Default constructor

        /**
         * @param value Element to add to the container
         * @return None
         * @throws None
         */
        void addElement(const T& value) {  // Add an element to the container
            data.push_back(value);  // Append value to data vector
        }

        /**
         * @param value Element to remove from the container
         * @return None
         * @throws std::runtime_error If element is not found
         */
        void removeElement(const T& value) {  // Remove an element from the container
            auto it = std::remove(data.begin(), data.end(), value);  // Move matching elements to end
            if (it == data.end()) {  // Check if no elements were found
                throw std::runtime_error("Element not found in container.");  // Throw exception if not found
            }
            data.erase(it, data.end());  // Erase removed elements from vector
        }

        /**
         * @return Number of elements in the container
         * @throws None
         */
        size_t size() const {  // Return the number of elements
            return data.size();  // Return size of data vector
        }

        /**
         * @return Constant reference to the underlying data vector
         * @throws None
         */
        const std::vector<T>& getData() const {  // Get container data
            return data;  // Return reference to data vector
        }

        /**
         * @param os Output stream to write to
         * @param container MyContainer to print
         * @return Reference to the output stream
         * @throws None
         */
        // Print all elements
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {  // Stream output operator
            os << "[";  // Print opening bracket
            for (size_t i = 0; i < container.data.size(); ++i) {  // Iterate over elements
                os << container.data[i];  // Print current element
                if (i < container.data.size() - 1) {  // Check if not last element
                    os << ", ";  // Print comma and space
                }
            }
            os << "]";  // Print closing bracket
            return os;  // Return output stream
        }

        /**
         * @return Iterator to the beginning of ascending order
         * @throws None
         */
        AscendingOrderIterator<T> begin_ascending_order() const {  // Begin iterator for ascending order
            return AscendingOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of ascending order
         * @throws None
         */
        AscendingOrderIterator<T> end_ascending_order() const {  // End iterator for ascending order
            return AscendingOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of descending order
         * @throws None
         */
        DescendingOrderIterator<T> begin_descending_order() const {  // Begin iterator for descending order
            return DescendingOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of descending order
         * @throws None
         */
        DescendingOrderIterator<T> end_descending_order() const {  // End iterator for descending order
            return DescendingOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of side-cross order
         * @throws None
         */
        SideCrossOrderIterator<T> begin_side_cross_order() const {  // Begin iterator for side-cross order
            return SideCrossOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of side-cross order
         * @throws None
         */
        SideCrossOrderIterator<T> end_side_cross_order() const {  // End iterator for side-cross order
            return SideCrossOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of reverse order
         * @throws None
         */
        ReverseOrderIterator<T> begin_reverse_order() const {  // Begin iterator for reverse order
            return ReverseOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of reverse order
         * @throws None
         */
        ReverseOrderIterator<T> end_reverse_order() const {  // End iterator for reverse order
            return ReverseOrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of insertion order
         * @throws None
         */
        OrderIterator<T> begin_order() const {  // Begin iterator for insertion order
            return OrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of insertion order
         * @throws None
         */
        OrderIterator<T> end_order() const {  // End iterator for insertion order
            return OrderIterator<T>(*this, true);  // Return new iterator at end
        }

        /**
         * @return Iterator to the beginning of middle-out order
         * @throws None
         */
        MiddleOutOrderIterator<T> begin_middle_out_order() const {  // Begin iterator for middle-out order
            return MiddleOutOrderIterator<T>(*this, false);  // Return new iterator at start
        }

        /**
         * @return Iterator to the end of middle-out order
         * @throws None
         */
        MiddleOutOrderIterator<T> end_middle_out_order() const {  // End iterator for middle-out order
            return MiddleOutOrderIterator<T>(*this, true);  // Return new iterator at end
        }

    };

} // Namespace ariel

#endif //MYCONTAINER_HPP  // Header guard