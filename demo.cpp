//noa.honigstein@gmail.com

#include <iostream>
#include "../include/MyContainer.hpp"
using namespace container;

int main() {
    
    // =============================================================================
    // INTEGER CONTAINER DEMO
    // =============================================================================
    std::cout << "=== INTEGER CONTAINER ===" << std::endl;
    MyContainer<int> intContainer;
    intContainer.add(7);
    intContainer.add(15);
    intContainer.add(6);
    intContainer.add(1);
    intContainer.add(2);
    
    std::cout << "Size of container: " << intContainer.size() << std::endl;
    std::cout << "Container: " << intContainer << std::endl;
    
    std::cout << "Ascending order: ";
    for (auto it = intContainer.begin_ascending_order(); it != intContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1 2 6 7 15
    }
    std::cout << std::endl;
    
    std::cout << "Descending order: ";
    for (auto it = intContainer.begin_descending_order(); it != intContainer.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 15 7 6 2 1
    }
    std::cout << std::endl;
    
    std::cout << "Side cross order: ";
    for (auto it = intContainer.begin_side_cross_order(); it != intContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1 15 2 7 6
    }
    std::cout << std::endl;
    
    std::cout << "Reverse order: ";
    for (auto it = intContainer.begin_reverse_order(); it != intContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 2 1 6 15 7
    }
    std::cout << std::endl;
    
    std::cout << "Normal order: ";
    for (auto it = intContainer.begin_order(); it != intContainer.end_order(); ++it) {
        std::cout << *it << ' ';  // 7 15 6 1 2
    }
    std::cout << std::endl;
    
    std::cout << "Middle out order: ";
    for (auto it = intContainer.begin_middle_out_order(); it != intContainer.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 6 15 1 7 2
    }
    std::cout << std::endl;
    
    // =============================================================================
    // STRING CONTAINER DEMO
    // =============================================================================
    std::cout << "\n=== STRING CONTAINER ===" << std::endl;
    MyContainer<std::string> stringContainer;
    stringContainer.add("zebra");
    stringContainer.add("apple");
    stringContainer.add("dog");
    stringContainer.add("cat");
    stringContainer.add("bird");
    
    std::cout << "Size of container: " << stringContainer.size() << std::endl;
    std::cout << "Container: " << stringContainer << std::endl;
    
    std::cout << "Ascending order: ";
    for (auto it = stringContainer.begin_ascending_order(); it != stringContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // apple bird cat dog zebra
    }
    std::cout << std::endl;
    
    std::cout << "Descending order: ";
    for (auto it = stringContainer.begin_descending_order(); it != stringContainer.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // zebra dog cat bird apple
    }
    std::cout << std::endl;
    
    std::cout << "Side cross order: ";
    for (auto it = stringContainer.begin_side_cross_order(); it != stringContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // apple zebra bird dog cat
    }
    std::cout << std::endl;
    
    std::cout << "Reverse order: ";
    for (auto it = stringContainer.begin_reverse_order(); it != stringContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // bird cat dog apple zebra
    }
    std::cout << std::endl;
    
    std::cout << "Normal order: ";
    for (auto it = stringContainer.begin_order(); it != stringContainer.end_order(); ++it) {
        std::cout << *it << ' ';  // zebra apple dog cat bird
    }
    std::cout << std::endl;
    
    std::cout << "Middle out order: ";
    for (auto it = stringContainer.begin_middle_out_order(); it != stringContainer.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // dog apple cat zebra bird
    }
    std::cout << std::endl;
    
    // =============================================================================
    // DOUBLE CONTAINER DEMO
    // =============================================================================
    std::cout << "\n=== DOUBLE CONTAINER ===" << std::endl;
    MyContainer<double> doubleContainer;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.add(9.81);
    doubleContainer.add(1.41);
    doubleContainer.add(6.28);
    
    std::cout << "Size of container: " << doubleContainer.size() << std::endl;
    std::cout << "Container: " << doubleContainer << std::endl;
    
    std::cout << "Ascending order: ";
    for (auto it = doubleContainer.begin_ascending_order(); it != doubleContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1.41 2.71 3.14 6.28 9.81
    }
    std::cout << std::endl;
    
    std::cout << "Descending order: ";
    for (auto it = doubleContainer.begin_descending_order(); it != doubleContainer.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 9.81 6.28 3.14 2.71 1.41
    }
    std::cout << std::endl;
    
    std::cout << "Side cross order: ";
    for (auto it = doubleContainer.begin_side_cross_order(); it != doubleContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1.41 9.81 2.71 6.28 3.14
    }
    std::cout << std::endl;
    
    std::cout << "Reverse order: ";
    for (auto it = doubleContainer.begin_reverse_order(); it != doubleContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 6.28 1.41 9.81 2.71 3.14
    }
    std::cout << std::endl;
    
    std::cout << "Normal order: ";
    for (auto it = doubleContainer.begin_order(); it != doubleContainer.end_order(); ++it) {
        std::cout << *it << ' ';  // 3.14 2.71 9.81 1.41 6.28
    }
    std::cout << std::endl;
    
    std::cout << "Middle out order: ";
    for (auto it = doubleContainer.begin_middle_out_order(); it != doubleContainer.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 9.81 2.71 1.41 3.14 6.28
    }
    std::cout << std::endl;
    
    return 0;
}