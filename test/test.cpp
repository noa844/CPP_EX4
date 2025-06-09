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
