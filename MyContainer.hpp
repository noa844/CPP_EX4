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

            class AscendingIterator;
            
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



class AscendingIterator {
    private:
        std::vector<T> sorted_data;
        size_t index;
    
    public:
        // Constructor for begin()
        AscendingIterator(const std::vector<T>& original_data): sorted_data(original_data), index(0) {
            std::sort(sorted_data.begin(), sorted_data.end());
        }

        // Constructor for end()
        AscendingIterator(const std::vector<T>& original_data, size_t end_index): sorted_data(original_data), index(end_index) {
            std::sort(sorted_data.begin(), sorted_data.end());
        }
    
        const T& operator*() const {
            return sorted_data.at(index);
        }
    
        AscendingIterator& operator++() {
            ++index;
            return *this;
        }
    
        bool operator!=(const AscendingIterator& other) const {
            return index != other.index || sorted_data != other.sorted_data;
        }
    
        bool operator==(const AscendingIterator& other) const {
            return !(*this != other);
        }
    };
    
    AscendingIterator begin_ascending_order() const {
        return AscendingIterator(data);
    }
    
    AscendingIterator end_ascending_order() const {
        return AscendingIterator(data, data.size());
    }
    
        
    };

} 
