#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstddef>

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
        std::vector<T> sortedData;
        size_t index;
        
    public:
        // Constructor for begin()
        AscendingIterator(const std::vector<T>& originalData): sortedData(originalData), index(0) {
            std::sort(sortedData.begin(), sortedData.end());
        }

        // Constructor for end()
        AscendingIterator(const std::vector<T>& originalData, size_t endIndex): sortedData(originalData), index(endIndex) {
            std::sort(sortedData.begin(), sortedData.end());
        }
        
        const T& operator*() const {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Attempted to dereference AscendingIterator beyond the end.");
            }
            return sortedData.at(index);
        }

        AscendingIterator& operator++() {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Cannot increment - AscendingIterator past the end.");
            }
            ++index;
            return *this;
        }
        
        bool operator!=(const AscendingIterator& other) const {
            return index != other.index || sortedData != other.sortedData;
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
    
    class DescendingIterator {
    private:
        std::vector<T> sortedData;
        size_t index;

    public:
        DescendingIterator(const std::vector<T>& originalData): sortedData(originalData), index(0) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        DescendingIterator(const std::vector<T>& originalData, size_t endIndex): sortedData(originalData), index(endIndex) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        const T& operator*() const {
            if (index >= sortedData.size()) {
                throw std::out_of_range("Attempted to dereference - DescendingIterator beyond the end.");
            }
            return sortedData.at(index);
        }

        DescendingIterator& operator++() {
            if (index >= sortedData.size()) {
                throw std::logic_error("Cannot increment - DescendingIterator past the end.");
            }
            ++index;
            return *this;
        }

        bool operator!=(const DescendingIterator& other) const {
            return index != other.index || sortedData != other.sortedData;
        }

        bool operator==(const DescendingIterator& other) const {
            return !(*this != other);
        }
    };

    DescendingIterator begin_descending_order() const {
        return DescendingIterator(data);
    }
    
    DescendingIterator end_descending_order() const {
        return DescendingIterator(data, data.size());
    }

    class SideCrossIterator {
        private:
            std::vector<T> sorted_data;
            size_t left;
            size_t right;
            bool leftSide;
        
        public:
            SideCrossIterator(const std::vector<T>& original_data, bool is_end = false)
                : sorted_data(original_data), left(0), right(0), leftSide(true) {
                std::sort(sorted_data.begin(), sorted_data.end());
                
                if (sorted_data.empty()) {
                    left = 1;
                    right = 0;
                    return;
                }
        
                if (is_end) {
                    // This sets the state to "past the end"
                    left = sorted_data.size();
                    right = 0;
                } else {
                    left = 0;
                    right = sorted_data.size() - 1;
                }
            }
        
            const T& operator*() const {
               
                if (left > right || left >= sorted_data.size()) {
                    throw std::out_of_range("Cannot dereference SideCrossIterator: out of range");
                }
         
                return leftSide ? sorted_data[left] : sorted_data[right];
            }
        
            SideCrossIterator& operator++() {
        
                if (left > right || left >= sorted_data.size()) {
                    throw std::logic_error("Cannot increment SideCrossIterator past the end.");
                }
        
                if (leftSide) {
                    ++left;
                } else {
                    --right;
                }
        
                leftSide = !leftSide;
                return *this;
            }

            bool is_done() const {
                return left > right;
            }            
        
            bool operator!=(const SideCrossIterator& other) const {
                return !is_done();
            }
            bool operator==(const SideCrossIterator& other) const {
                return is_done();
            }
            
    };

    SideCrossIterator begin_side_cross_order() const {
        return SideCrossIterator(data); 
    }
    
    SideCrossIterator end_side_cross_order() const {
        return SideCrossIterator(data, true);
    }

    class ReverseIterator {
        private:
            const std::vector<T>& ref_data;
            size_t index;
        
        public:
            ReverseIterator(const std::vector<T>& data, bool is_end = false)
                : ref_data(data) {
                index = is_end || data.empty() ? SIZE_MAX : data.size() - 1;
            }
        
            const T& operator*() const {
                if (ref_data.empty() || index >= ref_data.size()) {
                    throw std::out_of_range("Cannot dereference ReverseIterator: out of range");
                }
                return ref_data[index];
            }
        
            ReverseIterator& operator++() {
                if (index == 0) {
                    index = SIZE_MAX;
                } else {
                    --index;
                }
                return *this;
            }
        
            bool operator!=(const ReverseIterator& other) const {
                return index != other.index || &ref_data != &other.ref_data;
            }
        
            bool operator==(const ReverseIterator& other) const {
                return !(*this != other);
            }
    };
    
    ReverseIterator begin_reverse_order() const {
        return ReverseIterator(data);
    }
    
    ReverseIterator end_reverse_order() const {
        return ReverseIterator(data, true);
    }
        
           

};

} 
