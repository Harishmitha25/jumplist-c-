# JumpList Data Structure

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

2. **Delete "d" from the running example**:
   ```
   a --> b --> blah --> c --> cat --> etc --> ooo... --> x --> zzz
   a -----------------------> cat ---------------------> x
   4                          3                          2
   ```

---

## Notes
- The `print()` and `prettyPrint()` functions require precise whitespace formatting to pass tests.
- Proper memory management is critical, especially in `insert()` and `erase()` operations.
- The `JumpList` does not support copying; avoid using copy constructors or assignment operators.

---

## Testing
Use the `JumpList(int size, const string* arr)` constructor to create predefined lists for testing. Verify all operations using both the `print()` and `prettyPrint()` functions to ensure correctness.

---

## Constraints and Assumptions
- The `MAX_GAP_SIZE` is 5 by default but can be adjusted.
- Operations assume valid input and require efficient use of jump pointers for optimal performance.
- Handles edge cases like empty lists, head node changes, and merging/splitting segments.

---
