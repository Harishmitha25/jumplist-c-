# JumpList Data Structure - README

## Overview
The `JumpList` is a specialized linked list data structure. Each node stores a string and maintains pointers to the next node and, optionally, to a "jump" node further down the list. The structure ensures that strings are stored in alphabetical order, leveraging jump pointers for efficient search and traversal.

### Key Features
1. **Alphabetical Order**: Strings are always kept in alphabetical order.
2. **Jump Nodes**: Some nodes have a jump pointer that skips over multiple nodes, enabling faster traversal.
3. **Segments**: Nodes are divided into segments, with each jump node defining the start of a segment. The size of each segment is at most `MAX_GAP_SIZE` (5 by default).
4. **Head Node**: The head of the list is always a jump node.

### Node Structure
The `Node` class contains the following:
- `data_`: The string stored in the node.
- `next_`: Pointer to the next node.
- `jump_`: Pointer to the next jump node (nullptr for non-jump nodes).
- `gap_`: Number of nodes in the current segment (0 for non-jump nodes).
### Purpose
This JumpList implementation is part of an assignment for a university C++ module. It is designed to practice advanced data structures, memory management, and efficient algorithms.

### Motivation
The standard linked list data structure is simple, but it takes a long time to go through (or "traverse") all the nodes in procedures such as searching. Various methods can be used in order to speed this up. In this assignment, you will implement a modified linked list that has an additional "jump" pointer that "skips past" a larger number of nodes. This acts like a "fast lane" to allow going through the nodes more quickly. We call the data structure a "JumpList" here.

Note that your role here is the implementer of a software library that provides this JumpList data structure. You are NOT the end users of this library (the "clients"); they know nothing about what you are about to write, but just use the API of this data structure (described below) to store their strings.

This is a made-up data structure, and is not the same as other known data structures that may have similar names. (This is actually a "simplified" version of some known data structure.) Some of the requirements given, and the implementations needed, are different from such "similar" data structures, and are sub-optimal in terms of design or performance. Nevertheless you should just do as you are told, and not attempt to "imitate" any "better" solutions.

### JumpList Structure
The `JumpList` class maintains:
- `head_`: Pointer to the first node of the list.

Additional member variables can be introduced to enhance functionality.

---

## Class Functions

### Node Class
#### Constructor
```cpp
Node(string data, Node* next, Node* jump, int gap)
```
Initializes a `Node` with the given data, next pointer, jump pointer, and gap size.

### JumpList Class
#### Constructors
- **Default Constructor**
  ```cpp
  JumpList()
  ```
  Creates an empty `JumpList`.

- **Parameterized Constructor**
  ```cpp
  JumpList(int size, const string* arr)
  ```
  For testing purposes. Initializes a `JumpList` with nodes derived from the provided array or the example JumpList if `arr` is `nullptr`.

#### Destructor
- **Node Destructor**
  ```cpp
  ~Node()
  ```
  Releases memory used by a node.

- **JumpList Destructor**
  ```cpp
  ~JumpList()
  ```
  Releases all memory used by the `JumpList`.

### Supported Operations
1. **Size**
   ```cpp
   int size()
   ```
   Returns the number of elements in the list.

2. **Find**
   ```cpp
   bool find(const string& s)
   ```
   Searches for a string in the list using jump pointers for efficiency.

3. **Get**
   ```cpp
   string get(int i)
   ```
   Returns the string stored in the `i`-th node. If the index is out of bounds, returns an empty string.

4. **Print**
   ```cpp
   string print()
   ```
   Visualizes the contents of the `JumpList` with three lines:
   - All strings in the list.
   - All strings in the jump nodes.
   - Gap sizes of the jump nodes.

5. **Pretty Print** (Bonus)
   ```cpp
   string prettyPrint()
   ```
   Adds arrows to visualize pointers and aligns jump nodes and gaps.

6. **Insert**
   ```cpp
   bool insert(const string& s)
   ```
   Inserts a string into the correct position, maintaining alphabetical order. Splits a segment if it exceeds `MAX_GAP_SIZE`.

7. **Erase**
   ```cpp
   bool erase(const string& s)
   ```
   Removes a string from the list, merging and splitting segments as necessary.

---

## Examples

### Insert Operation
1. **Insert "dog" into the running example**:
   ```
   a --> b --> blah --> c --> cat --> d --> dog --> etc --> ooo... --> x --> zzz
   a -------------------------------> d -----------------------------> x
   5                                  4                                2
   ```

2. **Insert "A" into the running example**:
   ```
   A --> a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz
   A --------------> blah ----------------> d ---------------------> x
   3                 3                      3                        2
   ```

### Erase Operation
1. **Delete "blah" from the running example**:
   ```
   a --> b --> c --> cat --> d --> etc --> ooo... --> x --> zzz
   a ----------------------> d ---------------------> x
   4                         3                        2
   ```

2. **Delete "x" from the running example**:
   ```
   a --> b --> blah --> c --> cat --> d --> etc --> ooo... --> zzz
   a -------------------------------> d
   5                                  4
   ```

3. **Delete "d" from the running example**:
   ```
   a --> b --> blah --> c --> cat --> etc --> ooo... --> x --> zzz
   a -----------------------> cat ---------------------> x
   4                          3                          2
   ```

4. **Delete "a" from the running example**:
   ```
   b --> blah --> c --> cat --> d --> etc --> ooo... --> x --> zzz
   b -------------------------> d ---------------------> x
   4                            3                        2
   ```

5. **Delete all non-jump nodes from the running example**:
   ```
   a --> d --> x
   a --> d --> x
   1     1     1
   ```
   When "a" is deleted, it becomes:
   ```
   d --> x
   d --> x
   1     1
   ```

---

## Implementation Details

### Methods to Implement
- **Node Constructor**: Initializes a node with the given parameters.
- **Node Destructor**: Releases memory used by a node.
- **JumpList Default Constructor**: Initializes an empty JumpList.
- **JumpList Destructor**: Releases all memory used by the JumpList.
- **`size()`**: Computes the number of elements in the list.
- **`get(int i)`**: Retrieves the i-th node's data.
- **`print()`**: Returns a formatted string representation of the list.
- **`prettyPrint()`**: Returns a detailed visualization of the list.
- **`insert(const string& s)`**: Inserts a string while maintaining order and segment constraints.
- **`erase(const string& s)`**: Removes a string and adjusts the list's structure.

### Provided Methods
- **Parameterized Constructor**: Prepares a predefined list for testing.
- **`find(const string& s)`**: Searches for a string in the list efficiently.

---

## Notes
- Proper memory management is crucial, especially in `insert()` and `erase()`.
- Pay close attention to edge cases, such as deleting the head node or managing empty lists.
- The `print()` and `prettyPrint()` methods must follow exact formatting to pass test cases.
- Avoid copying JumpLists as they lack a copy constructor and assignment operator.

---
