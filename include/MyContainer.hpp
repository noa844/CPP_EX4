//noa.honigstein@gmail.com
#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstddef>

namespace container {

    /**
     * @brief A generic container class that provides various iteration patterns over stored elements.
     * 
     * This template class wraps a std::vector and provides multiple ways to iterate through
     * the elements including ascending, descending, side-cross, reverse, middle-out, and normal order.
     * All sorting operations are performed on copies of the data to preserve the original order.
     * 
     * @tparam T The type of elements to store (defaults to int)
     */
    template<typename T = int>
    class MyContainer {
        private:
            std::vector<T> data; ///< Internal storage vector for container elements

        public:
    
            /**
             * @brief Default constructor.
             * 
             * Creates an empty container with no elements.
             */
            MyContainer() = default;

            /**
             * @brief Default destructor.
             * 
             * Automatically cleans up all stored elements.
             */
            ~MyContainer() = default;
            
            /**
             * @brief Adds an element to the container.
             * 
             * @param value The value to add to the container (passed by const reference)
             */
            void add(const T& value) {
                data.push_back(value);
            }

            /**
             * @brief Removes all occurrences of a specific value from the container.
             * 
             * This method removes every instance of the specified value found in the container.
             * If the value is not found, it throws a runtime_error exception.
             * 
             * @param value The value to remove from the container (passed by const reference)
             * @throws std::runtime_error If the element is not found in the container
             */
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

            /**
             * @brief Returns the number of elements in the container.
             * 
             * @return size_t The current size of the container
             */
            size_t size() const {
                return data.size();
            }
  
            /**
             * @brief Provides read-only access to the internal data vector.
             * 
             * This method is primarily intended for testing purposes to access
             * the underlying vector without modification capabilities.
             * 
             * @return const std::vector<T>& A const reference to the internal data vector
             */
            const std::vector<T>& getData() const { //for testing
                return data;
            }
            
        /**
         * @brief Stream insertion operator for printing the container.
         * 
         * Outputs the container contents in the format: [ element1, element2, ... ]
         * 
         * @param os The output stream to write to
         * @param container The container to output
         * @return std::ostream& Reference to the output stream for chaining
         */
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



    /**
     * @brief Iterator class for traversing elements in ascending sorted order.
     * 
     * This iterator creates a sorted copy of the container data and allows
     * forward iteration through elements in ascending order. The original
     * container data remains unchanged.
     */
    class AscendingIterator {
    private:
        std::vector<T> sortedData; ///< Sorted copy of the container data
        size_t index; ///< Current position in the sorted data
        
    public:
        /**
         * @brief Constructor for begin() iterator.
         * 
         * Creates an iterator pointing to the smallest element in the container.
         * Makes a copy of the original data and sorts it in ascending order.
         * 
         * @param originalData The container's data vector to iterate over
         */
        AscendingIterator(const std::vector<T>& originalData):sortedData(originalData), index(0) {
            std::sort(sortedData.begin(), sortedData.end());
        }

        /**
         * @brief Constructor for end() iterator.
         * 
         * Creates an iterator representing the end position for comparison purposes.
         * 
         * @param originalData The container's data vector
         * @param endIndex The index representing the end position (typically size())
         */
        AscendingIterator(const std::vector<T>& originalData, size_t endIndex):sortedData(originalData), index(endIndex) {
            std::sort(sortedData.begin(), sortedData.end());
        }
        
        /**
         * @brief Dereference operator to access current element.
         * 
         * @return const T& Reference to the current element
         * @throws std::runtime_error If attempting to dereference beyond the end
         */
        const T& operator*() const {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Attempted to desourceerence AscendingIterator beyond the end.");
            }
            return sortedData.at(index);
        }

        /**
         * @brief Pre-increment operator to move to next element.
         * 
         * @return AscendingIterator& Reference to this iterator after incrementing
         * @throws std::runtime_error If attempting to increment past the end
         */
        AscendingIterator& operator++() {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Cannot increment - AscendingIterator past the end.");
            }
            ++index;
            return *this;
        }
        
        /**
         * @brief Inequality comparison operator.
         * 
         * @param other The other iterator to compare with
         * @return bool True if iterators are not equal, false otherwise
         */
        bool operator!=(const AscendingIterator& other) const {
            return index != other.index || sortedData != other.sortedData;
        }
        
        /**
         * @brief Equality comparison operator.
         * 
         * @param other The other iterator to compare with
         * @return bool True if iterators are equal, false otherwise
         */
        bool operator==(const AscendingIterator& other) const {
            return !(*this != other);
        }
    };
        
    /**
     * @brief Creates an iterator pointing to the beginning of ascending order traversal.
     * 
     * @return AscendingIterator Iterator pointing to the smallest element
     */
    AscendingIterator begin_ascending_order() const {
        return AscendingIterator(data);
    }
    
    /**
     * @brief Creates an iterator pointing to the end of ascending order traversal.
     * 
     * @return AscendingIterator Iterator representing the end position
     */
    AscendingIterator end_ascending_order() const {
        return AscendingIterator(data, data.size());
    }
    
    /**
     * @brief Iterator class for traversing elements in descending sorted order.
     * 
     * This iterator creates a sorted copy of the container data in descending order
     * and allows forward iteration through elements from largest to smallest.
     * The original container data remains unchanged.
     */
    class DescendingIterator {
    private:
        std::vector<T> sortedData; ///< Sorted copy of the container data in descending order
        size_t index; ///< Current position in the sorted data

    public:
        /**
         * @brief Constructor for begin() iterator.
         * 
         * Creates an iterator pointing to the largest element in the container.
         * Makes a copy of the original data and sorts it in descending order.
         * 
         * @param originalData The container's data vector to iterate over
         */
        DescendingIterator(const std::vector<T>& originalData): sortedData(originalData), index(0) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        /**
         * @brief Constructor for end() iterator.
         * 
         * Creates an iterator representing the end position for comparison purposes.
         * 
         * @param originalData The container's data vector
         * @param endIndex The index representing the end position (typically size())
         */
        DescendingIterator(const std::vector<T>& originalData, size_t endIndex): sortedData(originalData), index(endIndex) {
            std::sort(sortedData.begin(), sortedData.end(), std::greater<T>());
        }

        /**
         * @brief Dereference operator to access current element.
         * 
         * @return const T& Reference to the current element
         * @throws std::runtime_error If attempting to dereference beyond the end
         */
        const T& operator*() const {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Attempted to desourceerence - DescendingIterator beyond the end.");
            }
            return sortedData.at(index);
        }

        /**
         * @brief Pre-increment operator to move to next element.
         * 
         * @return DescendingIterator& Reference to this iterator after incrementing
         * @throws std::runtime_error If attempting to increment past the end
         */
        DescendingIterator& operator++() {
            if (index >= sortedData.size()) {
                throw std::runtime_error("Cannot increment - DescendingIterator past the end.");
            }
            ++index;
            return *this;
        }

        /**
         * @brief Inequality comparison operator.
         * 
         * @param other The other iterator to compare with
         * @return bool True if iterators are not equal, false otherwise
         */
        bool operator!=(const DescendingIterator& other) const {
            return index != other.index || sortedData != other.sortedData;
        }

        /**
         * @brief Equality comparison operator.
         * 
         * @param other The other iterator to compare with
         * @return bool True if iterators are equal, false otherwise
         */
        bool operator==(const DescendingIterator& other) const {
            return !(*this != other);
        }
    };

    /**
     * @brief Creates an iterator pointing to the beginning of descending order traversal.
     * 
     * @return DescendingIterator Iterator pointing to the largest element
     */
    DescendingIterator begin_descending_order() const {
        return DescendingIterator(data);
    }
    
    /**
     * @brief Creates an iterator pointing to the end of descending order traversal.
     * 
     * @return DescendingIterator Iterator representing the end position
     */
    DescendingIterator end_descending_order() const {
        return DescendingIterator(data, data.size());
    }

    /**
     * @brief Iterator class for traversing elements alternating between smallest and largest values.
     * 
     * This iterator creates a sorted copy of the container data and alternates between
     * picking elements from the left (smallest) and right (largest) sides.
     * Pattern: smallest, largest, second smallest, second largest, etc.
     */
    class SideCrossIterator {
        private:
            std::vector<T> sortedData; ///< Sorted copy of the container data
            int left; ///< Index pointing to the left (smallest) side
            int right; ///< Index pointing to the right (largest) side
            bool leftSide; ///< Flag indicating which side to pick from next
        
        public:
            /**
             * @brief Constructor for begin() and end() iterators.
             * 
             * Creates an iterator that alternates between the smallest and largest remaining elements.
             * For begin(): starts with left=0, right=size-1
             * For end(): sets up termination conditions based on container size
             * 
             * @param original_data The container's data vector to iterate over
             * @param is_end True if this is an end iterator, false for begin iterator
             */
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
        
            /**
             * @brief Dereference operator to access current element.
             * 
             * @return const T& Reference to the current element (from left or right side)
             * @throws std::runtime_error If attempting to dereference when out of range
             */
            const T& operator*() const {
                
                int n = static_cast<int>(sortedData.size());
                if (left > right || left >= n) {
                    throw std::runtime_error("Cannot desourceerence SideCrossIterator: out of range");
                }
         
                return leftSide ? sortedData[left] : sortedData[right];
            }
        
            /**
             * @brief Pre-increment operator to move to next element.
             * 
             * Alternates between advancing left index and retreating right index.
             * Also toggles the leftSide flag to alternate between sides.
             * 
             * @return SideCrossIterator& Reference to this iterator after incrementing
             * @throws std::runtime_error If attempting to increment past the end
             */
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

            /**
             * @brief Inequality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are not equal, false otherwise
             */
            bool operator!=(const SideCrossIterator& other) const {
               
                return left != other.left || right != other.right || sortedData != other.sortedData;
            }

            /**
             * @brief Equality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are equal, false otherwise
             */
            bool operator==(const SideCrossIterator& other) const {
                return !(*this != other);
            }
            
    };

    /**
     * @brief Creates an iterator pointing to the beginning of side-cross order traversal.
     * 
     * @return SideCrossIterator Iterator that alternates between smallest and largest elements
     */
    SideCrossIterator begin_side_cross_order() const {
        return SideCrossIterator(data); 
    }
    
    /**
     * @brief Creates an iterator pointing to the end of side-cross order traversal.
     * 
     * @return SideCrossIterator Iterator representing the end position
     */
    SideCrossIterator end_side_cross_order() const {
        return SideCrossIterator(data, true);
    }

    /**
     * @brief Iterator class for traversing elements in reverse insertion order.
     * 
     * This iterator traverses the container elements from last inserted to first inserted,
     * preserving the original insertion order but in reverse direction.
     */
    class ReverseIterator {
        private:
            const std::vector<T>& source_data; ///< Reference to the original container data
            size_t index; ///< Current position (SIZE_MAX indicates end)
        
        public:
            /**
             * @brief Constructor for begin() and end() iterators.
             * 
             * For begin(): starts at the last element (size-1)
             * For end(): sets index to SIZE_MAX to indicate end position
             * 
             * @param data The container's data vector to iterate over
             * @param is_end True if this is an end iterator, false for begin iterator
             */
            ReverseIterator(const std::vector<T>& data, bool is_end = false)
                : source_data(data) {
                index = is_end || data.empty() ? SIZE_MAX : data.size() - 1;
            }
        
            /**
             * @brief Dereference operator to access current element.
             * 
             * @return const T& Reference to the current element
             * @throws std::runtime_error If attempting to dereference when out of range
             */
            const T& operator*() const {
                if (source_data.empty() || index == SIZE_MAX || index >= source_data.size()) {
                    throw std::runtime_error("Cannot desourceerence ReverseIterator: out of range");
                }
                return source_data[index];
            }
        
            /**
             * @brief Pre-increment operator to move to next element (previous in original order).
             * 
             * Decrements the index to move backwards through the original data.
             * When reaching index 0, sets index to SIZE_MAX to indicate end.
             * 
             * @return ReverseIterator& Reference to this iterator after incrementing
             */
            ReverseIterator& operator++() {
                if (index == 0) {
                    index = SIZE_MAX;
                } else {
                    --index;
                }
                return *this;
            }
        
            /**
             * @brief Inequality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are not equal, false otherwise
             */
            bool operator!=(const ReverseIterator& other) const {
                return index != other.index || &source_data != &other.source_data;
            }
        
            /**
             * @brief Equality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are equal, false otherwise
             */
            bool operator==(const ReverseIterator& other) const {
                return !(*this != other);
            }
    };
    
    /**
     * @brief Creates an iterator pointing to the beginning of reverse order traversal.
     * 
     * @return ReverseIterator Iterator pointing to the last inserted element
     */
    ReverseIterator begin_reverse_order() const {
        return ReverseIterator(data);
    }
    
    /**
     * @brief Creates an iterator pointing to the end of reverse order traversal.
     * 
     * @return ReverseIterator Iterator representing the end position
     */
    ReverseIterator end_reverse_order() const {
        return ReverseIterator(data, true);
    }
        
    /**
     * @brief Iterator class for traversing elements in original insertion order.
     * 
     * This iterator provides standard forward iteration through the container elements
     * in the same order they were inserted (first-in, first-out traversal).
     */       
    class OrderIterator {
        private:
            const std::vector<T>& source_data; ///< Reference to the original container data
            size_t index; ///< Current position in the data
        
        public:
            /**
             * @brief Constructor for begin() and end() iterators.
             * 
             * For begin(): starts at index 0
             * For end(): starts at index equal to container size
             * 
             * @param data The container's data vector to iterate over
             * @param is_end True if this is an end iterator, false for begin iterator
             */
            OrderIterator(const std::vector<T>& data, bool is_end = false)
                : source_data(data), index(is_end ? data.size() : 0) {}
        
            /**
             * @brief Dereference operator to access current element.
             * 
             * @return const T& Reference to the current element
             * @throws std::runtime_error If attempting to dereference when out of range
             */
            const T& operator*() const {
                if (index >= source_data.size()) {
                    throw std::runtime_error("Cannot desourceerence OrderIterator: out of range");
                }
                return source_data[index];
            }
        
            /**
             * @brief Pre-increment operator to move to next element.
             * 
             * @return OrderIterator& Reference to this iterator after incrementing
             * @throws std::runtime_error If attempting to increment past the end
             */
            OrderIterator& operator++() {
                if (index >= source_data.size()) {
                    throw std::runtime_error("Cannot increment OrderIterator past the end.");
                }
                ++index;
                return *this;
            }
        
            /**
             * @brief Inequality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are not equal, false otherwise
             */
            bool operator!=(const OrderIterator& other) const {
                return index != other.index || &source_data != &other.source_data;
            }
        
            /**
             * @brief Equality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are equal, false otherwise
             */
            bool operator==(const OrderIterator& other) const {
                return !(*this != other);
            }
        };

        /**
         * @brief Creates an iterator pointing to the beginning of normal order traversal.
         * 
         * @return OrderIterator Iterator pointing to the first inserted element
         */
        OrderIterator begin_order() const {
            return OrderIterator(data);
        }
        
        /**
         * @brief Creates an iterator pointing to the end of normal order traversal.
         * 
         * @return OrderIterator Iterator representing the end position
         */
        OrderIterator end_order() const {
            return OrderIterator(data, true);
        }
        
    /**
     * @brief Iterator class for traversing elements starting from the middle and expanding outward.
     * 
     * This iterator starts at the middle element(s) and alternates between moving right and left,
     * expanding outward until all elements are visited. For even-sized containers, it starts
     * with the right-middle element, then the left-middle, then continues outward.
     */
    class MiddleOutIterator {
        private:
            const std::vector<T>& sourceData; ///< Reference to the original container data
            int left; ///< Left boundary index (can be negative when exhausted)
            size_t right; ///< Right boundary index
            bool rightSide; ///< Flag indicating which side to pick from next

        public:
            /**
             * @brief Constructor for begin() and end() iterators.
             * 
             * For begin(): initializes left and right to middle positions
             * For end(): sets boundary conditions to indicate completion
             * Special handling for single-element containers.
             * 
             * @param data The container's data vector to iterate over
             * @param is_end True if this is an end iterator, false for begin iterator
             */
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

            /**
             * @brief Dereference operator to access current element.
             * 
             * Returns the element from either the right or left side based on rightSide flag.
             * 
             * @return const T& Reference to the current element
             * @throws std::runtime_error If attempting to dereference when out of bounds
             */
            const T& operator*() const {
                
                
                if (left < 0 && right >= sourceData.size()) {
                    throw std::runtime_error("MiddleOutIterator: index out of bounds");
                }
                size_t index = rightSide ? right : static_cast<size_t>(left);
                return sourceData.at(index);
            }

            /**
             * @brief Pre-increment operator to move to next element.
             * 
             * Alternates between expanding right and left boundaries.
             * Special handling for single-element containers to properly terminate.
             * 
             * @return MiddleOutIterator& Reference to this iterator after incrementing
             * @throws std::runtime_error If attempting to increment past the end
             */
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

            /**
             * @brief Inequality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are not equal, false otherwise
             */
            bool operator!=(const MiddleOutIterator& other) const {
                return left != other.left || right != other.right || &sourceData != &other.sourceData;
            }

            /**
             * @brief Equality comparison operator.
             * 
             * @param other The other iterator to compare with
             * @return bool True if iterators are equal, false otherwise
             */
            bool operator==(const MiddleOutIterator& other) const {
                return !(*this != other);
            }

            
    };
    
    /**
     * @brief Creates an iterator pointing to the beginning of middle-out order traversal.
     * 
     * @return MiddleOutIterator Iterator starting from the middle element(s)
     */
    MiddleOutIterator begin_middle_out_order() const {
        return MiddleOutIterator(data);
    }
    
    /**
     * @brief Creates an iterator pointing to the end of middle-out order traversal.
     * 
     * @return MiddleOutIterator Iterator representing the end position
     */
    MiddleOutIterator end_middle_out_order() const {
        return MiddleOutIterator(data, true);
    }
       
};


}