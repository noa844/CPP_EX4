# Generic Container with Multiple Iterator Patterns

This project implements a generic template class `MyContainer` that provides various iteration patterns over stored elements in C++. The container wraps a `std::vector` and offers multiple ways to traverse elements including ascending, descending, side-cross, reverse, middle-out, and normal order iterations.

---

## Project Structure
```
CPP_EX4/
├── include/
│   └── MyContainer.hpp           # Template container class implementation
├── test/
│   └── test.cpp                  # Unit tests for all iterator patterns
├── demo.cpp                      # Demo of container functionality
├── Makefile                      # Build and run instructions
└── README.md
```

---

## How to Run the Project

1. **Build the project**
```bash
make
```

2. **Run the demo**
```bash
make main
```

3. **Run unit tests**
```bash
make test
```

4. **Check for memory leaks with Valgrind**
```bash
make valgrind
```

5. **Clean build files**
```bash
make clean
```

---

## Container Class Design (`MyContainer<T>`)

* **Generic Template**: Works with any type `T` (defaults to `int`)
* **Internal Storage**: Uses `std::vector<T>` for efficient element management
* **Non-destructive Iterations**: All sorting operations are performed on copies to preserve original insertion order
* **Multiple Iterator Patterns**: Six different ways to traverse the same data

### Core Operations:
- `add(const T& value)` - Adds an element to the container
- `remove(const T& value)` - Removes all occurrences of a value (throws if not found)
- `size()` - Returns the number of elements
- `operator<<` - Stream insertion for easy printing

---

## Iterator Patterns

### 1. **Ascending Order Iterator**
Traverses elements in sorted ascending order (smallest to largest).


### 2. **Descending Order Iterator**
Traverses elements in sorted descending order (largest to smallest).


### 3. **Side-Cross Iterator**
Alternates between smallest and largest remaining elements.
Pattern: smallest, largest, second smallest, second largest, etc.


### 4. **Reverse Order Iterator**
Traverses elements in reverse insertion order (last inserted first).


### 5. **Normal Order Iterator**
Traverses elements in original insertion order (first inserted first).


### 6. **Middle-Out Iterator**
Starts from middle element(s) and expands outward alternately.
For even-sized containers, starts with right-middle, then left-middle.


---

## Iterator Design Principles

### **Memory Efficiency**
- Sorted iterators (Ascending, Descending, Side-Cross) create temporary sorted copies
- Order-based iterators (Normal, Reverse, Middle-Out) reference original data directly
- All iterators implement proper bounds checking with exception handling

### **Exception Safety**
- All dereferencing operations check bounds and throw `std::runtime_error` if out of range
- Increment operations validate state before advancing
- Consistent error messages for debugging

### **Iterator Compliance**
- All iterators implement required operators: `*`, `++`, `!=`, `==`
- Support for range-based for loops
- Proper const-correctness throughout

---


## Technical Implementation Details

### **Template Specialization**
The container works with any comparable type `T`. The sorting operations require `T` to support:
- Copy constructor
- Assignment operator  
- Comparison operators (`<`, `>`, `==`)

### **Memory Management**
- Uses RAII principles through `std::vector`
- No manual memory management required
- Automatic cleanup of temporary sorted copies

### **Thread Safety**
- Read operations are thread-safe (const methods)
- Write operations (`add`, `remove`) are not thread-safe
- Consider external synchronization for concurrent access

---

## Author

| Name | Email |
|------|-------|
| [Noa Honigstein] | [noa.honigstein@gmail.com] |