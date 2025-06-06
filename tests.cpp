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

// Helper function to test all iterators for a given container
template<typename T>
void testIterators(const MyContainer<T>& c,
                   const vector<T>& expected_asc,
                   const vector<T>& expected_desc,
                   const vector<T>& expected_side,
                   const vector<T>& expected_rev,
                   const vector<T>& expected_order,
                   const vector<T>& expected_mid) {
    vector<T> result;

    SUBCASE("Ascending Order") {
        result.clear();
        for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_asc);
        auto asc_end_it = c.end_ascending_order();
        CHECK_THROWS_AS(*asc_end_it, out_of_range);
        CHECK_THROWS_AS(++asc_end_it, out_of_range);
        CHECK_THROWS_AS(asc_end_it++, out_of_range);
    }

    SUBCASE("Descending Order") {
        result.clear();
        for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_desc);
        auto desc_end_it = c.end_descending_order();
        CHECK_THROWS_AS(*desc_end_it, out_of_range);
        CHECK_THROWS_AS(++desc_end_it, out_of_range);
        CHECK_THROWS_AS(desc_end_it++, out_of_range);
    }

    SUBCASE("Side Cross Order") {
        result.clear();
        for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_side);
        auto side_end_it = c.end_side_cross_order();
        CHECK_THROWS_AS(*side_end_it, out_of_range);
        CHECK_THROWS_AS(++side_end_it, out_of_range);
        CHECK_THROWS_AS(side_end_it++, out_of_range);
    }

    SUBCASE("Reverse Order") {
        result.clear();
        for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_rev);
        auto rev_end_it = c.end_reverse_order();
        CHECK_THROWS_AS(*rev_end_it, out_of_range);
        CHECK_THROWS_AS(++rev_end_it, out_of_range);
        CHECK_THROWS_AS(rev_end_it++, out_of_range);
    }

    SUBCASE("Insertion Order") {
        result.clear();
        for (auto it = c.begin_order(); it != c.end_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_order);
        auto order_end_it = c.end_order();
        CHECK_THROWS_AS(*order_end_it, out_of_range);
        CHECK_THROWS_AS(++order_end_it, out_of_range);
        CHECK_THROWS_AS(order_end_it++, out_of_range);
    }

    SUBCASE("Middle Out Order") {
        result.clear();
        for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_mid);
        auto mid_end_it = c.end_middle_out_order();
        CHECK_THROWS_AS(*mid_end_it, out_of_range);
        CHECK_THROWS_AS(++mid_end_it, out_of_range);
        CHECK_THROWS_AS(mid_end_it++, out_of_range);
    }
}

TEST_CASE("MyContainer operations with different types") {
    SUBCASE("Testing with int") {
        MyContainer<int> c;

        // Test initial state
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<int>{});

        // Test addElement
        c.addElement(5);
        c.addElement(3);
        c.addElement(8);
        c.addElement(1);
        c.addElement(7);
        CHECK(c.size() == 5);
        CHECK(captureOutput(c) == "[5, 3, 8, 1, 7]");
        CHECK(c.getData() == std::vector<int>{5, 3, 8, 1, 7});

        // Test removeElement
        c.removeElement(3);
        CHECK(c.size() == 4);
        CHECK(captureOutput(c) == "[5, 8, 1, 7]");
        CHECK(c.getData() == std::vector<int>{5, 8, 1, 7});

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(30), std::runtime_error);

        // Test remove all elements
        c.removeElement(5);
        c.removeElement(8);
        c.removeElement(1);
        c.removeElement(7);
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<int>{});

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(1), std::runtime_error);
    }

    SUBCASE("Testing with double") {
        MyContainer<double> c;

        // Test initial state
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<double>{});

        // Test addElement
        c.addElement(5.5);
        c.addElement(3.3);
        c.addElement(8.8);
        c.addElement(1.1);
        c.addElement(7.7);
        CHECK(c.size() == 5);
        CHECK(captureOutput(c) == "[5.5, 3.3, 8.8, 1.1, 7.7]");
        CHECK(c.getData() == std::vector<double>{5.5, 3.3, 8.8, 1.1, 7.7});

        // Test removeElement
        c.removeElement(3.3);
        CHECK(c.size() == 4);
        CHECK(captureOutput(c) == "[5.5, 8.8, 1.1, 7.7]");
        CHECK(c.getData() == std::vector<double>{5.5, 8.8, 1.1, 7.7});

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(37.7), std::runtime_error);

        // Test remove all elements
        c.removeElement(5.5);
        c.removeElement(8.8);
        c.removeElement(1.1);
        c.removeElement(7.7);
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<double>{});

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(1.1), std::runtime_error);
    }

    SUBCASE("Testing with string") {
        MyContainer<std::string> c;

        // Test initial state
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<std::string>{});

        // Test addElement
        c.addElement("apple");
        c.addElement("banana");
        c.addElement("cherry");
        c.addElement("date");
        c.addElement("elderberry");
        CHECK(c.size() == 5);
        CHECK(captureOutput(c) == "[apple, banana, cherry, date, elderberry]");
        CHECK(c.getData() == std::vector<std::string>{"apple", "banana", "cherry", "date", "elderberry"});

        // Test removeElement
        c.removeElement("banana");
        CHECK(c.size() == 4);
        CHECK(captureOutput(c) == "[apple, cherry, date, elderberry]");
        CHECK(c.getData() == std::vector<std::string>{"apple", "cherry", "date", "elderberry"});

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement("fig"), std::runtime_error);

        // Test remove all elements
        c.removeElement("apple");
        c.removeElement("cherry");
        c.removeElement("date");
        c.removeElement("elderberry");
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<std::string>{});

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement("apple"), std::runtime_error);
    }

    SUBCASE("Testing with char") {
        MyContainer<char> c;

        // Test initial state
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<char>{});

        // Test addElement
        c.addElement('a');
        c.addElement('e');
        c.addElement('i');
        c.addElement('o');
        c.addElement('u');
        CHECK(c.size() == 5);
        CHECK(captureOutput(c) == "[a, e, i, o, u]");
        CHECK(c.getData() == std::vector<char>{'a', 'e', 'i', 'o', 'u'});

        // Test removeElement
        c.removeElement('e');
        CHECK(c.size() == 4);
        CHECK(captureOutput(c) == "[a, i, o, u]");
        CHECK(c.getData() == std::vector<char>{'a', 'i', 'o', 'u'});

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement('z'), std::runtime_error);

        // Test remove all elements
        c.removeElement('a');
        c.removeElement('i');
        c.removeElement('o');
        c.removeElement('u');
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<char>{});

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement('a'), std::runtime_error);
    }

    SUBCASE("Testing with float") {
        MyContainer<float> c;

        // Test initial state
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<float>{});

        // Test addElement
        c.addElement(1.1f);
        c.addElement(2.2f);
        c.addElement(3.3f);
        c.addElement(4.4f);
        c.addElement(5.5f);
        CHECK(c.size() == 5);
        CHECK(captureOutput(c) == "[1.1, 2.2, 3.3, 4.4, 5.5]");
        CHECK(c.getData() == std::vector<float>{1.1f, 2.2f, 3.3f, 4.4f, 5.5f});

        // Test removeElement
        c.removeElement(2.2f);
        CHECK(c.size() == 4);
        CHECK(captureOutput(c) == "[1.1, 3.3, 4.4, 5.5]");
        CHECK(c.getData() == std::vector<float>{1.1f, 3.3f, 4.4f, 5.5f});

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(99.9f), std::runtime_error);

        // Test remove all elements
        c.removeElement(1.1f);
        c.removeElement(3.3f);
        c.removeElement(4.4f);
        c.removeElement(5.5f);
        CHECK(c.size() == 0);
        CHECK(captureOutput(c) == "[]");
        CHECK(c.getData() == std::vector<float>{});

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(3.14f), std::runtime_error);
    }
}

TEST_CASE("Iterator advancement: prefix and postfix for all types") {
    SUBCASE("int") {
        MyContainer<int> c;
        for (int i = 1; i <= 5; ++i) c.addElement(i);
        CHECK(c.size() == 5);

        auto it_prefix = c.begin_ascending_order();
        CHECK(*it_prefix == 1);
        CHECK(*(++it_prefix) == 2);

        auto it_postfix = c.begin_ascending_order();
        CHECK(*it_postfix == 1);
        CHECK(*(it_postfix++) == 1);
        CHECK(*it_postfix == 2);

        auto order_prefix = c.begin_order();
        CHECK(*order_prefix == 1);
        CHECK(*(++order_prefix) == 2);

        auto order_postfix = c.begin_order();
        CHECK(*order_postfix == 1);
        CHECK(*(order_postfix++) == 1);
        CHECK(*order_postfix == 2);

        auto desc_prefix = c.begin_descending_order();
        CHECK(*desc_prefix == 5);
        CHECK(*(++desc_prefix) == 4);

        auto desc_postfix = c.begin_descending_order();
        CHECK(*desc_postfix == 5);
        CHECK(*(desc_postfix++) == 5);
        CHECK(*desc_postfix == 4);

        auto side_prefix = c.begin_side_cross_order();
        CHECK(*side_prefix == 1);
        CHECK(*(++side_prefix) == 5);

        auto side_postfix = c.begin_side_cross_order();
        CHECK(*side_postfix == 1);
        CHECK(*(side_postfix++) == 1);
        CHECK(*side_postfix == 5);

        auto rev_prefix = c.begin_reverse_order();
        CHECK(*rev_prefix == 5);
        CHECK(*(++rev_prefix) == 4);

        auto rev_postfix = c.begin_reverse_order();
        CHECK(*rev_postfix == 5);
        CHECK(*(rev_postfix++) == 5);
        CHECK(*rev_postfix == 4);

        auto mid_prefix = c.begin_middle_out_order();
        CHECK(*mid_prefix == 3);
        CHECK(*(++mid_prefix) == 2);

        auto mid_postfix = c.begin_middle_out_order();
        CHECK(*mid_postfix == 3);
        CHECK(*(mid_postfix++) == 3);
        CHECK(*mid_postfix == 2);
    }

    SUBCASE("float") {
        MyContainer<float> c;
        for (float i = 1.1f; i <= 5.1f; i += 1.0f) c.addElement(i);
        CHECK(c.size() == 5);

        auto asc_prefix = c.begin_ascending_order();
        CHECK(*asc_prefix == 1.1f);
        CHECK(*(++asc_prefix) == 2.1f);

        auto asc_postfix = c.begin_ascending_order();
        CHECK(*asc_postfix == 1.1f);
        CHECK(*(asc_postfix++) == 1.1f);
        CHECK(*asc_postfix == 2.1f);

        auto desc_prefix = c.begin_descending_order();
        CHECK(*desc_prefix == 5.1f);
        CHECK(*(++desc_prefix) == 4.1f);

        auto desc_postfix = c.begin_descending_order();
        CHECK(*desc_postfix == 5.1f);
        CHECK(*(desc_postfix++) == 5.1f);
        CHECK(*desc_postfix == 4.1f);

        auto side_prefix = c.begin_side_cross_order();
        CHECK(*side_prefix == 1.1f);
        CHECK(*(++side_prefix) == 5.1f);

        auto side_postfix = c.begin_side_cross_order();
        CHECK(*side_postfix == 1.1f);
        CHECK(*(side_postfix++) == 1.1f);
        CHECK(*side_postfix == 5.1f);

        auto rev_prefix = c.begin_reverse_order();
        CHECK(*rev_prefix == 5.1f);
        CHECK(*(++rev_prefix) == 4.1f);

        auto rev_postfix = c.begin_reverse_order();
        CHECK(*rev_postfix == 5.1f);
        CHECK(*(rev_postfix++) == 5.1f);
        CHECK(*rev_postfix == 4.1f);

        auto mid_prefix = c.begin_middle_out_order();
        CHECK(*mid_prefix == 3.1f);
        CHECK(*(++mid_prefix) == 2.1f);

        auto mid_postfix = c.begin_middle_out_order();
        CHECK(*mid_postfix == 3.1f);
        CHECK(*(mid_postfix++) == 3.1f);
        CHECK(*mid_postfix == 2.1f);
    }

    SUBCASE("double") {
        MyContainer<double> c;
        for (double i = 1.0; i <= 5.0; i += 1.0) c.addElement(i);
        CHECK(c.size() == 5);

        auto asc_prefix = c.begin_ascending_order();
        CHECK(*asc_prefix == 1.0);
        CHECK(*(++asc_prefix) == 2.0);

        auto asc_postfix = c.begin_ascending_order();
        CHECK(*asc_postfix == 1.0);
        CHECK(*(asc_postfix++) == 1.0);
        CHECK(*asc_postfix == 2.0);

        auto order_prefix = c.begin_order();
        CHECK(*order_prefix == 1.0);
        CHECK(*(++order_prefix) == 2.0);

        auto order_postfix = c.begin_order();
        CHECK(*order_postfix == 1.0);
        CHECK(*(order_postfix++) == 1.0);
        CHECK(*order_postfix == 2.0);

        auto desc_prefix = c.begin_descending_order();
        CHECK(*desc_prefix == 5.0);
        CHECK(*(++desc_prefix) == 4.0);

        auto desc_postfix = c.begin_descending_order();
        CHECK(*desc_postfix == 5.0);
        CHECK(*(desc_postfix++) == 5.0);
        CHECK(*desc_postfix == 4.0);

        auto side_prefix = c.begin_side_cross_order();
        CHECK(*side_prefix == 1.0);
        CHECK(*(++side_prefix) == 5.0);

        auto side_postfix = c.begin_side_cross_order();
        CHECK(*side_postfix == 1.0);
        CHECK(*(side_postfix++) == 1.0);
        CHECK(*side_postfix == 5.0);

        auto rev_prefix = c.begin_reverse_order();
        CHECK(*rev_prefix == 5.0);
        CHECK(*(++rev_prefix) == 4.0);

        auto rev_postfix = c.begin_reverse_order();
        CHECK(*rev_postfix == 5.0);
        CHECK(*(rev_postfix++) == 5.0);
        CHECK(*rev_postfix == 4.0);

        auto mid_prefix = c.begin_middle_out_order();
        CHECK(*mid_prefix == 3.0);
        CHECK(*(++mid_prefix) == 2.0);

        auto mid_postfix = c.begin_middle_out_order();
        CHECK(*mid_postfix == 3.0);
        CHECK(*(mid_postfix++) == 3.0);
        CHECK(*mid_postfix == 2.0);
    }

    SUBCASE("string") {
        MyContainer<std::string> c;
        c.addElement("alpha");
        c.addElement("bravo");
        c.addElement("charlie");
        c.addElement("delta");
        c.addElement("echo");
        CHECK(c.size() == 5);

        auto asc_prefix = c.begin_ascending_order();
        CHECK(*asc_prefix == "alpha");
        CHECK(*(++asc_prefix) == "bravo");

        auto asc_postfix = c.begin_ascending_order();
        CHECK(*asc_postfix == "alpha");
        CHECK(*(asc_postfix++) == "alpha");
        CHECK(*asc_postfix == "bravo");

        auto desc_prefix = c.begin_descending_order();
        CHECK(*desc_prefix == "echo");
        CHECK(*(++desc_prefix) == "delta");

        auto desc_postfix = c.begin_descending_order();
        CHECK(*desc_postfix == "echo");
        CHECK(*(desc_postfix++) == "echo");
        CHECK(*desc_postfix == "delta");

        auto side_prefix = c.begin_side_cross_order();
        CHECK(*side_prefix == "alpha");
        CHECK(*(++side_prefix) == "echo");

        auto side_postfix = c.begin_side_cross_order();
        CHECK(*side_postfix == "alpha");
        CHECK(*(side_postfix++) == "alpha");
        CHECK(*side_postfix == "echo");

        auto rev_prefix = c.begin_reverse_order();
        CHECK(*rev_prefix == "echo");
        CHECK(*(++rev_prefix) == "delta");

        auto rev_postfix = c.begin_reverse_order();
        CHECK(*rev_postfix == "echo");
        CHECK(*(rev_postfix++) == "echo");
        CHECK(*rev_postfix == "delta");

        auto mid_prefix = c.begin_middle_out_order();
        CHECK(*mid_prefix == "charlie");
        CHECK(*(++mid_prefix) == "bravo");

        auto mid_postfix = c.begin_middle_out_order();
        CHECK(*mid_postfix == "charlie");
        CHECK(*(mid_postfix++) == "charlie");
        CHECK(*mid_postfix == "bravo");
    }

    SUBCASE("char") {
        MyContainer<char> c;
        c.addElement('a');
        c.addElement('b');
        c.addElement('c');
        c.addElement('d');
        c.addElement('e');
        CHECK(c.size() == 5);

        auto asc_prefix = c.begin_ascending_order();
        CHECK(*asc_prefix == 'a');
        CHECK(*(++asc_prefix) == 'b');

        auto asc_postfix = c.begin_ascending_order();
        CHECK(*asc_postfix == 'a');
        CHECK(*(asc_postfix++) == 'a');
        CHECK(*asc_postfix == 'b');

        auto desc_prefix = c.begin_descending_order();
        CHECK(*desc_prefix == 'e');
        CHECK(*(++desc_prefix) == 'd');

        auto desc_postfix = c.begin_descending_order();
        CHECK(*desc_postfix == 'e');
        CHECK(*(desc_postfix++) == 'e');
        CHECK(*desc_postfix == 'd');

        auto side_prefix = c.begin_side_cross_order();
        CHECK(*side_prefix == 'a');
        CHECK(*(++side_prefix) == 'e');

        auto side_postfix = c.begin_side_cross_order();
        CHECK(*side_postfix == 'a');
        CHECK(*(side_postfix++) == 'a');
        CHECK(*side_postfix == 'e');

        auto rev_prefix = c.begin_reverse_order();
        CHECK(*rev_prefix == 'e');
        CHECK(*(++rev_prefix) == 'd');

        auto rev_postfix = c.begin_reverse_order();
        CHECK(*rev_postfix == 'e');
        CHECK(*(rev_postfix++) == 'e');
        CHECK(*rev_postfix == 'd');

        auto mid_prefix = c.begin_middle_out_order();
        CHECK(*mid_prefix == 'c');
        CHECK(*(++mid_prefix) == 'b');

        auto mid_postfix = c.begin_middle_out_order();
        CHECK(*mid_postfix == 'c');
        CHECK(*(mid_postfix++) == 'c');
        CHECK(*mid_postfix == 'b');
    }
}

TEST_CASE("Iterators with int") {
    SUBCASE("Odd-sized container") {
        MyContainer<int> c;
        c.addElement(4);
        c.addElement(9);
        c.addElement(3);
        c.addElement(11);
        c.addElement(5);

        testIterators(c,
                      vector<int>{3, 4, 5, 9, 11},    // ascending_order
                      vector<int>{11, 9, 5, 4, 3},    // descending_order
                      vector<int>{3, 11, 4, 9, 5},    // side_cross_order
                      vector<int>{5, 11, 3, 9, 4},    // reverse_order
                      vector<int>{4, 9, 3, 11, 5},    // order
                      vector<int>{3, 9, 11, 4, 5});   // middle_out_order
    }

    SUBCASE("Even-sized container") {
        MyContainer<int> c;
        c.addElement(10);
        c.addElement(2);
        c.addElement(7);
        c.addElement(1);
        c.addElement(6);
        c.addElement(12);

        testIterators(c,
                      vector<int>{1, 2, 6, 7, 10, 12},    // ascending_order
                      vector<int>{12, 10, 7, 6, 2, 1},    // descending_order
                      vector<int>{1, 12, 2, 10, 6, 7},    // side_cross_order
                      vector<int>{12, 6, 1, 7, 2, 10},    // reverse_order
                      vector<int>{10, 2, 7, 1, 6, 12},    // order
                      vector<int>{1, 7, 6, 2, 12, 10});   // middle_out_order
    }

    SUBCASE("Empty container") {
        MyContainer<int> c;

        testIterators(c,
                      vector<int>{},    // ascending_order
                      vector<int>{},    // descending_order
                      vector<int>{},    // side_cross_order
                      vector<int>{},    // reverse_order
                      vector<int>{},    // order
                      vector<int>{});   // middle_out_order
    }

    SUBCASE("Single element") {
        MyContainer<int> c;
        c.addElement(42);

        testIterators(c,
                      vector<int>{42},    // ascending_order
                      vector<int>{42},    // descending_order
                      vector<int>{42},    // side_cross_order
                      vector<int>{42},    // reverse_order
                      vector<int>{42},    // order
                      vector<int>{42});   // middle_out_order
    }

    SUBCASE("Duplicate elements") {
        MyContainer<int> c;
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);
        c.addElement(3);

        testIterators(c,
                      vector<int>{3, 3, 3, 3, 3},    // ascending_order
                      vector<int>{3, 3, 3, 3, 3},    // descending_order
                      vector<int>{3, 3, 3, 3, 3},    // side_cross_order
                      vector<int>{3, 3, 3, 3, 3},    // reverse_order
                      vector<int>{3, 3, 3, 3, 3},    // order
                      vector<int>{3, 3, 3, 3, 3});   // middle_out_order
    }

    SUBCASE("Large container") {
        MyContainer<int> c;
        vector<int> insertion_order;
        for (int i = 0; i < 10; ++i) {
            int val = i % 10;
            c.addElement(val);
            insertion_order.push_back(val);
        }
        CHECK(c.size() == 10);

        vector<int> expected_asc = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> expected_desc = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        vector<int> expected_side = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
        vector<int> expected_rev = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        vector<int> expected_mid = {5, 4, 6, 3, 7, 2, 8, 1, 9, 0};

        testIterators(c,
                      expected_asc,           // ascending_order
                      expected_desc,          // descending_order
                      expected_side,          // side_cross_order
                      expected_rev,           // reverse_order
                      insertion_order,        // order
                      expected_mid);          // middle_out_order
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

        testIterators(c,
                      vector<string>{"apple", "banana", "cherry", "date", "fig"},    // ascending_order
                      vector<string>{"fig", "date", "cherry", "banana", "apple"},    // descending_order
                      vector<string>{"apple", "fig", "banana", "date", "cherry"},    // side_cross_order
                      vector<string>{"fig", "date", "cherry", "apple", "banana"},    // reverse_order
                      vector<string>{"banana", "apple", "cherry", "date", "fig"},    // order
                      vector<string>{"cherry", "apple", "date", "banana", "fig"});   // middle_out_order
    }

    SUBCASE("Even-sized container") {
        MyContainer<string> c;
        c.addElement("grape");
        c.addElement("apple");
        c.addElement("banana");
        c.addElement("cherry");
        c.addElement("date");
        c.addElement("fig");

        testIterators(c,
                      vector<string>{"apple", "banana", "cherry", "date", "fig", "grape"},    // ascending_order
                      vector<string>{"grape", "fig", "date", "cherry", "banana", "apple"},    // descending_order
                      vector<string>{"apple", "grape", "banana", "fig", "cherry", "date"},    // side_cross_order
                      vector<string>{"fig", "date", "cherry", "banana", "apple", "grape"},    // reverse_order
                      vector<string>{"grape", "apple", "banana", "cherry", "date", "fig"},    // order
                      vector<string>{"cherry", "banana", "date", "apple", "fig", "grape"});   // middle_out_order
    }

    SUBCASE("Empty container") {
        MyContainer<string> c;

        testIterators(c,
                      vector<string>{},    // ascending_order
                      vector<string>{},    // descending_order
                      vector<string>{},    // side_cross_order
                      vector<string>{},    // reverse_order
                      vector<string>{},    // order
                      vector<string>{});   // middle_out_order
    }

    SUBCASE("Single element") {
        MyContainer<string> c;
        c.addElement("hello");

        testIterators(c,
                      vector<string>{"hello"},    // ascending_order
                      vector<string>{"hello"},    // descending_order
                      vector<string>{"hello"},    // side_cross_order
                      vector<string>{"hello"},    // reverse_order
                      vector<string>{"hello"},    // order
                      vector<string>{"hello"});   // middle_out_order
    }

    SUBCASE("Duplicate elements") {
        MyContainer<string> c;
        c.addElement("apple");
        c.addElement("apple");
        c.addElement("apple");
        c.addElement("apple");
        c.addElement("apple");

        testIterators(c,
                      vector<string>{"apple", "apple", "apple", "apple", "apple"},    // ascending_order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"},    // descending_order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"},    // side_cross_order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"},    // reverse_order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"},    // order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"});   // middle_out_order
    }

    SUBCASE("Large container") {
        MyContainer<string> c;
        vector<string> insertion_order;
        for (int i = 0; i < 10; ++i) {
            string val = "item" + to_string(i % 10);
            c.addElement(val);
            insertion_order.push_back(val);
        }
        CHECK(c.size() == 10);

        vector<string> expected_asc = {"item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9"};
        vector<string> expected_desc = {"item9", "item8", "item7", "item6", "item5", "item4", "item3", "item2", "item1", "item0"};
        vector<string> expected_side = {"item0", "item9", "item1", "item8", "item2", "item7", "item3", "item6", "item4", "item5"};
        vector<string> expected_rev = {"item9", "item8", "item7", "item6", "item5", "item4", "item3", "item2", "item1", "item0"};
        vector<string> expected_mid = {"item5", "item4", "item6", "item3", "item7", "item2", "item8", "item1", "item9", "item0"};

        testIterators(c,
                      expected_asc,           // ascending_order
                      expected_desc,          // descending_order
                      expected_side,          // side_cross_order
                      expected_rev,           // reverse_order
                      insertion_order,        // order
                      expected_mid);          // middle_out_order
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

        testIterators(c,
                      vector<double>{0.5, 1.41, 2.72, 3.14, 5.0},    // ascending_order
                      vector<double>{5.0, 3.14, 2.72, 1.41, 0.5},    // descending_order
                      vector<double>{0.5, 5.0, 1.41, 3.14, 2.72},    // side_cross_order
                      vector<double>{0.5, 5.0, 2.72, 1.41, 3.14},    // reverse_order
                      vector<double>{3.14, 1.41, 2.72, 5.0, 0.5},    // order
                      vector<double>{2.72, 1.41, 5.0, 3.14, 0.5});   // middle_out_order
    }

    SUBCASE("Even-sized container") {
        MyContainer<double> c;
        c.addElement(1.0);
        c.addElement(2.0);
        c.addElement(3.0);
        c.addElement(4.0);
        c.addElement(5.0);
        c.addElement(6.0);

        testIterators(c,
                      vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0},    // ascending_order
                      vector<double>{6.0, 5.0, 4.0, 3.0, 2.0, 1.0},    // descending_order
                      vector<double>{1.0, 6.0, 2.0, 5.0, 3.0, 4.0},    // side_cross_order
                      vector<double>{6.0, 5.0, 4.0, 3.0, 2.0, 1.0},    // reverse_order
                      vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0},    // order
                      vector<double>{4.0, 3.0, 5.0, 2.0, 6.0, 1.0});   // middle_out_order
    }

    SUBCASE("Empty container") {
        MyContainer<double> c;

        testIterators(c,
                      vector<double>{},    // ascending_order
                      vector<double>{},    // descending_order
                      vector<double>{},    // side_cross_order
                      vector<double>{},    // reverse_order
                      vector<double>{},    // order
                      vector<double>{});   // middle_out_order
    }

    SUBCASE("Single element") {
        MyContainer<double> c;
        c.addElement(1.23);

        testIterators(c,
                      vector<double>{1.23},    // ascending_order
                      vector<double>{1.23},    // descending_order
                      vector<double>{1.23},    // side_cross_order
                      vector<double>{1.23},    // reverse_order
                      vector<double>{1.23},    // order
                      vector<double>{1.23});   // middle_out_order
    }

    SUBCASE("Duplicate elements") {
        MyContainer<double> c;
        c.addElement(2.5);
        c.addElement(2.5);
        c.addElement(2.5);
        c.addElement(2.5);
        c.addElement(2.5);

        testIterators(c,
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5},    // ascending_order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5},    // descending_order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5},    // side_cross_order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5},    // reverse_order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5},    // order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5});   // middle_out_order
    }

    SUBCASE("Large container") {
        MyContainer<double> c;
        vector<double> insertion_order;
        for (int i = 0; i < 10; ++i) {
            double val = static_cast<double>(i % 10) + 0.5;
            c.addElement(val);
            insertion_order.push_back(val);
        }
        CHECK(c.size() == 10);

        vector<double> expected_asc = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5};
        vector<double> expected_desc = {9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5};
        vector<double> expected_side = {0.5, 9.5, 1.5, 8.5, 2.5, 7.5, 3.5, 6.5, 4.5, 5.5};
        vector<double> expected_rev = {9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5};
        vector<double> expected_mid = {5.5, 4.5, 6.5, 3.5, 7.5, 2.5, 8.5, 1.5, 9.5, 0.5};

        testIterators(c,
                      expected_asc,           // ascending_order
                      expected_desc,          // descending_order
                      expected_side,          // side_cross_order
                      expected_rev,           // reverse_order
                      insertion_order,        // order
                      expected_mid);          // middle_out_order
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

        testIterators(c,
                      vector<char>{'a', 'b', 'c', 'd', 'e'},    // ascending_order
                      vector<char>{'e', 'd', 'c', 'b', 'a'},    // descending_order
                      vector<char>{'a', 'e', 'b', 'd', 'c'},    // side_cross_order
                      vector<char>{'d', 'b', 'c', 'a', 'e'},    // reverse_order
                      vector<char>{'e', 'a', 'c', 'b', 'd'},    // order
                      vector<char>{'c', 'a', 'b', 'e', 'd'});   // middle_out_order
    }

    SUBCASE("Even-sized container") {
        MyContainer<char> c;
        c.addElement('a');
        c.addElement('b');
        c.addElement('c');
        c.addElement('d');
        c.addElement('e');
        c.addElement('f');

        testIterators(c,
                      vector<char>{'a', 'b', 'c', 'd', 'e', 'f'},    // ascending_order
                      vector<char>{'f', 'e', 'd', 'c', 'b', 'a'},    // descending_order
                      vector<char>{'a', 'f', 'b', 'e', 'c', 'd'},    // side_cross_order
                      vector<char>{'f', 'e', 'd', 'c', 'b', 'a'},    // reverse_order
                      vector<char>{'a', 'b', 'c', 'd', 'e', 'f'},    // order
                      vector<char>{'d', 'c', 'e', 'b', 'f', 'a'});   // middle_out_order
    }

    SUBCASE("Empty container") {
        MyContainer<char> c;

        testIterators(c,
                      vector<char>{},    // ascending_order
                      vector<char>{},    // descending_order
                      vector<char>{},    // side_cross_order
                      vector<char>{},    // reverse_order
                      vector<char>{},    // order
                      vector<char>{});   // middle_out_order
    }

    SUBCASE("Single element") {
        MyContainer<char> c;
        c.addElement('x');

        testIterators(c,
                      vector<char>{'x'},    // ascending_order
                      vector<char>{'x'},    // descending_order
                      vector<char>{'x'},    // side_cross_order
                      vector<char>{'x'},    // reverse_order
                      vector<char>{'x'},    // order
                      vector<char>{'x'});   // middle_out_order
    }

    SUBCASE("Duplicate elements") {
        MyContainer<char> c;
        c.addElement('a');
        c.addElement('a');
        c.addElement('a');
        c.addElement('a');
        c.addElement('a');

        testIterators(c,
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // ascending_order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // descending_order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // side_cross_order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // reverse_order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // order
                      vector<char>{'a', 'a', 'a', 'a', 'a'});   // middle_out_order
    }

    SUBCASE("Large container") {
        MyContainer<char> c;
        vector<char> insertion_order;
        for (int i = 0; i < 10; ++i) {
            char val = static_cast<char>('a' + (i % 10));
            c.addElement(val);
            insertion_order.push_back(val);
        }
        CHECK(c.size() == 10);

        vector<char> expected_asc = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        vector<char> expected_desc = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
        vector<char> expected_side = {'a', 'j', 'b', 'i', 'c', 'h', 'd', 'g', 'e', 'f'};
        vector<char> expected_rev = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
        vector<char> expected_mid = {'f', 'e', 'g', 'd', 'h', 'c', 'i', 'b', 'j', 'a'};

        testIterators(c,
                      expected_asc,           // ascending_order
                      expected_desc,          // descending_order
                      expected_side,          // side_cross_order
                      expected_rev,           // reverse_order
                      insertion_order,        // order
                      expected_mid);          // middle_out_order
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

        testIterators(c,
                      vector<float>{0.5f, 1.2f, 2.3f, 3.1f, 4.4f},    // ascending_order
                      vector<float>{4.4f, 3.1f, 2.3f, 1.2f, 0.5f},    // descending_order
                      vector<float>{0.5f, 4.4f, 1.2f, 3.1f, 2.3f},    // side_cross_order
                      vector<float>{0.5f, 4.4f, 2.3f, 1.2f, 3.1f},    // reverse_order
                      vector<float>{3.1f, 1.2f, 2.3f, 4.4f, 0.5f},    // order
                      vector<float>{2.3f, 1.2f, 4.4f, 3.1f, 0.5f});   // middle_out_order
    }

    SUBCASE("Even-sized container") {
        MyContainer<float> c;
        c.addElement(1.0f);
        c.addElement(2.0f);
        c.addElement(3.0f);
        c.addElement(4.0f);
        c.addElement(5.0f);
        c.addElement(6.0f);

        testIterators(c,
                      vector<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},    // ascending_order
                      vector<float>{6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f},    // descending_order
                      vector<float>{1.0f, 6.0f, 2.0f, 5.0f, 3.0f, 4.0f},    // side_cross_order
                      vector<float>{6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f},    // reverse_order
                      vector<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},    // order
                      vector<float>{4.0f, 3.0f, 5.0f, 2.0f, 6.0f, 1.0f});   // middle_out_order
    }

    SUBCASE("Empty container") {
        MyContainer<float> c;

        testIterators(c,
                      vector<float>{},    // ascending_order
                      vector<float>{},    // descending_order
                      vector<float>{},    // side_cross_order
                      vector<float>{},    // reverse_order
                      vector<float>{},    // order
                      vector<float>{});   // middle_out_order
    }

    SUBCASE("Single element") {
        MyContainer<float> c;
        c.addElement(1.5f);

        testIterators(c,
                      vector<float>{1.5f},    // ascending_order
                      vector<float>{1.5f},    // descending_order
                      vector<float>{1.5f},    // side_cross_order
                      vector<float>{1.5f},    // reverse_order
                      vector<float>{1.5f},    // order
                      vector<float>{1.5f});   // middle_out_order
    }

    SUBCASE("Duplicate elements") {
        MyContainer<float> c;
        c.addElement(2.5f);
        c.addElement(2.5f);
        c.addElement(2.5f);
        c.addElement(2.5f);
        c.addElement(2.5f);

        testIterators(c,
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // ascending_order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // descending_order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // side_cross_order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // reverse_order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f});   // middle_out_order
    }

    SUBCASE("Large container") {
        MyContainer<float> c;
        vector<float> insertion_order;
        for (int i = 0; i < 10; ++i) {
            float val = static_cast<float>(i % 10) + 0.1f;
            c.addElement(val);
            insertion_order.push_back(val);
        }
        CHECK(c.size() == 10);

        vector<float> expected_asc = {0.1f, 1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f, 9.1f};
        vector<float> expected_desc = {9.1f, 8.1f, 7.1f, 6.1f, 5.1f, 4.1f, 3.1f, 2.1f, 1.1f, 0.1f};
        vector<float> expected_side = {0.1f, 9.1f, 1.1f, 8.1f, 2.1f, 7.1f, 3.1f, 6.1f, 4.1f, 5.1f};
        vector<float> expected_rev = {9.1f, 8.1f, 7.1f, 6.1f, 5.1f, 4.1f, 3.1f, 2.1f, 1.1f, 0.1f};
        vector<float> expected_mid = {5.1f, 4.1f, 6.1f, 3.1f, 7.1f, 2.1f, 8.1f, 1.1f, 9.1f, 0.1f};

        testIterators(c,
                      expected_asc,           // ascending_order
                      expected_desc,          // descending_order
                      expected_side,          // side_cross_order
                      expected_rev,           // reverse_order
                      insertion_order,        // order
                      expected_mid);          // middle_out_order
    }
}