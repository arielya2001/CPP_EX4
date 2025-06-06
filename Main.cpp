/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#include <iostream>
#include "MyContainer.hpp"

using namespace ariel;

// פונקציית עזר שמדפיסה את כל סוגי הסריקות
template<typename T>
void printAllOrders(const MyContainer<T>& container, const std::string& label) {
    std::cout << "--- " << label << " ---" << std::endl;
    std::cout << "Size: " << container.size() << std::endl;

    std::cout << "Ascending Order: ";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Descending Order: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "SideCross Order: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Reverse Order: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "Order (original): ";
    for (auto it = container.begin_order(); it != container.end_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "MiddleOut Order: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n" << std::endl;
}

int main() {
    MyContainer<int> oddContainer;  // 5 איברים
    oddContainer.addElement(4);
    oddContainer.addElement(9);
    oddContainer.addElement(3);
    oddContainer.addElement(11);
    oddContainer.addElement(5);

    MyContainer<int> evenContainer;  // 6 איברים
    evenContainer.addElement(10);
    evenContainer.addElement(2);
    evenContainer.addElement(7);
    evenContainer.addElement(1);
    evenContainer.addElement(6);
    evenContainer.addElement(12);


    std::cout << "Odd Container: " << oddContainer << std::endl;
    printAllOrders(oddContainer, "Odd-sized container [5 items]");
    std::cout << "Even Container: " << evenContainer << std::endl;
    printAllOrders(evenContainer, "Even-sized container [6 items]");

    return 0;
}