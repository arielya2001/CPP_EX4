//
// Created by ariely122 on 6/6/25.
//

#ifndef SIDECROSSORDERITERATOR_HPP
#define SIDECROSSORDERITERATOR_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class SideCrossOrderIterator {
    private:
        const MyContainer<T>* container;
        std::vector<T> cross_data;  // הסדר המיוחד
        size_t index;

    public:
        // 🔹 בנאי רגיל
        SideCrossOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {

            std::vector<T> sorted = container->getData();
            std::sort(sorted.begin(), sorted.end());

            size_t start = 0;
            size_t end = sorted.size() - 1;

            while (start <= end) {
                if (start == end) {
                    cross_data.push_back(sorted[start]);
                } else {
                    cross_data.push_back(sorted[start]);
                    cross_data.push_back(sorted[end]);
                }
                ++start;
                if (end > 0) --end; // הגנה מפני underflow
            }

            if (is_end) {
                index = cross_data.size();
            }
        }
        // 🔹 גישה לערך
        T operator*() const {
            if (index >= cross_data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return cross_data[index];
        }

        // 🔹 ++
        SideCrossOrderIterator& operator++() {
            if (index >= cross_data.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // 🔹 ++ (postfix)
        SideCrossOrderIterator operator++(int) {
            SideCrossOrderIterator temp = *this;  // שומר את המצב הנוכחי
            ++(*this);                            // קורא ל־prefix ++ שכבר מוגדר
            return temp;                          // מחזיר את העותק לפני ההגדלה
        }


        // 🔹 השוואה
        bool operator!=(const SideCrossOrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const SideCrossOrderIterator& other) const {
            return index == other.index;
        }
    };

}
#endif //SIDECROSSORDERITERATOR_HPP
