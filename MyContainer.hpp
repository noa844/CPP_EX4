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
  
            const std::vector<T>& getData() const { //for testing
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
        AscendingIterator(const std::vector<T>& originalData):sortedData(originalData), index(0) {
            std::sort(sortedData.begin(), sortedData.end());
        }

        // Constructor for end()
        AscendingIterator(const std::vector<T>& originalData, size_t endIndex):sortedData(originalData), index(endIndex) {
            std::sort(sortedData.begin(), sortedData.end());
        }
        
        const T& operator*() const {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Attempted to desourceerence AscendingIterator beyond the end.");
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
                throw std::runtime_error("Attempted to desourceerence - DescendingIterator beyond the end.");
            }
            return sortedData.at(index);
        }

        DescendingIterator& operator++() {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Cannot increment - DescendingIterator past the end.");
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
            std::vector<T> sortedData;
            int left;
            int right;
            bool leftSide;
        
        public:
            SideCrossIterator(const std::vector<T>& original_data, bool is_end = false)
                : sortedData(original_data), left(0), right(0), leftSide(true) {
                std::sort(sortedData.begin(), sortedData.end());
                int n = static_cast<int>(sortedData.size());
                if (is_end) {
                    size_t mid = n / 2;
                    if( n % 2 == 0){
                        left = mid;
                        right = mid - 1;
                    }else{
                        left = mid + 1;
                        right = mid;
                    }
                    
                } else {
                    left = 0;
                    right = n - 1;
                }

            }
        
            const T& operator*() const {
                
                int n = static_cast<int>(sortedData.size());
                if (left > right || left >= n) {
                    throw std::runtime_error("Cannot desourceerence SideCrossIterator: out of range");
                }
         
                return leftSide ? sortedData[left] : sortedData[right];
            }
        
            SideCrossIterator& operator++() {
                int n = static_cast<int>(sortedData.size());
                if (left > right || left >= n) {
                    throw std::runtime_error("Cannot increment SideCrossIterator past the end.");
                }
        
                if (leftSide) {
                    ++left;
                } else {
                    --right;
                }
        
                leftSide = !leftSide;
                
                return *this;
            }

            bool operator!=(const SideCrossIterator& other) const {
               
                return left != other.left || right != other.right || sortedData != other.sortedData;
            }

            bool operator==(const SideCrossIterator& other) const {
                return !(*this != other);
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
            const std::vector<T>& source_data;
            size_t index;
        
        public:
            ReverseIterator(const std::vector<T>& data, bool is_end = false)
                : source_data(data) {
                index = is_end || data.empty() ? SIZE_MAX : data.size() - 1;
            }
        
            const T& operator*() const {
                if (source_data.empty() || index == SIZE_MAX || index >= source_data.size()) {
                    throw std::runtime_error("Cannot desourceerence ReverseIterator: out of range");
                }
                return source_data[index];
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
                return index != other.index || &source_data != &other.source_data;
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
        
           
    class OrderIterator {
        private:
            const std::vector<T>& source_data;
            size_t index;
        
        public:
            OrderIterator(const std::vector<T>& data, bool is_end = false)
                : source_data(data), index(is_end ? data.size() : 0) {}
        
            const T& operator*() const {
                if (index >= source_data.size()) {
                    throw std::runtime_error("Cannot desourceerence OrderIterator: out of range");
                }
                return source_data[index];
            }
        
            OrderIterator& operator++() {
                if (index >= source_data.size()) {
                    throw std::runtime_error("Cannot increment OrderIterator past the end.");
                }
                ++index;
                return *this;
            }
        
            bool operator!=(const OrderIterator& other) const {
                return index != other.index || &source_data != &other.source_data;
            }
        
            bool operator==(const OrderIterator& other) const {
                return !(*this != other);
            }
        };

        OrderIterator begin_order() const {
            return OrderIterator(data);
        }
        
        OrderIterator end_order() const {
            return OrderIterator(data, true);
        }
        
    class MiddleOutIterator {
        private:
            const std::vector<T>& sourceData;
            int left;
            size_t right;
            bool rightSide;

        public:
            MiddleOutIterator(const std::vector<T>& data, bool is_end = false)
                : sourceData(data), rightSide(true) {
                size_t n = data.size();
                if (n == 0 || is_end) {
                    left = -1;
                    right = n;
                }else if(n==1){
                    left = 0;
                    right = 0;
                } else {
                    size_t middle = n / 2;
                    right = middle;
                    left = static_cast<int>(middle) - 1;
                }

               
            }

            const T& operator*() const {
                
                
                if (left < 0 && right >= sourceData.size()) {
                    throw std::runtime_error("MiddleOutIterator: index out of bounds");
                }
                size_t index = rightSide ? right : static_cast<size_t>(left);
                return sourceData.at(index);
            }

            MiddleOutIterator& operator++() {
                
                if (left < 0 && right >= sourceData.size()) {
                    throw std::runtime_error("Cannot increment MiddleOutIterator past the end.");
                }

                if (rightSide) {
                    ++right;
                    if (sourceData.size() == 1 && right == 1){ //handle size is 1.
                        --left;
                    }
                } else {
                    --left;
                }
                

                rightSide = !rightSide;
                return *this;
            }

            bool operator!=(const MiddleOutIterator& other) const {
                return left != other.left || right != other.right || &sourceData != &other.sourceData;
            }

            bool operator==(const MiddleOutIterator& other) const {
                return !(*this != other);
            }

            
    };
    MiddleOutIterator begin_middle_out_order() const {
        return MiddleOutIterator(data);
    }
    
    MiddleOutIterator end_middle_out_order() const {
        return MiddleOutIterator(data, true);
    }
       
};


} 
