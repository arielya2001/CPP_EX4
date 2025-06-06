#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include "AscendingOrderIterator.hpp"
#include "DescendingOrderIterator.hpp"
#include "SideCrossOrderIterator.hpp"
#include "ReverseOrderIterator.hpp"
#include "OrderIterator.hpp"
#include "MiddleOutOrderIterator.hpp"
#include <sstream>
#include <vector>

using namespace ariel;

// Helper function to capture container output
template<typename T>
std::string captureOutput(const MyContainer<T>& container) {
    std::ostringstream oss;
    oss << container;
    return oss.str();
}

TEST_CASE("MyContainer Basic Functionality") {
    MyContainer<int> container;

    SUBCASE("Empty container") {
        CHECK(container.size() == 0);
        CHECK(captureOutput(container) == "[]");
    }

    SUBCASE("Add elements") {
        container.addElement(1);
        container.addElement(2);
        container.addElement(3);
        CHECK(container.size() == 3);
        CHECK(captureOutput(container) == "[1, 2, 3]");
    }

    SUBCASE("Remove existing element") {
        container.addElement(1);
        container.addElement(2);
        container.addElement(1);
        container.removeElement(1);
        CHECK(container.size() == 1);
        CHECK(captureOutput(container) == "[2]");
    }

    SUBCASE("Remove non-existing element throws exception") {
        CHECK_THROWS_AS(container.removeElement(1), std::runtime_error);
    }

    SUBCASE("Add and remove multiple elements") {
        container.addElement(5);
        container.addElement(5);
        container.addElement(3);
        container.removeElement(5);
        CHECK(container.size() == 1);
        CHECK(captureOutput(container) == "[3]");
    }
}

TEST_CASE("AscendingOrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(3);
    container.addElement(1);
    container.addElement(4);
    container.addElement(2);

    SUBCASE("Correct ascending order") {
        std::vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({1, 2, 3, 4}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_ascending_order();
        CHECK(it == empty.end_ascending_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_ascending_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }

    SUBCASE("Increment beyond end throws exception") {
        auto it = container.end_ascending_order();
        CHECK_THROWS_AS(++it, std::out_of_range);
    }
}

TEST_CASE("DescendingOrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(3);
    container.addElement(1);
    container.addElement(4);
    container.addElement(2);

    SUBCASE("Correct descending order") {
        std::vector<int> result;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({4, 3, 2, 1}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_descending_order();
        CHECK(it == empty.end_descending_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_descending_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }

    SUBCASE("Increment beyond end throws exception") {
        auto it = container.end_descending_order();
        CHECK_THROWS_AS(++it, std::out_of_range);
    }
}

TEST_CASE("SideCrossOrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(3);
    container.addElement(1);
    container.addElement(4);
    container.addElement(2);

    SUBCASE("Correct side cross order") {
        std::vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({1, 4, 2, 3}));
    }

    SUBCASE("Odd number of elements") {
        MyContainer<int> odd;
        odd.addElement(1);
        odd.addElement(3);
        odd.addElement(2);
        std::vector<int> result;
        for (auto it = odd.begin_side_cross_order(); it != odd.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({1, 3, 2}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_side_cross_order();
        CHECK(it == empty.end_side_cross_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_side_cross_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }

    SUBCASE("Increment beyond end throws exception") {
        auto it = container.end_side_cross_order();
        CHECK_THROWS_AS(++it, std::out_of_range);
    }
}

TEST_CASE("ReverseOrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);

    SUBCASE("Correct reverse order") {
        std::vector<int> result;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({4, 3, 2, 1}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_reverse_order();
        CHECK(it == empty.end_reverse_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_reverse_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
}

TEST_CASE("OrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);

    SUBCASE("Correct original order") {
        std::vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({1, 2, 3, 4}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_order();
        CHECK(it == empty.end_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }

    SUBCASE("Increment beyond end throws exception") {
        auto it = container.end_order();
        CHECK_THROWS_AS(++it, std::out_of_range);
    }
}

TEST_CASE("MiddleOutOrderIterator Tests") {
    MyContainer<int> container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);

    SUBCASE("Correct middle-out order (odd size)") {
        std::vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({3, 2, 4, 1, 5}));
    }

    SUBCASE("Even number of elements") {
        MyContainer<int> even;
        even.addElement(1);
        even.addElement(2);
        even.addElement(3);
        even.addElement(4);
        std::vector<int> result;
        for (auto it = even.begin_middle_out_order(); it != even.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<int>({2, 1, 3, 4}));
    }

    SUBCASE("Empty container") {
        MyContainer<int> empty;
        auto it = empty.begin_middle_out_order();
        CHECK(it == empty.end_middle_out_order());
    }

    SUBCASE("Out of range access throws exception") {
        auto it = container.end_middle_out_order();
        CHECK_THROWS_AS(*it, std::out_of_range);
    }

    SUBCASE("Increment beyond end throws exception") {
        auto it = container.end_middle_out_order();
        CHECK_THROWS_AS(++it, std::out_of_range);
    }
}

TEST_CASE("Edge Cases") {
    SUBCASE("Single element container") {
        MyContainer<int> container;
        container.addElement(1);

        std::vector<int> asc, desc, side, rev, ord, mid;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc.push_back(*it);
        }
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            desc.push_back(*it);
        }
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            side.push_back(*it);
        }
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            rev.push_back(*it);
        }
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            ord.push_back(*it);
        }
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            mid.push_back(*it);
        }
        CHECK(asc == std::vector<int>({1}));
        CHECK(desc == std::vector<int>({1}));
        CHECK(side == std::vector<int>({1}));
        CHECK(rev == std::vector<int>({1}));
        CHECK(ord == std::vector<int>({1}));
        CHECK(mid == std::vector<int>({1}));
    }

    SUBCASE("Duplicate elements") {
        MyContainer<int> container;
        container.addElement(2);
        container.addElement(2);
        container.addElement(2);

        std::vector<int> asc, desc, side;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc.push_back(*it);
        }
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            desc.push_back(*it);
        }
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            side.push_back(*it);
        }
        CHECK(asc == std::vector<int>({2, 2, 2}));
        CHECK(desc == std::vector<int>({2, 2, 2}));
        CHECK(side == std::vector<int>({2, 2, 2}));
    }

    SUBCASE("Large container") {
        MyContainer<int> container;
        for (int i = 0; i < 1000; ++i) {
            container.addElement(i);
        }
        CHECK(container.size() == 1000);

        std::vector<int> asc;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc.push_back(*it);
        }
        CHECK(asc.size() == 1000);
        CHECK(asc[0] == 0);
        CHECK(asc[999] == 999);
    }
}

TEST_CASE("Non-integer Type Support") {
    MyContainer<std::string> container;
    container.addElement("apple");
    container.addElement("banana");
    container.addElement("cherry");

    SUBCASE("Ascending order with strings") {
        std::vector<std::string> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == std::vector<std::string>({"apple", "banana", "cherry"}));
    }

    SUBCASE("Remove string element") {
        container.removeElement("banana");
        CHECK(container.size() == 2);
        CHECK(captureOutput(container) == "[apple, cherry]");
    }
}