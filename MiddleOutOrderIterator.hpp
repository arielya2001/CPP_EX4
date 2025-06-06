//
// Created by ariely122 on 6/6/25.
//

#ifndef MIDDLEOUTORDERITERATOR_HPP
#define MIDDLEOUTORDERITERATOR_HPP

#include <vector>
#include <stdexcept>

namespace ariel {

    template<typename T>
    class MyContainer;

    template<typename T>
    class MiddleOutOrderIterator {
    private:
        const MyContainer<T>* container;
        std::vector<T> middle_out_data;
        size_t index;

    public:
        // 🔹 בנאי רגיל
        MiddleOutOrderIterator(const MyContainer<T>& cont, bool is_end = false)
            : container(&cont), index(0) {

            const std::vector<T>& data = container->getData();
            size_t n = data.size();

            if (n == 0) {
                middle_out_data = {};
            } else {
                int mid = n / 2;
                int left = mid - 1;
                int right = mid + 1;

                // הוסף את האמצע קודם
                middle_out_data.push_back(data[mid]);

                // הוסף לסירוגין שמאלה וימינה
                while (left >= 0 || right < (int)n) {
                    if (left >= 0) {
                        middle_out_data.push_back(data[left--]);
                    }
                    if (right < (int)n) {
                        middle_out_data.push_back(data[right++]);
                    }
                }
            }

            if (is_end) {
                index = middle_out_data.size();
            }
        }

        // 🔹 גישה לערך
        T operator*() const {
            if (index >= middle_out_data.size()) {
                throw std::out_of_range("Iterator out of range");
            }
            return middle_out_data[index];
        }

        // 🔹 ++
        MiddleOutOrderIterator& operator++() {
            if (index >= middle_out_data.size()) {
                throw std::out_of_range("Cannot increment beyond end.");
            }
            ++index;
            return *this;
        }

        // 🔹 השוואה
        bool operator!=(const MiddleOutOrderIterator& other) const {
            return index != other.index;
        }

        bool operator==(const MiddleOutOrderIterator& other) const {
            return index == other.index;
        }
    };

}

#endif // MIDDLEOUTORDERITERATOR_HPP
