#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../MyContainer.hpp"
#include <string>
#include <sstream>
using namespace container;

TEST_CASE("MyContainer with int") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    CHECK(c.size() == 2);
    c.remove(1);
    CHECK(c.size() == 1);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ 2 ]");
}

TEST_CASE("MyContainer with double") {
    MyContainer<double> c;
    c.add(3.14);
    c.add(2.71);
    c.add(3.14);
    CHECK(c.size() == 3);

    c.remove(3.14); // remove all occurrences
    CHECK(c.size() == 1);
    CHECK(c.getData()[0] == 2.71);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ 2.71 ]");
}

TEST_CASE("MyContainer with string") {
    MyContainer<std::string> c;
    c.add("hello");
    c.add("world");
    c.add("hello");
    c.add("world");


    CHECK(c.size() == 4);
    c.remove("hello");
    CHECK(c.size() == 2);

    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[ world, world ]");
}

TEST_CASE("Removing a non-existing string throws") {
    MyContainer<std::string> c;
    c.add("hello");
    CHECK_THROWS_WITH(c.remove("CS"), "Element not found in container.");
}

TEST_CASE("AscendingIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_ascending_order();
    auto end = c.end_ascending_order();
    CHECK(it == end); // both should point to the end
    std::ostringstream oss;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
        oss << *it << " "; // this should never run
    }

    CHECK(oss.str() == "");
}

TEST_CASE("AscendingIterator: multiple elements") {
    MyContainer<int> c;
    c.add(5);
    c.add(1);
    c.add(8);
    c.add(3);

    std::vector<int> expected = {1, 3, 5, 8};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("AscendingIterator: stability after remove") {
    MyContainer<int> c;
    c.add(7);
    c.add(3);
    c.add(5);
    c.remove(3); // remove the smallest

    std::vector<int> expected = {5, 7};
    size_t i = 0;
    for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("AscendingIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.end_ascending_order();
    CHECK_THROWS_WITH(*it, "Attempted to desourceerence AscendingIterator beyond the end.");
}

TEST_CASE("AscendingIterator: incrementing past end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.begin_ascending_order();
    ++it; // now at end
    CHECK_THROWS_WITH(++it, "Cannot increment - AscendingIterator past the end.");
}



TEST_CASE("DescendingIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_descending_order();
    auto end = c.end_descending_order();
    CHECK(it == end); // nothing to iterate

    std::ostringstream oss;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        oss << *it << " "; // this should never run
    }

    CHECK(oss.str() == "");
}

TEST_CASE("DescendingIterator: one element") {
    MyContainer<int> c;
    c.add(42);

    std::ostringstream oss;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
        oss << *it << " ";
    }
    CHECK(oss.str() == "42 ");
}

TEST_CASE("DescendingIterator: multiple elements") {
    MyContainer<int> c;
    c.add(4);
    c.add(10);
    c.add(2);
    c.add(7);

    std::vector<int> expected = {10, 7, 4, 2};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("DescendingIterator: after removing max") {
    MyContainer<int> c;
    c.add(3);
    c.add(8);
    c.add(5);
    c.remove(8); // remove the largest value

    std::vector<int> expected = {5, 3};
    size_t i = 0;
    for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}
TEST_CASE("DescendingIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.end_descending_order();
    CHECK_THROWS_WITH(*it, "Attempted to desourceerence - DescendingIterator beyond the end.");
}

TEST_CASE("DescendingIterator: incrementing past end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.begin_descending_order();
    ++it; 
    CHECK_THROWS_WITH(++it, "Cannot increment - DescendingIterator past the end.");
}


TEST_CASE("SideCrossIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_side_cross_order();
    auto end = c.end_side_cross_order();
    CHECK(it == end); // nothing to iterate

    std::ostringstream oss;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        oss << *it << " "; // this should never run
    }

    CHECK(oss.str() == "");
}



TEST_CASE("SideCrossIterator: one element") {
    MyContainer<int> c;
    c.add(5);

    std::ostringstream oss;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
        oss << *it << " ";
    }
    CHECK(oss.str() == "5 ");
}

TEST_CASE("SideCrossIterator: even number of elements") {
    MyContainer<int> c;
    c.add(10);
    c.add(1);
    c.add(7);
    c.add(3);

    // sorted: [1, 3, 7, 10]
    // side-cross: 1, 10, 3, 7
    std::vector<int> expected = {1, 10, 3, 7};
    size_t i = 0;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("SideCrossIterator: odd number of elements") {
    MyContainer<int> c;
    c.add(2);
    c.add(9);
    c.add(5);
    c.add(1);
    c.add(7);

    // sorted: [1, 2, 5, 7, 9]
    // side-cross: 1, 9, 2, 7, 5
    std::vector<int> expected = {1, 9, 2, 7, 5};
    size_t i = 0;
    for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("SideCrossIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.end_side_cross_order();
    CHECK_THROWS_WITH(*it, "Cannot desourceerence SideCrossIterator: out of range");
}

TEST_CASE("SideCrossIterator: incrementing past end throws") {
    MyContainer<int> c;
    c.add(3);
    auto it = c.begin_side_cross_order();
    ++it; // moves to end if only one element
    CHECK_THROWS_WITH(++it, "Cannot increment SideCrossIterator past the end.");
}

TEST_CASE("ReverseIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_reverse_order();
    auto end = c.end_reverse_order();
    CHECK(it == end); // nothing to iterate
    CHECK_THROWS_WITH(*it, "Cannot desourceerence ReverseIterator: out of range");

    std::ostringstream oss;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        oss << *it << " "; // this should never run
    }

    CHECK(oss.str() == "");
}

TEST_CASE("ReverseIterator: one element") {
    MyContainer<int> c;
    c.add(42);

    std::ostringstream oss;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
        
        oss << *it << " ";
    }
    CHECK(oss.str() == "42 ");
}

TEST_CASE("ReverseIterator: multiple elements") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    std::vector<int> expected = {3, 2, 1};
    size_t i = 0;
    for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("ReverseIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(5);
    auto it = c.begin_reverse_order();
    ++it;
    CHECK_THROWS_WITH(*it, "Cannot desourceerence ReverseIterator: out of range");

    auto end = c.end_reverse_order();
    CHECK_THROWS_WITH(*end, "Cannot desourceerence ReverseIterator: out of range");

}

TEST_CASE("ReverseIterator: incrementing past end throws nothing (it's allowed)") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.begin_reverse_order();
    ++it; // should move to end
    CHECK(it == c.end_reverse_order());
}


TEST_CASE("OrderIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_order();
    auto end = c.end_order();
    CHECK(it == end); // should not iterate
    CHECK_THROWS_WITH(*it, "Cannot desourceerence OrderIterator: out of range");

    std::ostringstream oss;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        oss << *it << " "; // this should never run
    }

    CHECK(oss.str() == "");
}

TEST_CASE("OrderIterator: one element") {
    MyContainer<int> c;
    c.add(11);

    std::ostringstream oss;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        oss << *it << " ";
    }
    CHECK(oss.str() == "11 ");
}

TEST_CASE("OrderIterator: multiple elements") {
    MyContainer<int> c;
    c.add(1);
    c.add(4);
    c.add(9);

    std::vector<int> expected = {1, 4, 9};
    size_t i = 0;
    for (auto it = c.begin_order(); it != c.end_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("OrderIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(77);
    auto it = c.end_order();
    CHECK_THROWS_WITH(*it, "Cannot desourceerence OrderIterator: out of range");
}

TEST_CASE("OrderIterator: incrementing past end throws") {
    MyContainer<int> c;
    c.add(5);
    auto it = c.begin_order();
    ++it;
    CHECK_THROWS_WITH(++it, "Cannot increment OrderIterator past the end.");
}

TEST_CASE("MiddleOutIterator: empty container") {
    MyContainer<int> c;
    auto it = c.begin_middle_out_order();
    auto end = c.end_middle_out_order();
    CHECK(it == end);

    std::ostringstream oss;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        oss << *it << " ";
    }
    CHECK(oss.str() == "");
}

TEST_CASE("MiddleOutIterator: one element") {
    MyContainer<int> c;
    c.add(42);

    std::ostringstream oss;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
        oss << *it << " ";
    }
    CHECK(oss.str() == "42 ");
}

TEST_CASE("MiddleOutIterator: odd number of elements") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    c.add(4);
    c.add(5);

    std::vector<int> expected = {3, 2, 4, 1, 5};
    size_t i = 0;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("MiddleOutIterator: even number of elements") {
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    c.add(30);
    c.add(40);

    std::vector<int> expected = {30, 20, 40, 10};
    size_t i = 0;
    for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
}

TEST_CASE("MiddleOutIterator: dereferencing end throws") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.begin_middle_out_order();
    ++it; // moves to end
    CHECK_THROWS_WITH(*it, "MiddleOutIterator: index out of bounds");
}
TEST_CASE("MiddleOutIterator: incrementing past end throws") {
    MyContainer<int> c;
    c.add(5);
    c.add(1);
    c.add(1);

    auto it = c.begin_middle_out_order();
    ++it;
    ++it;
    ++it;
    CHECK_THROWS_WITH(++it, "Cannot increment MiddleOutIterator past the end.");
}



