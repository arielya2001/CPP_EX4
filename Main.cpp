/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#include <iostream>      // Include iostream header for input/output operations
#include "MyContainer.hpp"  // Include MyContainer header for container class

using namespace ariel;  // Use ariel namespace to access MyContainer

/**
 * @param container The MyContainer to print elements from
 * @param label Description label for the container
 * @return None
 * @throws None
 */
// Helper function that prints all iteration orders
template<typename T>  // Template function for printing container orders
void printAllOrders(const MyContainer<T>& container, const std::string& label) {  // Print all iteration orders
    std::cout << "--- " << label << " ---" << std::endl;  // Print header with label
    std::cout << "Size: " << container.size() << std::endl;  // Print container size

    std::cout << "Ascending Order: ";  // Print label for ascending order
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {  // Iterate in ascending order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << std::endl;  // Print newline after ascending order

    std::cout << "Descending Order: ";  // Print label for descending order
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {  // Iterate in descending order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << std::endl;  // Print newline after descending order

    std::cout << "SideCross Order: ";  // Print label for side-cross order
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {  // Iterate in side-cross order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << std::endl;  // Print newline after side-cross order

    std::cout << "Reverse Order: ";  // Print label for reverse order
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {  // Iterate in reverse order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << std::endl;  // Print newline after reverse order

    std::cout << "Order (original): ";  // Print label for insertion order
    for (auto it = container.begin_order(); it != container.end_order(); ++it) {  // Iterate in insertion order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << std::endl;  // Print newline after insertion order

    std::cout << "MiddleOut Order: ";  // Print label for middle-out order
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {  // Iterate in middle-out order
        std::cout << *it << ' ';  // Print current element followed by space
    }
    std::cout << "\n" << std::endl;  // Print newline and extra newline
}

/**
 * @return 0 on successful execution
 * @throws None
 */
int main() {  // Main function
    MyContainer<int> oddContainer;  // Create container for odd-sized test // 5 איברים
    oddContainer.addElement(4);  // Add element 4 to oddContainer
    oddContainer.addElement(9);  // Add element 9 to oddContainer
    oddContainer.addElement(3);  // Add element 3 to oddContainer
    oddContainer.addElement(11);  // Add element 11 to oddContainer
    oddContainer.addElement(5);  // Add element 5 to oddContainer

    MyContainer<int> evenContainer;  // Create container for even-sized test // 6 איברים
    evenContainer.addElement(10);  // Add element 10 to evenContainer
    evenContainer.addElement(2);  // Add element 2 to evenContainer
    evenContainer.addElement(7);  // Add element 7 to evenContainer
    evenContainer.addElement(1);  // Add element 1 to evenContainer
    evenContainer.addElement(6);  // Add element 6 to evenContainer
    evenContainer.addElement(12);  // Add element 12 to evenContainer

    std::cout << "Odd Container: " << oddContainer << std::endl;  // Print oddContainer using operator<<
    printAllOrders(oddContainer, "Odd-sized container [5 items]");  // Print all orders for oddContainer
    std::cout << "Even Container: " << evenContainer << std::endl;  // Print evenContainer using operator<<
    printAllOrders(evenContainer, "Even-sized container [6 items]");  // Print all orders for evenContainer

    return 0;  // Return success code
}