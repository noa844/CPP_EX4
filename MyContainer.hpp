#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace container {

template<typename T = int>
class MyContainer {
private:
    std::vector<T> data;

public:
    MyContainer() = default;

    ~MyContainer() = default;

    
    void add(const T& value) {
        data.push_back(value);
    }

    
    void remove(const T& value) {
        bool found = false;
        auto it = data.begin();
        for (auto it = data.begin(); it != data.end(); ) {
            if (*it == value) {
                it = data.erase(it); 
                found = true;
            } else {
                ++it;
            }
        }        
        if (!found) {
            throw std::runtime_error("Element not found in container.");
        }
    }

 
    size_t size() const {
        return data.size();
    }

    
    const std::vector<T>& getData() const {
        return data;
    }

   
    friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
        os << "[ ";
        for (size_t i = 0; i < container.data.size(); ++i) {
            os << container.data[i];
            if (i + 1 < container.data.size()) {
                os << ", ";
            }
        }
        os << " ]";
        return os;
    }
    

    
};

} 
