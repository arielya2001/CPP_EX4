//
// Created by ariely122 on 6/6/25.
//

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "AscendingOrderIterator.hpp"
#include "DescendingOrderIterator.hpp"
#include "ReverseOrderIterator.hpp"
#include "SideCrossOrderIterator.hpp"
#include "OrderIterator.hpp"
#include "MiddleOutOrderIterator.hpp"


namespace ariel {

    template<typename T>
    class MyContainer {
    private:
        std::vector<T> data;

    public:
        MyContainer() = default;

        void addElement(const T& value) {
            data.push_back(value);
        }

        void removeElement(const T& value) {
            auto it = std::remove(data.begin(), data.end(), value);
            if (it == data.end()) {
                throw std::runtime_error("Element not found in container.");
            }
            data.erase(it, data.end());
        }

        size_t size() const {
            return data.size();
        }

        const std::vector<T>& getData() const {
            return data;
        }

        // הדפסת כל האיברים
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            os << "[";
            for (size_t i = 0; i < container.data.size(); ++i) {
                os << container.data[i];
                if (i < container.data.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }




        AscendingOrderIterator<T> begin_ascending_order() const {
            return AscendingOrderIterator<T>(*this, false);
        }

        AscendingOrderIterator<T> end_ascending_order() const {
            return AscendingOrderIterator<T>(*this, true);
        }


        DescendingOrderIterator<T> begin_descending_order() const {
            return DescendingOrderIterator<T>(*this, false);
        }

        DescendingOrderIterator<T> end_descending_order() const {
            return DescendingOrderIterator<T>(*this, true);
        }

        SideCrossOrderIterator<T> begin_side_cross_order() const {
            return SideCrossOrderIterator<T>(*this, false);
        }

        SideCrossOrderIterator<T> end_side_cross_order() const {
            return SideCrossOrderIterator<T>(*this, true);
        }

        ReverseOrderIterator<T> begin_reverse_order() const {
            return ReverseOrderIterator<T>(*this, false);
        }

        ReverseOrderIterator<T> end_reverse_order() const {
            return ReverseOrderIterator<T>(*this, true);
        }

        OrderIterator<T> begin_order() const {
            return OrderIterator<T>(*this, false);
        }

        OrderIterator<T> end_order() const {
            return OrderIterator<T>(*this, true);
        }

        MiddleOutOrderIterator<T> begin_middle_out_order() const {
            return MiddleOutOrderIterator<T>(*this, false);
        }

        MiddleOutOrderIterator<T> end_middle_out_order() const {
            return MiddleOutOrderIterator<T>(*this, true);
        }



    };
}


#endif //MYCONTAINER_HPP
