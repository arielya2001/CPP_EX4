/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef ASCENDINGORDERITERATOR_HPP
#define ASCENDINGORDERITERATOR_HPP

#include <vector>
#include <algorithm>
#include <cstddef>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class AscendingOrderIterator {
    private:
        const MyContainer<T>* container;  // מצביע לקונטיינר
        std::vector<T> sorted_data;       // עותק ממויין של האיברים
        size_t index;                     // אינדקס

    public:
        // 🔹 בנאי רגיל
        AscendingOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {
            sorted_data = container->getData();
            std::sort(sorted_data.begin(), sorted_data.end());
            if (is_end) {
                index = sorted_data.size();
            }
        }

        // אופרטור גישה לערך
        T operator*() const {
            if (index >= sorted_data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return sorted_data[index];
        }

        // אופרטור הגדלה
        AscendingOrderIterator& operator++() {
            if (index >= sorted_data.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        AscendingOrderIterator operator++(int) {
            if (index >= sorted_data.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            AscendingOrderIterator temp = *this;  // שומר את הערך הנוכחי
            ++(*this);                            // מעלה את האינדקס (משתמש ב־++ הקיים)
            return temp;                          // מחזיר את הערך הישן
        }

        // השוואה
        bool operator!=(const AscendingOrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const AscendingOrderIterator& other) const {
            return index == other.index;
        }
    };

}

#endif //ASCENDINGORDERITERATOR_HPP
