//
// Created by ariely122 on 6/6/25.
//

#ifndef REVERSEORDERITERATOR_HPP
#define REVERSEORDERITERATOR_HPP

#include <vector>
#include <stdexcept>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class ReverseOrderIterator {
    private:
        const MyContainer<T>* container;
        size_t index;

    public:
        // 🔹 בנאי רגיל
        ReverseOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {
            if (is_end) {
                index = container->getData().size();
            }
        }

        // 🔹 בנאי העתקה
        ReverseOrderIterator(const ReverseOrderIterator& other)
            : container(other.container), index(other.index) {}

        // 🔹 אופרטור השמה
        ReverseOrderIterator& operator=(const ReverseOrderIterator& other) {
            if (this != &other) {
                container = other.container;
                index = other.index;
            }
            return *this;
        }

        // 🔹 גישה לערך
        T operator*() const {
            const std::vector<T>& data = container->getData();
            if (index >= data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return data[data.size() - 1 - index]; // ← סריקה הפוכה
        }

        // 🔹 ++
        ReverseOrderIterator& operator++() {
            ++index;
            return *this;
        }

        // 🔹 השוואה
        bool operator!=(const ReverseOrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const ReverseOrderIterator& other) const {
            return index == other.index;
        }
    };

}

#endif //REVERSEORDERITERATOR_HPP
