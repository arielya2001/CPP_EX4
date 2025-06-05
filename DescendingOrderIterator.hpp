//
// Created by ariely122 on 6/6/25.
//


#ifndef DESCENDINGORDERITERATOR_HPP
#define DESCENDINGORDERITERATOR_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class DescendingOrderIterator {
    private:
        const MyContainer<T>* container;
        std::vector<T> sorted_data;
        size_t index;

    public:
        // 🔹 בנאי רגיל
        DescendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {
            sorted_data = container->getData();
            std::sort(sorted_data.begin(), sorted_data.end(), std::greater<T>());
            if (is_end) {
                index = sorted_data.size();
            }
        }

        //  בנאי העתקה
        DescendingOrderIterator(const DescendingOrderIterator& other)
            : container(other.container),
              sorted_data(other.sorted_data),
              index(other.index) {}

        //  אופרטור השמה
        DescendingOrderIterator& operator=(const DescendingOrderIterator& other) {
            if (this != &other) {
                container = other.container;
                sorted_data = other.sorted_data;
                index = other.index;
            }
            return *this;
        }

        // אופרטור גישה לערך
        T operator*() const {
            if (index >= sorted_data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return sorted_data[index];
        }

        // אופרטור ++
        DescendingOrderIterator& operator++() {
            if (index >= sorted_data.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // השוואה
        bool operator!=(const DescendingOrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const DescendingOrderIterator& other) const {
            return index == other.index;
        }
    };

}
#endif //DESCENDINGORDERITERATOR_HPP
