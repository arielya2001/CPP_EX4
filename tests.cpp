#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "MyContainer.hpp"
#include <vector>
#include <string>
#include <sstream>

using namespace ariel;
using namespace std;

// Helper function to capture container output via operator<<
template<typename T>
string captureOutput(const MyContainer<T>& c) {
    ostringstream oss;
    oss << c;
    return oss.str();
}

TEST_CASE("Basic operations and container functions") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    CHECK(captureOutput(c) == "[]");

    c.addElement(5);
    c.addElement(3);
    c.addElement(8);
    c.addElement(1);
    c.addElement(7);
    CHECK(c.size() == 5);
    CHECK(captureOutput(c) == "[5, 3, 8, 1, 7]");
    CHECK(c.getData() == vector<int>{5, 3, 8, 1, 7});

    c.removeElement(3);
    CHECK(c.size() == 4);
    CHECK(captureOutput(c) == "[5, 8, 1, 7]");
    CHECK(c.getData() == vector<int>{5, 8, 1, 7});

    CHECK_THROWS_AS(c.removeElement(42), runtime_error);
}

TEST_CASE("Iterators with int") {
    SUBCASE("Odd-sized container") {
        MyContainer<int> c;
        c.addElement(4);
        c.addElement(9);
        c.addElement(3);
        c.addElement(11);
        c.addElement(5);

        vector<int> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<int>{3, 4, 5, 9, 11});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<int>{11, 9, 5, 4, 3});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<int>{3, 11, 4, 9, 5});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<int>{5, 11, 3, 9, 4});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<int>{4, 9, 3, 11, 5});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<int>{3, 9, 11, 4, 5});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Even-sized container") {
        MyContainer<int> c;
        c.addElement(10);
        c.addElement(2);
        c.addElement(7);
        c.addElement(1);
        c.addElement(6);
        c.addElement(12);

        vector<int> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<int>{1, 2, 6, 7, 10, 12});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<int>{12, 10, 7, 6, 2, 1});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<int>{1, 12, 2, 10, 6, 7});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<int>{12, 6, 1, 7, 2, 10});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<int>{10, 2, 7, 1, 6, 12});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<int>{1, 7, 6, 2, 12, 10});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Empty container") {
        MyContainer<int> c;

        vector<int> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<int>{});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<int>{});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<int>{});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<int>{});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<int>{});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<int>{});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Single element") {
        MyContainer<int> c;
        c.addElement(42);

        vector<int> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<int>{42});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<int>{42});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<int>{42});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<int>{42});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<int>{42});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<int>{42});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Duplicate elements") {
        MyContainer<int> c;
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);

        vector<int> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<int>{3, 3, 3, 3, 3});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Large container") {
        MyContainer<int> c;
        for (int i = 0; i < 1000; ++i) {
            c.addElement(i % 100); // Limited range to avoid excessive memory
        }
        CHECK(c.size() == 1000);
        vector<int> asc;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            asc.push_back(*asc_it);
        }
        CHECK(asc.size() == 1000);
        CHECK(asc[0] == 0);
        CHECK(asc[999] == 99);
    }
}

TEST_CASE("Iterators with string") {
    SUBCASE("Odd-sized container") {
        MyContainer<string> c;
        c.addElement("banana");
        c.addElement("apple");
        c.addElement("cherry");
        c.addElement("date");
        c.addElement("fig");

        vector<string> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<string>{"apple", "banana", "cherry", "date", "fig"});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<string>{"fig", "date", "cherry", "banana", "apple"});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<string>{"apple", "fig", "banana", "date", "cherry"});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<string>{"fig", "date", "cherry", "apple", "banana"});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<string>{"banana", "apple", "cherry", "date", "fig"});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<string>{"cherry", "apple", "date", "banana", "fig"});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Empty container") {
        MyContainer<string> c;

        vector<string> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<string>{});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<string>{});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<string>{});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<string>{});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<string>{});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<string>{});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Single element") {
        MyContainer<string> c;
        c.addElement("hello");

        vector<string> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<string>{"hello"});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }
}

TEST_CASE("Iterators with double") {
    SUBCASE("Odd-sized container") {
        MyContainer<double> c;
        c.addElement(3.14);
        c.addElement(1.41);
        c.addElement(2.72);
        c.addElement(5.0);
        c.addElement(0.5);

        vector<double> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<double>{0.5, 1.41, 2.72, 3.14, 5.0});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<double>{5.0, 3.14, 2.72, 1.41, 0.5});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<double>{0.5, 5.0, 1.41, 3.14, 2.72});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<double>{0.5, 5.0, 2.72, 1.41, 3.14});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<double>{3.14, 1.41, 2.72, 5.0, 0.5});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<double>{2.72, 1.41, 5.0, 3.14, 0.5});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Empty container") {
        MyContainer<double> c;

        vector<double> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<double>{});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<double>{});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<double>{});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<double>{});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<double>{});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<double>{});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Single element") {
        MyContainer<double> c;
        c.addElement(1.23);

        vector<double> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<double>{1.23});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<double>{1.23});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<double>{1.23});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<double>{1.23});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<double>{1.23});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<double>{1.23});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }
}

TEST_CASE("Iterators with char") {
    SUBCASE("Odd-sized container") {
        MyContainer<char> c;
        c.addElement('e');
        c.addElement('a');
        c.addElement('c');
        c.addElement('b');
        c.addElement('d');

        vector<char> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<char>{'a', 'b', 'c', 'd', 'e'});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<char>{'e', 'd', 'c', 'b', 'a'});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<char>{'a', 'e', 'b', 'd', 'c'});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<char>{'d', 'b', 'c', 'a', 'e'});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<char>{'e', 'a', 'c', 'b', 'd'});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<char>{'c', 'a', 'b', 'e', 'd'});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Empty container") {
        MyContainer<char> c;

        vector<char> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<char>{});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<char>{});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<char>{});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<char>{});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<char>{});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<char>{});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Single element") {
        MyContainer<char> c;
        c.addElement('x');

        vector<char> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<char>{'x'});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<char>{'x'});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<char>{'x'});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<char>{'x'});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<char>{'x'});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<char>{'x'});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }
}

TEST_CASE("Iterators with float") {
    SUBCASE("Odd-sized container") {
        MyContainer<float> c;
        c.addElement(3.1f);
        c.addElement(1.2f);
        c.addElement(2.3f);
        c.addElement(4.4f);
        c.addElement(0.5f);

        vector<float> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<float>{0.5f, 1.2f, 2.3f, 3.1f, 4.4f});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<float>{4.4f, 3.1f, 2.3f, 1.2f, 0.5f});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<float>{0.5f, 4.4f, 1.2f, 3.1f, 2.3f});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<float>{0.5f, 4.4f, 2.3f, 1.2f, 3.1f});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<float>{3.1f, 1.2f, 2.3f, 4.4f, 0.5f});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<float>{2.3f, 1.2f, 4.4f, 3.1f, 0.5f});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Empty container") {
        MyContainer<float> c;

        vector<float> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<float>{});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<float>{});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<float>{});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<float>{});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<float>{});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<float>{});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }

    SUBCASE("Single element") {
        MyContainer<float> c;
        c.addElement(1.5f);

        vector<float> result;
        for (auto asc_it = c.begin_ascending_order(); asc_it != c.end_ascending_order(); ++asc_it) {
            result.push_back(*asc_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);

        result.clear();
        for (auto desc_it = c.begin_descending_order(); desc_it != c.end_descending_order(); ++desc_it) {
            result.push_back(*desc_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);

        result.clear();
        for (auto side_it = c.begin_side_cross_order(); side_it != c.end_side_cross_order(); ++side_it) {
            result.push_back(*side_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);

        result.clear();
        for (auto rev_it = c.begin_reverse_order(); rev_it != c.end_reverse_order(); ++rev_it) {
            result.push_back(*rev_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        // Note: ReverseOrderIterator does not throw on ++ beyond end

        result.clear();
        for (auto order_it = c.begin_order(); order_it != c.end_order(); ++order_it) {
            result.push_back(*order_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);

        result.clear();
        for (auto mid_it = c.begin_middle_out_order(); mid_it != c.end_middle_out_order(); ++mid_it) {
            result.push_back(*mid_it);
        }
        CHECK(result == vector<float>{1.5f});
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
    }
}