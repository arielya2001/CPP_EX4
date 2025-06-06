/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/

#ifndef ORDERITERATOR_HPP
#define ORDERITERATOR_HPP

#include <vector>
#include <stdexcept>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class OrderIterator {
    private:
        const MyContainer<T>* container;
        size_t index;

    public:
        // 🔹 בנאי רגיל
        OrderIterator(const MyContainer<T>& cont, bool is_end = false)
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
            return data[index];
        }

        // 🔹 ++
        OrderIterator& operator++() {
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // 🔹 ++ (postfix)
        OrderIterator operator++(int) {
            if (index >= container->getData().size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            OrderIterator temp = *this;  // שומר את המצב הנוכחי
            ++(*this);                   // מפעיל את prefix ++ שכבר קיים
            return temp;                 // מחזיר את העותק לפני ההגדלה
        }


        // 🔹 השוואה
        bool operator!=(const OrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const OrderIterator& other) const {
            return index == other.index;
        }
    };

}

#endif // ORDERITERATOR_HPP
