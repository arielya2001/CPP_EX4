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
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }
        // 🔹 ++ (postfix)
        ReverseOrderIterator operator++(int) {
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ReverseOrderIterator temp = *this;  // שמירה על המצב הנוכחי
            ++(*this);                          // שימוש באופרטור prefix שכבר קיים
            return temp;                        // החזרת המצב הישן
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
