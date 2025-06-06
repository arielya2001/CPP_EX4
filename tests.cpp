/*
Mail - ariel.yaacobi@msmail.ariel.ac.il
*/
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN  // Configures doctest to include main function

#include "doctest.h"  // Includes the doctest testing framework
#include "MyContainer.hpp"  // Includes the MyContainer class header
#include <vector>  // Includes vector container from STL
#include <string>  // Includes string class from STL
#include <sstream>  // Includes string stream for output capture

using namespace ariel;  // Uses the ariel namespace
using namespace std;  // Uses the standard namespace

// Helper function to capture container output via operator<<
template<typename T>  // Template for generic type T
string captureOutput(const MyContainer<T>& c) {  // Captures output of MyContainer
    ostringstream oss;  // Creates output string stream
    oss << c;  // Streams container content to oss
    return oss.str();  // Returns the captured string
}

// Helper function to test all iterators for a given container
template<typename T>  // Template for generic type T
void testIterators(const MyContainer<T>& c,  // Tests iterators of MyContainer
                   const vector<T>& expected_asc,  // Expected ascending order
                   const vector<T>& expected_desc,  // Expected descending order
                   const vector<T>& expected_side,  // Expected side cross order
                   const vector<T>& expected_rev,  // Expected reverse order
                   const vector<T>& expected_order,  // Expected insertion order
                   const vector<T>& expected_mid) {  // Expected middle out order
    vector<T> result;  // Stores iterator results

    SUBCASE("Ascending Order") {  // Tests ascending order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {  // Iterates in ascending order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_asc);  // Verifies ascending order
        auto asc_end_it = c.end_ascending_order();  // Gets end iterator
        CHECK_THROWS_AS(*asc_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++asc_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(asc_end_it++, out_of_range);  // Tests postfix increment of end
    }

    SUBCASE("Descending Order") {  // Tests descending order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {  // Iterates in descending order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_desc);  // Verifies descending order
        auto desc_end_it = c.end_descending_order();  // Gets end iterator
        CHECK_THROWS_AS(*desc_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++desc_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(desc_end_it++, out_of_range);  // Tests postfix increment of end
    }

    SUBCASE("Side Cross Order") {  // Tests side cross order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {  // Iterates in side cross order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_side);  // Verifies side cross order
        auto side_end_it = c.end_side_cross_order();  // Gets end iterator
        CHECK_THROWS_AS(*side_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++side_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(side_end_it++, out_of_range);  // Tests postfix increment of end
    }

    SUBCASE("Reverse Order") {  // Tests reverse order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {  // Iterates in reverse order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_rev);  // Verifies reverse order
        auto rev_end_it = c.end_reverse_order();  // Gets end iterator
        CHECK_THROWS_AS(*rev_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++rev_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(rev_end_it++, out_of_range);  // Tests postfix increment of end
    }

    SUBCASE("Insertion Order") {  // Tests insertion order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_order(); it != c.end_order(); ++it) {  // Iterates in insertion order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_order);  // Verifies insertion order
        auto order_end_it = c.end_order();  // Gets end iterator
        CHECK_THROWS_AS(*order_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++order_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(order_end_it++, out_of_range);  // Tests postfix increment of end
    }

    SUBCASE("Middle Out Order") {  // Tests middle out order iterator
        result.clear();  // Clears result vector
        for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {  // Iterates in middle out order
            result.push_back(*it);  // Adds element to result
        }
        CHECK(result == expected_mid);  // Verifies middle out order
        auto mid_end_it = c.end_middle_out_order();  // Gets end iterator
        CHECK_THROWS_AS(*mid_end_it, out_of_range);  // Tests dereference of end
        CHECK_THROWS_AS(++mid_end_it, out_of_range);  // Tests prefix increment of end
        CHECK_THROWS_AS(mid_end_it++, out_of_range);  // Tests postfix increment of end
    }
}

// Tests basic operations (add, remove, size, output) for different data types
// This test case verifies the core functionality of MyContainer, including
// adding elements, removing elements, checking size, and string representation
// across various data types (int, double, string, char, float).
TEST_CASE("MyContainer operations with different types") {  // Tests operations with various types
    SUBCASE("Testing with int") {  // Tests int container
        MyContainer<int> c;  // Creates int container

        // Test initial state
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<int>{});  // Verifies empty data

        // Test addElement
        c.addElement(5);  // Adds 5 to container
        c.addElement(3);  // Adds 3 to container
        c.addElement(8);  // Adds 8 to container
        c.addElement(1);  // Adds 1 to container
        c.addElement(7);  // Adds 7 to container
        CHECK(c.size() == 5);  // Verifies size
        CHECK(captureOutput(c) == "[5, 3, 8, 1, 7]");  // Verifies output
        CHECK(c.getData() == std::vector<int>{5, 3, 8, 1, 7});  // Verifies data

        // Test removeElement
        c.removeElement(3);  // Removes 3 from container
        CHECK(c.size() == 4);  // Verifies size
        CHECK(captureOutput(c) == "[5, 8, 1, 7]");  // Verifies output
        CHECK(c.getData() == std::vector<int>{5, 8, 1, 7});  // Verifies data

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(30), std::runtime_error);  // Tests invalid removal

        // Test remove all elements
        c.removeElement(5);  // Removes 5 from container
        c.removeElement(8);  // Removes 8 from container
        c.removeElement(1);  // Removes 1 from container
        c.removeElement(7);  // Removes 7 from container
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<int>{});  // Verifies empty data

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(1), std::runtime_error);  // Tests removal from empty container
    }

    SUBCASE("Testing with double") {  // Tests double container
        MyContainer<double> c;  // Creates double container

        // Test initial state
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<double>{});  // Verifies empty data

        // Test addElement
        c.addElement(5.5);  // Adds 5.5 to container
        c.addElement(3.3);  // Adds 3.3 to container
        c.addElement(8.8);  // Adds 8.8 to container
        c.addElement(1.1);  // Adds 1.1 to container
        c.addElement(7.7);  // Adds 7.7 to container
        CHECK(c.size() == 5);  // Verifies size
        CHECK(captureOutput(c) == "[5.5, 3.3, 8.8, 1.1, 7.7]");  // Verifies output
        CHECK(c.getData() == std::vector<double>{5.5, 3.3, 8.8, 1.1, 7.7});  // Verifies data

        // Test removeElement
        c.removeElement(3.3);  // Removes 3.3 from container
        CHECK(c.size() == 4);  // Verifies size
        CHECK(captureOutput(c) == "[5.5, 8.8, 1.1, 7.7]");  // Verifies output
        CHECK(c.getData() == std::vector<double>{5.5, 8.8, 1.1, 7.7});  // Verifies data

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(37.7), std::runtime_error);  // Tests invalid removal

        // Test remove all elements
        c.removeElement(5.5);  // Removes 5.5 from container
        c.removeElement(8.8);  // Removes 8.8 from container
        c.removeElement(1.1);  // Removes 1.1 from container
        c.removeElement(7.7);  // Removes 7.7 from container
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<double>{});  // Verifies empty data

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(1.1), std::runtime_error);  // Tests removal from empty container
    }

    SUBCASE("Testing with string") {  // Tests string container
        MyContainer<std::string> c;  // Creates string container

        // Test initial state
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<std::string>{});  // Verifies empty data

        // Test addElement
        c.addElement("apple");  // Adds "apple" to container
        c.addElement("banana");  // Adds "banana" to container
        c.addElement("cherry");  // Adds "cherry" to container
        c.addElement("date");  // Adds "date" to container
        c.addElement("elderberry");  // Adds "elderberry" to container
        CHECK(c.size() == 5);  // Verifies size
        CHECK(captureOutput(c) == "[apple, banana, cherry, date, elderberry]");  // Verifies output
        CHECK(c.getData() == std::vector<std::string>{"apple", "banana", "cherry", "date", "elderberry"});  // Verifies data

        // Test removeElement
        c.removeElement("banana");  // Removes "banana" from container
        CHECK(c.size() == 4);  // Verifies size
        CHECK(captureOutput(c) == "[apple, cherry, date, elderberry]");  // Verifies output
        CHECK(c.getData() == std::vector<std::string>{"apple", "cherry", "date", "elderberry"});  // Verifies data

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement("fig"), std::runtime_error);  // Tests invalid removal

        // Test remove all elements
        c.removeElement("apple");  // Removes "apple" from container
        c.removeElement("cherry");  // Removes "cherry" from container
        c.removeElement("date");  // Removes "date" from container
        c.removeElement("elderberry");  // Removes "elderberry" from container
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<std::string>{});  // Verifies empty data

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement("apple"), std::runtime_error);  // Tests removal from empty container
    }

    SUBCASE("Testing with char") {  // Tests char container
        MyContainer<char> c;  // Creates char container

        // Test initial state
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<char>{});  // Verifies empty data

        // Test addElement
        c.addElement('a');  // Adds 'a' to container
        c.addElement('e');  // Adds 'e' to container
        c.addElement('i');  // Adds 'i' to container
        c.addElement('o');  // Adds 'o' to container
        c.addElement('u');  // Adds 'u' to container
        CHECK(c.size() == 5);  // Verifies size
        CHECK(captureOutput(c) == "[a, e, i, o, u]");  // Verifies output
        CHECK(c.getData() == std::vector<char>{'a', 'e', 'i', 'o', 'u'});  // Verifies data

        // Test removeElement
        c.removeElement('e');  // Removes 'e' from container
        CHECK(c.size() == 4);  // Verifies size
        CHECK(captureOutput(c) == "[a, i, o, u]");  // Verifies output
        CHECK(c.getData() == std::vector<char>{'a', 'i', 'o', 'u'});  // Verifies data

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement('z'), std::runtime_error);  // Tests invalid removal

        // Test remove all elements
        c.removeElement('a');  // Removes 'a' from container
        c.removeElement('i');  // Removes 'i' from container
        c.removeElement('o');  // Removes 'o' from container
        c.removeElement('u');  // Removes 'u' from container
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<char>{});  // Verifies empty data

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement('a'), std::runtime_error);  // Tests removal from empty container
    }

    SUBCASE("Testing with float") {  // Tests float container
        MyContainer<float> c;  // Creates float container

        // Test initial state
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<float>{});  // Verifies empty data

        // Test addElement
        c.addElement(1.1f);  // Adds 1.1f to container
        c.addElement(2.2f);  // Adds 2.2f to container
        c.addElement(3.3f);  // Adds 3.3f to container
        c.addElement(4.4f);  // Adds 4.4f to container
        c.addElement(5.5f);  // Adds 5.5f to container
        CHECK(c.size() == 5);  // Verifies size
        CHECK(captureOutput(c) == "[1.1, 2.2, 3.3, 4.4, 5.5]");  // Verifies output
        CHECK(c.getData() == std::vector<float>{1.1f, 2.2f, 3.3f, 4.4f, 5.5f});  // Verifies data

        // Test removeElement
        c.removeElement(2.2f);  // Removes 2.2f from container
        CHECK(c.size() == 4);  // Verifies size
        CHECK(captureOutput(c) == "[1.1, 3.3, 4.4, 5.5]");  // Verifies output
        CHECK(c.getData() == std::vector<float>{1.1f, 3.3f, 4.4f, 5.5f});  // Verifies data

        // Test removeElement with non-existent element
        CHECK_THROWS_AS(c.removeElement(99.9f), std::runtime_error);  // Tests invalid removal

        // Test remove all elements
        c.removeElement(1.1f);  // Removes 1.1f from container
        c.removeElement(3.3f);  // Removes 3.3f from container
        c.removeElement(4.4f);  // Removes 4.4f from container
        c.removeElement(5.5f);  // Removes 5.5f from container
        CHECK(c.size() == 0);  // Verifies empty size
        CHECK(captureOutput(c) == "[]");  // Verifies empty output
        CHECK(c.getData() == std::vector<float>{});  // Verifies empty data

        // Test remove from empty container
        CHECK_THROWS_AS(c.removeElement(3.14f), std::runtime_error);  // Tests removal from empty container
    }
}

// Tests iterator prefix and postfix advancement
// This test case checks the behavior of prefix and postfix increment operators
// for all iterator types across different data types, ensuring correct
// advancement and value access in various traversal orders.
TEST_CASE("Iterator advancement: prefix and postfix for all types"){
    // Tests iterator increment operations
    SUBCASE("int") {  // Tests integer iterator operations
        MyContainer<int> c;  // Creates integer container
        for (int i = 1; i <= 5; ++i) c.addElement(i);  // Adds elements 1 to 5
        CHECK(c.size() == 5);  // Verifies container size

        auto it_prefix = c.begin_ascending_order();  // Gets ascending order iterator
        CHECK(*it_prefix == 1);  // Verifies first element
        CHECK(*(++it_prefix) == 2);  // Verifies next element after prefix increment

        auto it_postfix = c.begin_ascending_order();  // Gets another ascending order iterator
        CHECK(*it_postfix == 1);  // Verifies first element
        CHECK(*(it_postfix++) == 1);  // Verifies value before postfix increment
        CHECK(*it_postfix == 2);  // Verifies value after postfix increment

        auto order_prefix = c.begin_order();  // Gets insertion order iterator
        CHECK(*order_prefix == 1);  // Verifies first element
        CHECK(*(++order_prefix) == 2);  // Verifies next element after prefix increment

        auto order_postfix = c.begin_order();  // Gets another insertion order iterator
        CHECK(*order_postfix == 1);  // Verifies first element
        CHECK(*(order_postfix++) == 1);  // Verifies value before postfix increment
        CHECK(*order_postfix == 2);  // Verifies value after postfix increment

        auto desc_prefix = c.begin_descending_order();  // Gets descending order iterator
        CHECK(*desc_prefix == 5);  // Verifies first element
        CHECK(*(++desc_prefix) == 4);  // Verifies next element after prefix increment

        auto desc_postfix = c.begin_descending_order();  // Gets another descending order iterator
        CHECK(*desc_postfix == 5);  // Verifies first element
        CHECK(*(desc_postfix++) == 5);  // Verifies value before postfix increment
        CHECK(*desc_postfix == 4);  // Verifies value after postfix

        auto side_prefix = c.begin_side_cross_order();  // Gets side cross order iterator
        CHECK(*side_prefix == 1);  // Verifies first element
        CHECK(*(++side_prefix) == 5);  // Verifies next element after prefix increment

        auto side_postfix = c.begin_side_cross_order();  // Gets another side cross order iterator
        CHECK(*side_postfix == 1);  // Verifies first element
        CHECK(*(side_postfix++) == 1);  // Verifies value before postfix increment
        CHECK(*side_postfix == 5);  // Verifies value after postfix increment

        auto rev_prefix = c.begin_reverse_order();  // Gets reverse order iterator
        CHECK(*rev_prefix == 5);  // Verifies first element
        CHECK(*(++rev_prefix) == 4);  // Verifies next element after prefix increment

        auto rev_postfix = c.begin_reverse_order();  // Gets another reverse order iterator
        CHECK(*rev_postfix == 5);  // Verifies first element
        CHECK(*(rev_postfix++) == 5);  // Verifies value before postfix increment
        CHECK(*rev_postfix == 4);  // Verifies value after postfix increment

        auto mid_prefix = c.begin_middle_out_order();  // Gets middle out order iterator
        CHECK(*mid_prefix == 3);  // Verifies first element
        CHECK(*(++mid_prefix) == 2);  // Verifies next element after prefix increment

        auto mid_postfix = c.begin_middle_out_order();  // Gets another middle out order iterator
        CHECK(*mid_postfix == 3);  // Verifies first element
        CHECK(*(mid_postfix++) == 3);  // Verifies value before postfix increment
        CHECK(*mid_postfix == 2);  // Verifies value after postfix increment
    }

    SUBCASE("float") {  // Tests float iterator operations
        MyContainer<float> c;  // Creates float container
        for (float i = 1.1f; i <= 5.1f; i += 1.0f) c.addElement(i);  // Adds floats 1.1 to 5.1
        CHECK(c.size() == 5);  // Verifies container size

        auto asc_prefix = c.begin_ascending_order();  // Gets ascending order iterator
        CHECK(*asc_prefix == 1.1f);  // Verifies first element
        CHECK(*(++asc_prefix) == 2.1f);  // Verifies next element after prefix increment

        auto asc_postfix = c.begin_ascending_order();  // Gets another ascending order iterator
        CHECK(*asc_postfix == 1.1f);  // Verifies first element
        CHECK(*(asc_postfix++) == 1.1f);  // Verifies value before postfix increment
        CHECK(*asc_postfix == 2.1f);  // Verifies value after postfix increment

        auto desc_prefix = c.begin_descending_order();  // Gets descending order iterator
        CHECK(*desc_prefix == 5.1f);  // Verifies first element
        CHECK(*(++desc_prefix) == 4.1f);  // Verifies next element after prefix increment

        auto desc_postfix = c.begin_descending_order();  // Gets another descending order iterator
        CHECK(*desc_postfix == 5.1f);  // Verifies first element
        CHECK(*(desc_postfix++) == 5.1f);  // Verifies value before postfix increment
        CHECK(*desc_postfix == 4.1f);  // Verifies value after postfix increment

        auto side_prefix = c.begin_side_cross_order();  // Gets side cross order iterator
        CHECK(*side_prefix == 1.1f);  // Verifies first element
        CHECK(*(++side_prefix) == 5.1f);  // Verifies next element after prefix increment

        auto side_postfix = c.begin_side_cross_order();  // Gets another side cross order iterator
        CHECK(*side_postfix == 1.1f);  // Verifies first element
        CHECK(*(side_postfix++) == 1.1f);  // Verifies value before postfix increment
        CHECK(*side_postfix == 5.1f);  // Verifies value after postfix increment

        auto rev_prefix = c.begin_reverse_order();  // Gets reverse order iterator
        CHECK(*rev_prefix == 5.1f);  // Verifies first element
        CHECK(*(++rev_prefix) == 4.1f);  // Verifies next element after prefix increment

        auto rev_postfix = c.begin_reverse_order();  // Gets another reverse order iterator
        CHECK(*rev_postfix == 5.1f);  // Verifies first element
        CHECK(*(rev_postfix++) == 5.1f);  // Verifies value before postfix increment
        CHECK(*rev_postfix == 4.1f);  // Verifies value after postfix increment

        auto mid_prefix = c.begin_middle_out_order();  // Gets middle out order iterator
        CHECK(*mid_prefix == 3.1f);  // Verifies first element
        CHECK(*(++mid_prefix) == 2.1f);  // Verifies next element after prefix increment

        auto mid_postfix = c.begin_middle_out_order();  // Gets another middle iterator
        CHECK(*mid_postfix == 3.1f);  // Verifies first element
        CHECK(*(mid_postfix++) == 3.1f); // Verifies value before postfix increment
        CHECK(*mid_postfix == 2.1f); // Verifies value after postfix increment
    }

    SUBCASE("double") {  // Tests double iterator operations
        MyContainer<double> c;  // Creates double container
        for (double i = 1.0; i <= 5.0; i += 1.0) c.addElement(i);  // Adds doubles 1.0 to 5.0
        CHECK(c.size() == 5);  // Verifies container size

        auto asc_prefix = c.begin_ascending_order();  // Gets ascending order iterator
        CHECK(*asc_prefix == 1.0);  // Verifies first element
        CHECK(*(++asc_prefix) == 2.0);  // Verifies next element after prefix increment

        auto asc_postfix = c.begin_ascending_order();  // Gets another ascending order iterator
        CHECK(*asc_postfix == 1.0);  // Verifies first element
        CHECK(*(asc_postfix++) == 1.0);  // Verifies value before postfix
        CHECK(*asc_postfix == 2.0);  // Verifies value after postfix increment

        auto order_prefix = c.begin_order();  // Gets insertion order iterator
        CHECK(*order_prefix == 1.0);  // Verifies first element
        CHECK(*(++order_prefix) == 2.0);  // Verifies next element after prefix increment

        auto order_postfix = c.begin_order();  // Gets another insertion order iterator
        CHECK(*order_postfix == 1.0);  // Verifies first element
        CHECK(*(order_postfix++) == 1.0);  // Verifies value before postfix increment
        CHECK(*order_postfix == 2.0);  // Verifies value after postfix increment

        auto desc_prefix = c.begin_descending_order();  // Gets descending order iterator
        CHECK(*desc_prefix == 5.0);  // Verifies first element
        CHECK(*(++desc_prefix) == 4.0);  // Verifies next element after prefix increment

        auto desc_postfix = c.begin_descending_order();  // Gets another descending order iterator
        CHECK(*desc_postfix == 5.0);  // Verifies first element
        CHECK(*(desc_postfix++) == 5.0);  // Verifies value before postfix increment
        CHECK(*desc_postfix == 4.0);  // Verifies value after postfix increment

        auto side_prefix = c.begin_side_cross_order();  // Gets side cross order iterator
        CHECK(*side_prefix == 1.0);  // Verifies first element
        CHECK(*(++side_prefix) == 5.0);  // Verifies next element after prefix increment

        auto side_postfix = c.begin_side_cross_order();  // Gets another side cross order iterator
        CHECK(*side_postfix == 1.0);  // Verifies first element
        CHECK(*(side_postfix++) == 1.0);  // Verifies value before postfix increment
        CHECK(*side_postfix == 5.0);  // Verifies value after postfix increment

        auto rev_prefix = c.begin_reverse_order();  // Gets reverse order iterator
        CHECK(*rev_prefix == 5.0);  // Verifies first element
        CHECK(*(++rev_prefix) == 4.0);  // Verifies next element after prefix increment

        auto rev_postfix = c.begin_reverse_order();  // Gets another reverse order iterator
        CHECK(*rev_postfix == 5.0);  // Verifies first element
        CHECK(*(rev_postfix++) == 5.0);  // Verifies value before postfix increment
        CHECK(*rev_postfix == 4.0);  // Verifies value after postfix increment

        auto mid_prefix = c.begin_middle_out_order();  // Gets middle out order iterator
        CHECK(*mid_prefix == 3.0);  // Verifies first element
        CHECK(*(++mid_prefix) == 2.0);  // Verifies next element after prefix increment

        auto mid_postfix = c.begin_middle_out_order();  // Gets another middle out order iterator
        CHECK(*mid_postfix == 3.0);  // Verifies first element
        CHECK(*(mid_postfix++) == 3.0);  // Verifies value before postfix increment
        CHECK(*mid_postfix == 2.0);  // Verifies value after postfix increment
    }
SUBCASE("string") {  // Tests string iterator operations
        MyContainer<std::string> c;  // Creates string container
        c.addElement("alpha");  // Adds "alpha" to container
        c.addElement("bravo");  // Adds "bravo" to container
        c.addElement("charlie");  // Adds "charlie" to container
        c.addElement("delta");  // Adds "delta" to container
        c.addElement("echo");  // Adds "echo" to container
        CHECK(c.size() == 5);  // Verifies container size

        auto asc_prefix = c.begin_ascending_order();  // Gets ascending order iterator
        CHECK(*asc_prefix == "alpha");  // Verifies first element
        CHECK(*(++asc_prefix) == "bravo");  // Verifies next element after prefix increment

        auto asc_postfix = c.begin_ascending_order();  // Gets another ascending order iterator
        CHECK(*asc_postfix == "alpha");  // Verifies first element
        CHECK(*(asc_postfix++) == "alpha");  // Verifies value before postfix increment
        CHECK(*asc_postfix == "bravo");  // Verifies value after postfix increment

        auto desc_prefix = c.begin_descending_order();  // Gets descending order iterator
        CHECK(*desc_prefix == "echo");  // Verifies first element
        CHECK(*(++desc_prefix) == "delta");  // Verifies next element after prefix increment

        auto desc_postfix = c.begin_descending_order();  // Gets another descending order iterator
        CHECK(*desc_postfix == "echo");  // Verifies first element
        CHECK(*(desc_postfix++) == "echo");  // Verifies value before postfix increment
        CHECK(*desc_postfix == "delta");  // Verifies value after postfix increment

        auto side_prefix = c.begin_side_cross_order();  // Gets side cross order iterator
        CHECK(*side_prefix == "alpha");  // Verifies first element
        CHECK(*(++side_prefix) == "echo");  // Verifies next element after prefix increment

        auto side_postfix = c.begin_side_cross_order();  // Gets another side cross order iterator
        CHECK(*side_postfix == "alpha");  // Verifies first element
        CHECK(*(side_postfix++) == "alpha");  // Verifies value before postfix increment
        CHECK(*side_postfix == "echo");  // Verifies value after postfix increment

        auto rev_prefix = c.begin_reverse_order();  // Gets reverse order iterator
        CHECK(*rev_prefix == "echo");  // Verifies first element
        CHECK(*(++rev_prefix) == "delta");  // Verifies next element after prefix increment

        auto rev_postfix = c.begin_reverse_order();  // Gets another reverse order iterator
        CHECK(*rev_postfix == "echo");  // Verifies first element
        CHECK(*(rev_postfix++) == "echo");  // Verifies value before postfix increment
        CHECK(*rev_postfix == "delta");  // Verifies value after postfix increment

        auto mid_prefix = c.begin_middle_out_order();  // Gets middle out order iterator
        CHECK(*mid_prefix == "charlie"); // Verifies middle element
        CHECK(*(++mid_prefix) == "bravo");  // Verifies next element after prefix increment

        auto mid_postfix = c.begin_middle_out_order();  // Gets another middle out order iterator
        CHECK(*mid_postfix == "charlie");  // Verifies first element
        CHECK(*(mid_postfix++) == "charlie");  // Verifies value before postfix increment
        CHECK(*mid_postfix == "bravo");  // Verifies value after postfix increment
    }

    SUBCASE("char") {  // Tests char iterator operations
        MyContainer<char> c;  // Creates char container
        c.addElement('a');  // Adds 'a' to container
        c.addElement('b');  // Adds 'b' to container
        c.addElement('c');  // Adds 'c' to container
        c.addElement('d');  // Adds 'd' to container
        c.addElement('e');  // Adds 'e' to container
        CHECK(c.size() == 5);  // Verifies container size

        auto asc_prefix = c.begin_ascending_order();  // Gets ascending order iterator
        CHECK(*asc_prefix == 'a');  // Verifies first element
        CHECK(*(++asc_prefix) == 'b');  // Verifies next element after prefix increment

        auto asc_postfix = c.begin_ascending_order();  // Gets another ascending order iterator
        CHECK(*asc_postfix == 'a');  // Verifies first element
        CHECK(*(asc_postfix++) == 'a');  // Verifies value before postfix increment
        CHECK(*asc_postfix == 'b');  // Verifies value after postfix increment

        auto desc_prefix = c.begin_descending_order();  // Gets descending order iterator
        CHECK(*desc_prefix == 'e');  // Verifies first element
        CHECK(*(++desc_prefix) == 'd');  // Verifies next element after prefix increment

        auto desc_postfix = c.begin_descending_order();  // Gets another descending order iterator
        CHECK(*desc_postfix == 'e');  // Verifies first element
        CHECK(*(desc_postfix++) == 'e');  // Verifies value before postfix increment
        CHECK(*desc_postfix == 'd');  // Verifies value after postfix increment

        auto side_prefix = c.begin_side_cross_order();  // Gets side cross order iterator
        CHECK(*side_prefix == 'a');  // Verifies first element
        CHECK(*(++side_prefix) == 'e');  // Verifies next element after prefix increment

        auto side_postfix = c.begin_side_cross_order();  // Gets another side cross order iterator
        CHECK(*side_postfix == 'a');  // Verifies first element
        CHECK(*(side_postfix++) == 'a');  // Verifies value before postfix increment
        CHECK(*side_postfix == 'e');  // Verifies value after postfix increment

        auto rev_prefix = c.begin_reverse_order();  // Gets reverse order iterator
        CHECK(*rev_prefix == 'e');  // Verifies first element
        CHECK(*(++rev_prefix) == 'd');  // Verifies next element after prefix increment

        auto rev_postfix = c.begin_reverse_order();  // Gets another reverse order iterator
        CHECK(*rev_postfix == 'e');  // Verifies first element
        CHECK(*(rev_postfix++) == 'e');  // Verifies value before postfix increment
        CHECK(*rev_postfix == 'd');  // Verifies value after postfix increment

        auto mid_prefix = c.begin_middle_out_order();  // Gets middle out order iterator
        CHECK(*mid_prefix == 'c');  // Verifies middle element
        CHECK(*(++mid_prefix) == 'b');  // Verifies next element after prefix increment

        auto mid_postfix = c.begin_middle_out_order();  // Gets another middle out order iterator
        CHECK(*mid_postfix == 'c');  // Verifies first element
        CHECK(*(mid_postfix++) == 'c');  // Verifies value before postfix increment
        CHECK(*mid_postfix == 'b');  // Verifies value after postfix increment
    }
}

// Tests iterator equality and inequality comparisons
// This test case verifies the behavior of == and != operators for all iterator
// types across various container states (empty, single element, odd-sized,
// even-sized, duplicates, and large), ensuring correct comparison logic.
TEST_CASE("Iterator == and != comparison for all orders and cases") {  // Tests iterator comparison operators

    SUBCASE("Empty container") {  // Tests iterators in empty container
        MyContainer<int> c;  // Creates empty integer container
        CHECK(c.begin_ascending_order() == c.end_ascending_order());  // Verifies ascending iterators are equal
        CHECK(c.begin_descending_order() == c.end_descending_order());  // Verifies descending iterators are equal
        CHECK(c.begin_side_cross_order() == c.end_side_cross_order());  // Verifies side cross iterators are equal
        CHECK(c.begin_reverse_order() == c.end_reverse_order());  // Verifies reverse iterators are equal
        CHECK(c.begin_order() == c.end_order());  // Verifies insertion order iterators are equal
        CHECK(c.begin_middle_out_order() == c.end_middle_out_order());  // Verifies middle out iterators are equal
    }

    SUBCASE("Single element") {  // Tests iterators with one element
        MyContainer<int> c;  // Creates integer container
        c.addElement(1);  // Adds single element

        auto asc1 = c.begin_ascending_order();  // Gets first ascending iterator
        auto asc2 = c.begin_ascending_order();  // Gets second ascending iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal
        ++asc2;  // Increments second iterator
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        ++asc1;  // Increments first iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal again
        asc1 = c.begin_ascending_order();  // Resets first iterator
        asc2 = c.begin_ascending_order();  // Resets second iterator
        CHECK(asc1++ == asc2);  // Verifies postfix increment equality
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        CHECK(++asc2 == asc1);  // Verifies prefix increment equality

        auto desc1 = c.begin_descending_order();  // Gets first descending iterator
        auto desc2 = c.begin_descending_order();  // Gets second descending iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal
        ++desc2;  // Increments second iterator
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        ++desc1;  // Increments first iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal again
        desc1 = c.begin_descending_order();  // Resets first iterator
        desc2 = c.begin_descending_order();  // Resets second iterator
        CHECK(desc1++ == desc2);  // Verifies postfix increment equality
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        CHECK(++desc2 == desc1);  // Verifies prefix increment equality

        auto cross1 = c.begin_side_cross_order();  // Gets first side cross iterator
        auto cross2 = c.begin_side_cross_order();  // Gets second side cross iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal
        ++cross2;  // Increments second iterator
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        ++cross1;  // Increments first iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal again
        cross1 = c.begin_side_cross_order();  // Resets first iterator
        cross2 = c.begin_side_cross_order();  // Resets second iterator
        CHECK(cross1++ == cross2);  // Verifies postfix increment equality
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        CHECK(++cross2 == cross1);  // Verifies prefix increment equality

        auto rev1 = c.begin_reverse_order();  // Gets first reverse iterator
        auto rev2 = c.begin_reverse_order();  // Gets second reverse iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal
        ++rev2;  // Increments second iterator
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        ++rev1;  // Increments first iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal again
        rev1 = c.begin_reverse_order();  // Resets first iterator
        rev2 = c.begin_reverse_order();  // Resets second iterator
        CHECK(rev1++ == rev2);  // Verifies postfix increment equality
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        CHECK(++rev2 == rev1);  // Verifies prefix increment equality

        auto ord1 = c.begin_order();  // Gets first insertion order iterator
        auto ord2 = c.begin_order();  // Gets second insertion order iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal
        ++ord2;  // Increments second iterator
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        ++ord1;  // Increments first iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal again
        ord1 = c.begin_order();  // Resets first iterator
        ord2 = c.begin_order();  // Resets second iterator
        CHECK(ord1++ == ord2);  // Verifies postfix increment equality
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        CHECK(++ord2 == ord1);  // Verifies prefix increment equality

        auto mid1 = c.begin_middle_out_order();  // Gets first middle out iterator
        auto mid2 = c.begin_middle_out_order();  // Gets second middle out iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal
        ++mid2;  // Increments second iterator
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        ++mid1;  // Increments first iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal again
        mid1 = c.begin_middle_out_order();  // Resets first iterator
        mid2 = c.begin_middle_out_order();  // Resets second iterator
        CHECK(mid1++ == mid2);  // Verifies postfix increment equality
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        CHECK(++mid2 == mid1);  // Verifies prefix increment equality
    }

    SUBCASE("Odd-sized container") {  // Tests iterators with odd number of elements
        MyContainer<int> c;  // Creates integer container
        c.addElement(1);  // Adds element 1
        c.addElement(2);  // Adds element 2
        c.addElement(3);  // Adds element 3

        auto asc1 = c.begin_ascending_order();  // Gets first ascending iterator
        auto asc2 = c.begin_ascending_order();  // Gets second ascending iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal
        ++asc2;  // Increments second iterator
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        ++asc1;  // Increments first iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal again
        asc1 = c.begin_ascending_order();  // Resets first iterator
        asc2 = c.begin_ascending_order();  // Resets second iterator
        CHECK(asc1++ == asc2);  // Verifies postfix increment equality
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        CHECK(++asc2 == asc1);  // Verifies prefix increment equality

        auto desc1 = c.begin_descending_order();  // Gets first descending iterator
        auto desc2 = c.begin_descending_order();  // Gets second descending iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal
        ++desc2;  // Increments second iterator
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        ++desc1;  // Increments first iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal again
        desc1 = c.begin_descending_order();  // Resets first iterator
        desc2 = c.begin_descending_order();  // Resets second iterator
        CHECK(desc1++ == desc2);  // Verifies postfix increment equality
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        CHECK(++desc2 == desc1);  // Verifies prefix increment equality

        auto cross1 = c.begin_side_cross_order();  // Gets first side cross iterator
        auto cross2 = c.begin_side_cross_order();  // Gets second side cross iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal
        ++cross2;  // Increments second iterator
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        ++cross1;  // Increments first iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal again
        cross1 = c.begin_side_cross_order();  // Resets first iterator
        cross2 = c.begin_side_cross_order();  // Resets second iterator
        CHECK(cross1++ == cross2);  // Verifies postfix increment equality
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        CHECK(++cross2 == cross1);  // Verifies prefix increment equality

        auto rev1 = c.begin_reverse_order();  // Gets first reverse iterator
        auto rev2 = c.begin_reverse_order();  // Gets second reverse iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal
        ++rev2;  // Increments second iterator
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        ++rev1;  // Increments first iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal again
        rev1 = c.begin_reverse_order();  // Resets first iterator
        rev2 = c.begin_reverse_order();  // Resets second iterator
        CHECK(rev1++ == rev2);  // Verifies postfix increment equality
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        CHECK(++rev2 == rev1);  // Verifies prefix increment equality

        auto ord1 = c.begin_order();  // Gets first insertion order iterator
        auto ord2 = c.begin_order();  // Gets second insertion order iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal
        ++ord2;  // Increments second iterator
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        ++ord1;  // Increments first iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal again
        ord1 = c.begin_order();  // Resets first iterator
        ord2 = c.begin_order();  // Resets second iterator
        CHECK(ord1++ == ord2);  // Verifies postfix increment equality
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        CHECK(++ord2 == ord1);  // Verifies prefix increment equality

        auto mid1 = c.begin_middle_out_order();  // Gets first middle out iterator
        auto mid2 = c.begin_middle_out_order();  // Gets second middle out iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal
        ++mid2;  // Increments second iterator
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        ++mid1;  // Increments first iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal again
        mid1 = c.begin_middle_out_order();  // Resets first iterator
        mid2 = c.begin_middle_out_order();  // Resets second iterator
        CHECK(mid1++ == mid2);  // Verifies postfix increment equality
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        CHECK(++mid2 == mid1);  // Verifies prefix increment equality
    }

    SUBCASE("Even-sized container") {  // Tests iterators with even number of elements
        MyContainer<int> c;  // Creates integer container
        c.addElement(1);  // Adds element 1
        c.addElement(2);  // Adds element 2
        c.addElement(3);  // Adds element 3
        c.addElement(4);  // Adds element 4

        auto asc1 = c.begin_ascending_order();  // Gets first ascending iterator
        auto asc2 = c.begin_ascending_order();  // Gets second ascending iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal
        ++asc2;  // Increments second iterator
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        ++asc1;  // Increments first iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal again
        asc1 = c.begin_ascending_order();  // Resets first iterator
        asc2 = c.begin_ascending_order();  // Resets second iterator
        CHECK(asc1++ == asc2);  // Verifies postfix increment equality
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        CHECK(++asc2 == asc1);  // Verifies prefix increment equality

        auto desc1 = c.begin_descending_order();  // Gets first descending iterator
        auto desc2 = c.begin_descending_order();  // Gets second descending iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal
        ++desc2;  // Increments second iterator
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        ++desc1;  // Increments first iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal again
        desc1 = c.begin_descending_order();  // Resets first iterator
        desc2 = c.begin_descending_order();  // Resets second iterator
        CHECK(desc1++ == desc2);  // Verifies postfix increment equality
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        CHECK(++desc2 == desc1);  // Verifies prefix increment equality

        auto cross1 = c.begin_side_cross_order();  // Gets first side cross iterator
        auto cross2 = c.begin_side_cross_order();  // Gets second side cross iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal
        ++cross2;  // Increments second iterator
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        ++cross1;  // Increments first iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal again
        cross1 = c.begin_side_cross_order();  // Resets first iterator
        cross2 = c.begin_side_cross_order();  // Resets second iterator
        CHECK(cross1++ == cross2);  // Verifies postfix increment equality
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        CHECK(++cross2 == cross1);  // Verifies prefix increment equality

        auto rev1 = c.begin_reverse_order();  // Gets first reverse iterator
        auto rev2 = c.begin_reverse_order();  // Gets second reverse iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal
        ++rev2;  // Increments second iterator
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        ++rev1;  // Increments first iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal again
        rev1 = c.begin_reverse_order();  // Resets first iterator
        rev2 = c.begin_reverse_order();  // Resets second iterator
        CHECK(rev1++ == rev2);  // Verifies postfix increment equality
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        CHECK(++rev2 == rev1);  // Verifies prefix increment equality

        auto ord1 = c.begin_order();  // Gets first insertion order iterator
        auto ord2 = c.begin_order();  // Gets second insertion order iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal
        ++ord2;  // Increments second iterator
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        ++ord1;  // Increments first iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal again
        ord1 = c.begin_order();  // Resets first iterator
        ord2 = c.begin_order();  // Resets second iterator
        CHECK(ord1++ == ord2);  // Verifies postfix increment equality
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        CHECK(++ord2 == ord1);  // Verifies prefix increment equality

        auto mid1 = c.begin_middle_out_order();  // Gets first middle out iterator
        auto mid2 = c.begin_middle_out_order();  // Gets second middle out iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal
        ++mid2;  // Increments second iterator
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        ++mid1;  // Increments first iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal again
        mid1 = c.begin_middle_out_order();  // Resets first iterator
        mid2 = c.begin_middle_out_order();  // Resets second iterator
        CHECK(mid1++ == mid2);  // Verifies postfix increment equality
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        CHECK(++mid2 == mid1);  // Verifies prefix increment equality
    }

    SUBCASE("Duplicate elements") {  // Tests iterators with duplicate elements
        MyContainer<int> c;  // Creates integer container
        for (int i = 0; i < 5; ++i) c.addElement(3);  // Adds five duplicate elements

        auto asc1 = c.begin_ascending_order();  // Gets first ascending iterator
        auto asc2 = c.begin_ascending_order();  // Gets second ascending iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal
        ++asc2;  // Increments second iterator
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        ++asc1;  // Increments first iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal again
        asc1 = c.begin_ascending_order();  // Resets first iterator
        asc2 = c.begin_ascending_order();  // Resets second iterator
        CHECK(asc1++ == asc2);  // Verifies postfix increment equality
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        CHECK(++asc2 == asc1);  // Verifies prefix increment equality

        auto desc1 = c.begin_descending_order();  // Gets first descending iterator
        auto desc2 = c.begin_descending_order();  // Gets second descending iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal
        ++desc2;  // Increments second iterator
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        ++desc1;  // Increments first iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal again
        desc1 = c.begin_descending_order();  // Resets first iterator
        desc2 = c.begin_descending_order();  // Resets second iterator
        CHECK(desc1++ == desc2);  // Verifies postfix increment equality
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        CHECK(++desc2 == desc1);  // Verifies prefix increment equality

        auto cross1 = c.begin_side_cross_order();  // Gets first side cross iterator
        auto cross2 = c.begin_side_cross_order();  // Gets second side cross iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal
        ++cross2;  // Increments second iterator
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        ++cross1;  // Increments first iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal again
        cross1 = c.begin_side_cross_order();  // Resets first iterator
        cross2 = c.begin_side_cross_order();  // Resets second iterator
        CHECK(cross1++ == cross2);  // Verifies postfix increment equality
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        CHECK(++cross2 == cross1);  // Verifies prefix increment equality

        auto rev1 = c.begin_reverse_order();  // Gets first reverse iterator
        auto rev2 = c.begin_reverse_order();  // Gets second reverse iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal
        ++rev2;  // Increments second iterator
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        ++rev1;  // Increments first iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal again
        rev1 = c.begin_reverse_order();  // Resets first iterator
        rev2 = c.begin_reverse_order();  // Resets second iterator
        CHECK(rev1++ == rev2);  // Verifies postfix increment equality
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        CHECK(++rev2 == rev1);  // Verifies prefix increment equality

        auto ord1 = c.begin_order();  // Gets first insertion order iterator
        auto ord2 = c.begin_order();  // Gets second insertion order iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal
        ++ord2;  // Increments second iterator
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        ++ord1;  // Increments first iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal again
        ord1 = c.begin_order();  // Resets first iterator
        ord2 = c.begin_order();  // Resets second iterator
        CHECK(ord1++ == ord2);  // Verifies postfix increment equality
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        CHECK(++ord2 == ord1);  // Verifies prefix increment equality

        auto mid1 = c.begin_middle_out_order();  // Gets first middle out iterator
        auto mid2 = c.begin_middle_out_order();  // Gets second middle out iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal
        ++mid2;  // Increments second iterator
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        ++mid1;  // Increments first iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal again
        mid1 = c.begin_middle_out_order();  // Resets first iterator
        mid2 = c.begin_middle_out_order();  // Resets second iterator
        CHECK(mid1++ == mid2);  // Verifies postfix increment equality
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        CHECK(++mid2 == mid1);  // Verifies prefix increment equality
    }

    SUBCASE("Large container") {  // Tests iterators with large number of elements
        MyContainer<int> c;  // Creates integer container
        for (int i = 0; i < 10; ++i) c.addElement(i);  // Adds elements 0 to 9

        auto asc1 = c.begin_ascending_order();  // Gets first ascending iterator
        auto asc2 = c.begin_ascending_order();  // Gets second ascending iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal
        ++asc2;  // Increments second iterator
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        ++asc1;  // Increments first iterator
        CHECK(asc1 == asc2);  // Verifies iterators are equal again
        asc1 = c.begin_ascending_order();  // Resets first iterator
        asc2 = c.begin_ascending_order();  // Resets second iterator
        CHECK(asc1++ == asc2);  // Verifies postfix increment equality
        CHECK(asc1 != asc2);  // Verifies iterators are not equal
        CHECK(++asc2 == asc1);  // Verifies prefix increment equality

        auto desc1 = c.begin_descending_order();  // Gets first descending iterator
        auto desc2 = c.begin_descending_order();  // Gets second descending iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal
        ++desc2;  // Increments second iterator
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        ++desc1;  // Increments first iterator
        CHECK(desc1 == desc2);  // Verifies iterators are equal again
        desc1 = c.begin_descending_order();  // Resets first iterator
        desc2 = c.begin_descending_order();  // Resets second iterator
        CHECK(desc1++ == desc2);  // Verifies postfix increment equality
        CHECK(desc1 != desc2);  // Verifies iterators are not equal
        CHECK(++desc2 == desc1);  // Verifies prefix increment equality

        auto cross1 = c.begin_side_cross_order();  // Gets first side cross iterator
        auto cross2 = c.begin_side_cross_order();  // Gets second side cross iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal
        ++cross2;  // Increments second iterator
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        ++cross1;  // Increments first iterator
        CHECK(cross1 == cross2);  // Verifies iterators are equal again
        cross1 = c.begin_side_cross_order();  // Resets first iterator
        cross2 = c.begin_side_cross_order();  // Resets second iterator
        CHECK(cross1++ == cross2);  // Verifies postfix increment equality
        CHECK(cross1 != cross2);  // Verifies iterators are not equal
        CHECK(++cross2 == cross1);  // Verifies prefix increment equality

        auto rev1 = c.begin_reverse_order();  // Gets first reverse iterator
        auto rev2 = c.begin_reverse_order();  // Gets second reverse iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal
        ++rev2;  // Increments second iterator
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        ++rev1;  // Increments first iterator
        CHECK(rev1 == rev2);  // Verifies iterators are equal again
        rev1 = c.begin_reverse_order();  // Resets first iterator
        rev2 = c.begin_reverse_order();  // Resets second iterator
        CHECK(rev1++ == rev2);  // Verifies postfix increment equality
        CHECK(rev1 != rev2);  // Verifies iterators are not equal
        CHECK(++rev2 == rev1);  // Verifies prefix increment equality

        auto ord1 = c.begin_order();  // Gets first insertion order iterator
        auto ord2 = c.begin_order();  // Gets second insertion order iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal
        ++ord2;  // Increments second iterator
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        ++ord1;  // Increments first iterator
        CHECK(ord1 == ord2);  // Verifies iterators are equal again
        ord1 = c.begin_order();  // Resets first iterator
        ord2 = c.begin_order();  // Resets second iterator
        CHECK(ord1++ == ord2);  // Verifies postfix increment equality
        CHECK(ord1 != ord2);  // Verifies iterators are not equal
        CHECK(++ord2 == ord1);  // Verifies prefix increment equality

        auto mid1 = c.begin_middle_out_order();  // Gets first middle out iterator
        auto mid2 = c.begin_middle_out_order();  // Gets second middle out iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal
        ++mid2;  // Increments second iterator
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        ++mid1;  // Increments first iterator
        CHECK(mid1 == mid2);  // Verifies iterators are equal again
        mid1 = c.begin_middle_out_order();  // Resets first iterator
        mid2 = c.begin_middle_out_order();  // Resets second iterator
        CHECK(mid1++ == mid2);  // Verifies postfix increment equality
        CHECK(mid1 != mid2);  // Verifies iterators are not equal
        CHECK(++mid2 == mid1);  // Verifies prefix increment equality
    }
}

// Tests iterator stability after container modification
// This test case verifies that an iterator remains valid and points to the same element
// after the container is modified by adding a new element.
TEST_CASE("Iterator after container modification") {  // Tests iterator stability
    MyContainer<int> c;  // Creates integer container
    c.addElement(1);  // Adds element 1
    auto it = c.begin_ascending_order();  // Gets ascending order iterator
    c.addElement(2);  // Adds element 2
    CHECK(*it == 1); // Verifies iterator points to original element
}

// Tests iterator assignment
// This test case checks that assigning one iterator to another results in both
// iterators being equal, pointing to the same position in the container.
TEST_CASE("Iterator assignment") {  // Tests iterator assignment
    MyContainer<int> c;  // Creates integer container
    c.addElement(1);  // Adds element 1
    auto it1 = c.begin_ascending_order();  // Gets first ascending iterator
    auto it2 = c.begin_ascending_order();  // Gets second ascending iterator
    it2 = it1;  // Assigns first iterator to second
    CHECK(it1 == it2);  // Verifies iterators are equal
}

// Tests dereferencing iterator in empty container
// This test case ensures that attempting to dereference an iterator in an empty
// container throws an out_of_range exception.
TEST_CASE("Empty container dereference") {  // Tests empty container dereference
    MyContainer<int> c;  // Creates empty integer container
    auto it = c.begin_ascending_order();  // Gets ascending iterator
    CHECK_THROWS_AS(*it, std::out_of_range);  // Verifies dereference throws exception
}

// Tests iterator traversal orders with integer elements
// This test case uses the testIterators helper function to verify all iterator
// types (ascending, descending, side cross, reverse, insertion, middle out)
// produce the expected order for various integer container configurations.
TEST_CASE("Iterators with int") {  // Tests iterators with integers
    SUBCASE("Odd-sized container") {  // Tests container with odd number of elements
        MyContainer<int> c;  // Creates integer container
        c.addElement(4);  // Adds element 4
        c.addElement(9);  // Adds element 9
        c.addElement(3);  // Adds element 3
        c.addElement(11);  // Adds element 11
        c.addElement(5);  // Adds element 5

        testIterators(c,  // Tests all iterator types
                      vector<int>{3, 4, 5, 9, 11},    // Expected ascending order
                      vector<int>{11, 9, 5, 4, 3},    // Expected descending order
                      vector<int>{3, 11, 4, 9, 5},    // Expected side cross order
                      vector<int>{5, 11, 3, 9, 4},    // Expected reverse order
                      vector<int>{4, 9, 3, 11, 5},    // Expected insertion order
                      vector<int>{3, 9, 11, 4, 5});   // Expected middle out order
    }

    SUBCASE("Even-sized container") {  // Tests container with even number of elements
        MyContainer<int> c;  // Creates integer container
        c.addElement(10);  // Adds element 10
        c.addElement(2);  // Adds element 2
        c.addElement(7);  // Adds element 7
        c.addElement(1);  // Adds element 1
        c.addElement(6);  // Adds element 6
        c.addElement(12);  // Adds element 12

        testIterators(c,  // Tests all iterator types
                      vector<int>{1, 2, 6, 7, 10, 12},    // Expected ascending order
                      vector<int>{12, 10, 7, 6, 2, 1},    // Expected descending order
                      vector<int>{1, 12, 2, 10, 6, 7},    // Expected side cross order
                      vector<int>{12, 6, 1, 7, 2, 10},    // Expected reverse order
                      vector<int>{10, 2, 7, 1, 6, 12},    // Expected insertion order
                      vector<int>{1, 7, 6, 2, 12, 10});   // Expected middle out order
    }

    SUBCASE("Empty container") {  // Tests empty container
        MyContainer<int> c;  // Creates empty integer container

        testIterators(c,  // Tests all iterator types
                      vector<int>{},    // Expected ascending order
                      vector<int>{},    // Expected descending order
                      vector<int>{},    // Expected side cross order
                      vector<int>{},    // Expected reverse order
                      vector<int>{},    // Expected insertion order
                      vector<int>{});   // Expected middle out order
    }

    SUBCASE("Single element") {  // Tests container with one element
        MyContainer<int> c;  // Creates integer container
        c.addElement(42);  // Adds element 42

        testIterators(c,  // Tests all iterator types
                      vector<int>{42},    // Expected ascending order
                      vector<int>{42},    // Expected descending order
                      vector<int>{42},    // Expected side cross order
                      vector<int>{42},    // Expected reverse order
                      vector<int>{42},    // Expected insertion order
                      vector<int>{42});   // Expected middle out order
    }

    SUBCASE("Duplicate elements") {  // Tests container with duplicate elements
        MyContainer<int> c;  // Creates integer container
        c.addElement(3);  // Adds element 3
        c.addElement(3);  // Adds element 3
        c.addElement(3);  // Adds element 3
        c.addElement(3);  // Adds element 3
        c.addElement(3);  // Adds element 3

        testIterators(c,  // Tests all iterator types
                      vector<int>{3, 3, 3, 3, 3},    // Expected ascending order
                      vector<int>{3, 3, 3, 3, 3},    // Expected descending order
                      vector<int>{3, 3, 3, 3, 3},    // Expected side cross order
                      vector<int>{3, 3, 3, 3, 3},    // Expected reverse order
                      vector<int>{3, 3, 3, 3, 3},    // Expected insertion order
                      vector<int>{3, 3, 3, 3, 3});   // Expected middle out order
    }

    SUBCASE("Large container") {  // Tests container with many elements
        MyContainer<int> c;  // Creates integer container
        vector<int> insertion_order;  // Tracks insertion order
        for (int i = 0; i < 10; ++i) {  // Loops to add 10 elements
            int val = i % 10;  // Generates value 0-9
            c.addElement(val);  // Adds element
            insertion_order.push_back(val);  // Records insertion order
        }
        CHECK(c.size() == 10);  // Verifies container size

        vector<int> expected_asc = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Defines expected ascending order
        vector<int> expected_desc = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};  // Defines expected descending order
        vector<int> expected_side = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};  // Defines expected side cross order
        vector<int> expected_rev = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};  // Defines expected reverse order
        vector<int> expected_mid = {5, 4, 6, 3, 7, 2, 8, 1, 9, 0};  // Defines expected middle out order

        testIterators(c,  // Tests all iterator types
                      expected_asc,           // Expected ascending order
                      expected_desc,          // Expected descending order
                      expected_side,          // Expected side cross order
                      expected_rev,           // Expected reverse order
                      insertion_order,        // Expected insertion order
                      expected_mid);          // Expected middle out order
    }
}

// Tests iterator traversal orders with string elements
// This test case verifies all iterator types produce the expected order for
// various string container configurations using the testIterators helper function.
TEST_CASE("Iterators with string") {  // Tests iterators with strings
    SUBCASE("Odd-sized container") {  // Tests container with odd number of elements
        MyContainer<string> c;  // Creates string container
        c.addElement("banana");  // Adds "banana"
        c.addElement("apple");  // Adds "apple"
        c.addElement("cherry");  // Adds "cherry"
        c.addElement("date");  // Adds "date"
        c.addElement("fig");  // Adds "fig"

        testIterators(c,  // Tests all iterator types
                      vector<string>{"apple", "banana", "cherry", "date", "fig"},    // Expected ascending order
                      vector<string>{"fig", "date", "cherry", "banana", "apple"},    // Expected descending order
                      vector<string>{"apple", "fig", "banana", "date", "cherry"},    // Expected side cross order
                      vector<string>{"fig", "date", "cherry", "apple", "banana"},    // Expected reverse order
                      vector<string>{"banana", "apple", "cherry", "date", "fig"},    // Expected insertion order
                      vector<string>{"cherry", "apple", "date", "banana", "fig"});   // Expected middle out order
    }

    SUBCASE("Even-sized container") {  // Tests container with even number of elements
        MyContainer<string> c;  // Creates string container
        c.addElement("grape");  // Adds "grape"
        c.addElement("apple");  // Adds "apple"
        c.addElement("banana");  // Adds "banana"
        c.addElement("cherry");  // Adds "cherry"
        c.addElement("date");  // Adds "date"
        c.addElement("fig");  // Adds "fig"

        testIterators(c,  // Tests all iterator types
                      vector<string>{"apple", "banana", "cherry", "date", "fig", "grape"},    // Expected ascending order
                      vector<string>{"grape", "fig", "date", "cherry", "banana", "apple"},    // Expected descending order
                      vector<string>{"apple", "grape", "banana", "fig", "cherry", "date"},    // Expected side cross order
                      vector<string>{"fig", "date", "cherry", "banana", "apple", "grape"},    // Expected reverse order
                      vector<string>{"grape", "apple", "banana", "cherry", "date", "fig"},    // Expected insertion order
                      vector<string>{"cherry", "banana", "date", "apple", "fig", "grape"});   // Expected middle out order
    }

    SUBCASE("Empty container") {  // Tests empty container
        MyContainer<string> c;  // Creates empty string container

        testIterators(c,  // Tests all iterator types
                      vector<string>{},    // Expected ascending order
                      vector<string>{},    // Verifies empty container iterator
                      vector<string>{},    // Expected side cross order
                      vector<string>{},    // Expected reverse order
                      vector<string>{},    // Expected insertion order
                      vector<string>{});   // Expected middle out order
    }

    SUBCASE("Single element") {  // Tests container with one element
        MyContainer<string> c;  // Creates string container
        c.addElement("hello");    // Adds "hello"

        testIterators(c,  // Tests all iterator types
                      vector<string>{"hello"},    // Expected ascending order
                      vector<string>{"hello"},    // Expected descending order
                      vector<string>{"hello"},    // Expected side cross order
                      vector<string>{"hello"},    // Expected reverse order
                      vector<string>{"hello"},    // Expected insertion order
                      vector<string>{"hello"});   // Expected middle out order
    }

    SUBCASE("Duplicate elements") {  // Tests container with duplicate elements
        MyContainer<string> c;  // Creates string container
        c.addElement("apple");  // Adds "apple"
        c.addElement("apple");    // Adds "apple" again
        c.addElement("apple");    // Adds "apple"
        c.addElement("apple");    // Adds "apple"
        c.addElement("apple");    // Adds "apple" again

        testIterators(c,  // Tests all iterator types
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}, // Expected ascending order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}, // Expected descending order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}, // Expected side cross order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}, // Expected reverse order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}, // Expected insertion order
                      vector<string>{"apple", "apple", "apple", "apple", "apple"}); // Expected middle out order
    }

    SUBCASE("Large container") {  // Tests container with many elements
        MyContainer<string> c;  // Creates string container
        vector<string> insertion_order;  // Tracks insertion order
        for (int i = 0; i < 10; ++i) {  // Loops to add 10 elements
            string val = "item" + to_string(i % 10);  // Generates value string
            c.addElement(val);  // Adds element to container
            insertion_order.push_back(val);  // Records element in insertion order
        }
        CHECK(c.size() == 10);  // Verifies container size

        vector<string> expected_asc = {"item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9"};  // Defines expected ascending order
        vector<string> expected_desc = {"item9", "item8", "item7", "item6", "item5", "item4", "item3", "item2", "item1", "item0"}; // // Defines expected descending
        vector<string> expected_side = {"item0", "item9", "item1", "item8", "item2", "item7", "item3", "item6", "item4", "item5"}; // // Defines expected side cross order
        vector<string> expected_rev = {"item9", "item8", "item7", "item6", "item5", "item4", "item3", "item2", "item1", "item0"}; // // Defines expected reverse order
        vector<string> expected_mid = {"item5", "item4", "item6", "item3", "item7", "item2", "item8", "item1", "item9", "item0"}; // Defines expected middle out order

        testIterators(c,  // Tests all iterator types
                      expected_asc,           // Expected ascending order
                      expected_desc,          // Expected descending order
                      expected_side,          // Expected side cross order
                      expected_rev,           // Expected reverse order
                      insertion_order,        // Expected insertion order
                      expected_mid);          // Expected middle out order
    }
}

// Tests iterator traversal orders with double elements
// This test case verifies that all iterator types produce the expected order
// for various double container configurations using the testIterators helper function.
TEST_CASE("Iterators with double") {  // Tests iterators with doubles
    SUBCASE("Odd-sized container") {  // Tests container with odd number of elements
        MyContainer<double> c;  // Creates double container
        c.addElement(3.14);  // Adds element 3.14
        c.addElement(1.41);  // Adds element 1.41
        c.addElement(2.72);  // Adds element 2.72
        c.addElement(5.0); // // Adds element 5.0
        c.addElement(0.5); // Adds element 0.5

        testIterators(c,  // Tests all iterator types
                      vector<double>{0.5, 1.41, 2.72, 3.14, 5.0},    // Expected ascending order
                      vector<double>{5.0, 3.14, 2.72, 1.41, 0.5}, // // Expected descending order
                      vector<double>{0.5, 5.0, 1.41, 3.14, 2.72}, // // Expected side cross order
                      vector<double>{0.5, 5.0, 2.72, 1.41, 3.14}, // // Expected reverse order
                      vector<double>{3.14, 1.41, 2.72, 5.0, 0.5}, // // Expected insertion order
                      vector<double>{2.72, 1.41, 5.0, 3.14, 0.5}); // // Expected middle out order
    }

    SUBCASE("Even-sized container") {  // Tests container with even number of elements
        MyContainer<double> c;  // Creates double container
        c.addElement(1.0);  // Adds element 1.0
        c.addElement(2.0);  // Adds element 2.0
        c.addElement(3.0);  // Adds element 3.0
        c.addElement(4.0);  // Adds element 4.0
        c.addElement(5.0);  // Adds element 5.0
        c.addElement(6.0);  // Adds element 6.0

        testIterators(c,  // Tests all iterator types
                      vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, // // Expected ascending order
                      vector<double>{6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, // // Expected descending order
                      vector<double>{1.0, 6.0, 2.0, 5.0, 3.0, 4.0}, // // Expected side cross order
                      vector<double>{6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, // // Expected reverse order
                      vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, // // Expected insertion order
                      vector<double>{4.0, 3.0, 5.0, 2.0, 6.0, 1.0}); // // Expected middle out order
    }

    SUBCASE("Empty container") {  // Tests empty container
        MyContainer<double> c;  // Creates empty double container

        testIterators(c,  // Tests all iterator types
                      vector<double>{},            // Expected ascending order
                      vector<double>{},    // Expected descending order
                      vector<double>{},        // Expected side cross order
                      vector<double>{},        // Expected reverse order
                      vector<double>{},    // Expected insertion order
                      vector<double>{});   // Expected middle out order
    }

    SUBCASE("Single element") {  // Tests container with a single element
        MyContainer<double> c;  // Creates double container
        c.addElement(1.23);  // Adds element 1.23

        testIterators(c,  // Tests all iterator types
                      vector<double>{1.23},    // Expected ascending order
                      vector<double>{1.23},     // Expected descending order
                      vector<double>{1.23},    // Expected side cross order
                      vector<double>{1.23},     // Expected reverse order
                      vector<double>{1.23},     // Expected insertion order
                      vector<double>{1.23});   // Expected middle out order
    }

    SUBCASE("Duplicate elements") {  // Tests container with duplicate elements
        MyContainer<double> c;  // Creates double container
        c.addElement(2.5);    // Adds element 2.5
        c.addElement(2.5);  // Adds element 2.5 again
        c.addElement(2.5);  // Adds element 2.5 again
        c.addElement(2.5);  // Adds element 2.5 again
        c.addElement(2.5);  // Adds element 2.5 again

        testIterators(c,  // Tests all iterator types
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}, // // Expected ascending order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}, // // Expected descending order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}, // // Expected side cross order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}, // // Expected reverse order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}, // // Expected insertion order
                      vector<double>{2.5, 2.5, 2.5, 2.5, 2.5}); // // Expected middle out order
    }

    SUBCASE("Large container") {  // Tests container with many elements
        MyContainer<double> c;  // Creates double container
        vector<double> insertion_order;  // Tracks insertion order
        for (int i = 0; i < 10; ++i) {  // Loops to add 10 elements
            double val = static_cast<double>(i % 10) + 0.5;  // Generates double value
            c.addElement(val);  // Adds element to container
            insertion_order.push_back(val); // // Records element in insertion order
        }
        CHECK(c.size() == 10); // // Verifies container size

        vector<double> expected_asc = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5}; // // Defines expected ascending order
        vector<double> expected_desc = {9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5}; // // Defines expected descending order
        vector<double> expected_side = {0.5, 9.5, 1.5, 8.5, 2.5, 7.5, 3.5, 6.5, 4.5, 5.5}; // // Defines expected side cross order
        vector<double> expected_rev = {9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5}; // // Defines expected reverse order
        vector<double> expected_mid = {5.5, 4.5, 6.5, 3.5, 7.5, 2.5, 8.5, 1.5, 9.5, 0.5}; // // Defines expected middle out order

        testIterators(c,  // Tests all iterator types
                      expected_asc,           // Expected ascending order
                      expected_desc,          // Expected descending order
                      expected_side,          // Expected side cross order
                      expected_rev,           // Expected reverse order
                      insertion_order,    // Expected insertion order
                      expected_mid);          // Expected middle out order
    }
}

// Tests iterator traversal orders with char elements
// This test case verifies that all iterator types produce the expected order
// for various character configurations using the testIterators helper function.
TEST_CASE("Iterators with char") {  // Tests iterators with chars
    SUBCASE("Odd-sized container") {  // Tests container with odd number of elements
        MyContainer<char> c;  // Creates char container
        c.addElement('e');    // Adds element 'e'
        c.addElement('a');    // Adds element 'a'
        c.addElement('c');    // Adds element 'c'
        c.addElement('b');    // Adds element 'b'
        c.addElement('d');    // Adds element 'd'

        testIterators(c,  // Tests all iterator types
                      vector<char>{'a', 'b', 'c', 'd', 'e'},    // Expected ascending order
                      vector<char>{'e', 'd', 'c', 'b', 'a'},    // Expected descending order
                      vector<char>{'a', 'e', 'b', 'd', 'c'},    // Expected side cross order
                      vector<char>{'d', 'b', 'c', 'a', 'e'},    // Expected reverse order
                      vector<char>{'e', 'a', 'c', 'b', 'd'},    // Expected insertion order
                      vector<char>{'c', 'a', 'b', 'e', 'd'});   // Expected middle out order
    }

    SUBCASE("Even-sized container") {  // Tests container with even number of elements
        MyContainer<char> c;  // Creates char container
        c.addElement('a');    // Adds element 'a'
        c.addElement('b');    // Adds element 'b'
        c.addElement('c');    // Adds element 'c'
        c.addElement('d');    // Adds element 'd'
        c.addElement('e');    // Adds element 'e'
        c.addElement('f');    // Adds element 'f'

        testIterators(c,  // Tests all iterator types
                      vector<char>{'a', 'b', 'c', 'd', 'e', 'f'},    // Expected ascending order
                      vector<char>{'f', 'e', 'd', 'c', 'b', 'a'},    // Expected descending order
                      vector<char>{'a', 'f', 'b', 'e', 'c', 'd'},    // Expected side cross order
                      vector<char>{'f', 'e', 'd', 'c', 'b', 'a'},    // Expected reverse order
                      vector<char>{'a', 'b', 'c', 'd', 'e', 'f'},    // Expected insertion order
                      vector<char>{'d', 'c', 'e', 'b', 'f', 'a'});   // Expected middle out order
    }

    SUBCASE("Empty container") {  // Tests empty container
        MyContainer<char> c;  // Creates empty char container

        testIterators(c,  // Tests all iterator types
                      vector<char>{},    // Expected ascending order
                      vector<char>{},    // Expected descending order
                      vector<char>{},    // Expected side cross order
                      vector<char>{},    // Expected reverse order
                      vector<char>{},    // Expected insertion order
                      vector<char>{});   // Expected middle out order
    }

    SUBCASE("Single element") {  // Tests container with a single element
        MyContainer<char> c;  // Creates char container
        c.addElement('x');    // Adds element 'x'

        testIterators(c,  // Tests all iterator types
                      vector<char>{'x'},    // Expected ascending order
                      vector<char>{'x'},    // Expected descending order
                      vector<char>{'x'},    // Expected side cross order
                      vector<char>{'x'},    // Expected reverse order
                      vector<char>{'x'},    // Expected insertion order
                      vector<char>{'x'});   // Expected middle out order
    }

    SUBCASE("Duplicate elements") {  // Tests container with duplicate elements
        MyContainer<char> c;  // Creates char container
        c.addElement('a');    // Adds element 'a'
        c.addElement('a');    // Adds element 'a' again
        c.addElement('a');    // Adds element 'a' again
        c.addElement('a');    // Adds element 'a' again
        c.addElement('a');    // Adds element 'a' again

        testIterators(c,  // Tests all iterator types
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // Expected ascending order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // Expected descending order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // Expected side cross order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // Expected reverse order
                      vector<char>{'a', 'a', 'a', 'a', 'a'},    // Expected insertion order
                      vector<char>{'a', 'a', 'a', 'a', 'a'});   // Expected middle out order
    }

    SUBCASE("Large container") {  // Tests container with many elements
        MyContainer<char> c;  // Creates char container
        vector<char> insertion_order;  // Tracks insertion order
        for (int i = 0; i < 10; ++i) {  // Loops to add 10 elements
            char val = static_cast<char>('a' + (i % 10));  // Generates value a-j
            c.addElement(val);  // Adds element to container
            insertion_order.push_back(val);  // Records element in insertion order
        }
        CHECK(c.size() == 10);  // Verifies container size

        vector<char> expected_asc = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};  // Defines expected ascending order
        vector<char> expected_desc = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};  // Defines expected descending order
        vector<char> expected_side = {'a', 'j', 'b', 'i', 'c', 'h', 'd', 'g', 'e', 'f'};  // Defines expected side cross order
        vector<char> expected_rev = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};  // Defines expected reverse order
        vector<char> expected_mid = {'f', 'e', 'g', 'd', 'h', 'c', 'i', 'b', 'j', 'a'};  // Defines expected middle out order

        testIterators(c,  // Tests all iterator types
                      expected_asc,           // Expected ascending order
                      expected_desc,          // Expected descending order
                      expected_side,          // Expected side cross order
                      expected_rev,           // Expected reverse order
                      insertion_order,        // Expected insertion order
                      expected_mid);          // Expected middle out order
    }
}

// Tests iterator traversal orders with float elements
// This test case verifies that all iterator types produce the expected order
// for various float container configurations using the testIterators helper function.
TEST_CASE("Iterators with float") {  // Tests iterators with floats
    SUBCASE("Odd-sized container") {  // Tests container with odd number of elements
        MyContainer<float> c;  // Creates float container
        c.addElement(3.1f);  // Adds element 3.1
        c.addElement(1.2f);  // Adds element 1.2
        c.addElement(2.3f);  // Adds element 2.3
        c.addElement(4.4f);  // Adds element 4.4
        c.addElement(0.5f);  // Adds element 0.5

        testIterators(c,  // Tests all iterator types
                      vector<float>{0.5f, 1.2f, 2.3f, 3.1f, 4.4f},    // Expected ascending order
                      vector<float>{4.4f, 3.1f, 2.3f, 1.2f, 0.5f},    // Expected descending order
                      vector<float>{0.5f, 4.4f, 1.2f, 3.1f, 2.3f},    // Expected side cross order
                      vector<float>{0.5f, 4.4f, 2.3f, 1.2f, 3.1f},    // Expected reverse order
                      vector<float>{3.1f, 1.2f, 2.3f, 4.4f, 0.5f},    // Expected insertion order
                      vector<float>{2.3f, 1.2f, 4.4f, 3.1f, 0.5f});   // Expected middle out order
    }

    SUBCASE("Even-sized container") {  // Tests container with even number of elements
        MyContainer<float> c;  // Creates float container
        c.addElement(1.0f);  // Adds element 1.0
        c.addElement(2.0f);  // Adds element 2.0
        c.addElement(3.0f);  // Adds element 3.0
        c.addElement(4.0f);  // Adds element 4.0
        c.addElement(5.0f);  // Adds element 5.0
        c.addElement(6.0f);  // Adds element 6.0

        testIterators(c,  // Tests all iterator types
                      vector<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},    // Expected ascending order
                      vector<float>{6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f},    // Expected descending order
                      vector<float>{1.0f, 6.0f, 2.0f, 5.0f, 3.0f, 4.0f},    // Expected side cross order
                      vector<float>{6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f},    // Expected reverse order
                      vector<float>{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},    // Expected insertion order
                      vector<float>{4.0f, 3.0f, 5.0f, 2.0f, 6.0f, 1.0f});   // Expected middle out order
    }

    SUBCASE("Empty container") {  // Tests empty container
        MyContainer<float> c;  // Creates empty float container

        testIterators(c,  // Tests all iterator types
                      vector<float>{},    // Expected ascending order
                      vector<float>{},    // Expected descending order
                      vector<float>{},    // Expected side cross order
                      vector<float>{},    // Expected reverse order
                      vector<float>{},    // Expected insertion order
                      vector<float>{});   // Expected middle out order
    }

    SUBCASE("Single element") {  // Tests container with a single element
        MyContainer<float> c;  // Creates float container
        c.addElement(1.5f);  // Adds element 1.5

        testIterators(c,  // Tests all iterator types
                      vector<float>{1.5f},    // Expected ascending order
                      vector<float>{1.5f},    // Expected descending order
                      vector<float>{1.5f},    // Expected side cross order
                      vector<float>{1.5f},    // Expected reverse order
                      vector<float>{1.5f},    // Expected insertion order
                      vector<float>{1.5f});   // Expected middle out order
    }

    SUBCASE("Duplicate elements") {  // Tests container with duplicate elements
        MyContainer<float> c;  // Creates float container
        c.addElement(2.5f);  // Adds element 2.5
        c.addElement(2.5f);  // Adds element 2.5 again
        c.addElement(2.5f);  // Adds element 2.5 again
        c.addElement(2.5f);  // Adds element 2.5 again
        c.addElement(2.5f);  // Adds element 2.5 again

        testIterators(c,  // Tests all iterator types
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // Expected ascending order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // Expected descending order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // Expected side cross order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // Expected reverse order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f},    // Expected insertion order
                      vector<float>{2.5f, 2.5f, 2.5f, 2.5f, 2.5f});   // Expected middle out order
    }

    SUBCASE("Large container") {  // Tests container with many elements
        MyContainer<float> c;  // Creates float container
        vector<float> insertion_order;  // Tracks insertion order
        for (int i = 0; i < 10; ++i) {  // Loops to add 10 elements
            float val = static_cast<float>(i % 10) + 0.1f;  // Generates float value
            c.addElement(val);  // Adds element to container
            insertion_order.push_back(val); // // Records element in insertion order
        }
        CHECK(c.size() == 10);  // Verifies container size

        vector<float> expected_asc = {0.1f, 1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f, 9.1f}; // // Defines expected ascending order
        vector<float> expected_desc = {9.1f, 8.1f, 7.1f, 6.1f, 5.1f, 4.1f, 3.1f, 2.1f, 1.1f, 0.1f}; // // Defines expected descending order
        vector<float> expected_side = {0.1f, 9.1f, 1.1f, 8.1f, 2.1f, 7.1f, 3.1f, 6.1f, 4.1f, 5.1f}; // // Defines expected side cross order
        vector<float> expected_rev = {9.1f, 8.1f, 7.1f, 6.1f, 5.1f, 4.1f, 3.1f, 2.1f, 1.1f, 0.1f}; // // Defines expected reverse order
        vector<float> expected_mid = {5.1f, 4.1f, 6.1f, 3.1f, 7.1f, 2.1f, 8.1f, 1.1f, 9.1f, 0.1f}; // // Defines expected middle out order

        testIterators(c,  // Tests all iterator types
                      expected_asc,           // Expected ascending order
                      expected_desc,          // Expected descending order
                      expected_side,          // Expected side cross order
                      expected_rev,           // Expected reverse order
                      insertion_order,    // Expected insertion order
                      expected_mid);          // Expected middle out order
    }
}