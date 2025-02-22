#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>
#include <queue>

// This file is the version distributed to students for implementation.

/**
 * @brief Returns the index of the left child of a heap node.
 * 
 * @param node Index of the current node
 * @return constexpr size_t Index of the left child
 */
inline constexpr size_t heap_left(size_t node) {
    return 2 * node + 1;
}

/**
 * @brief Returns the index of the right child of a heap node.
 * 
 * @param node Index of the current node
 * @return constexpr size_t Index of the right child
 */
inline constexpr size_t heap_right(size_t node) {
    return 2 * node + 2;
}

/**
 * @brief Returns the index of the parent of a heap node.
 * 
 * @param node Index of the current node
 * @return constexpr size_t Index of the parent
 */
inline constexpr size_t heap_parent(size_t node) {
    while (!node) {
        return node / 2;
    }
    return (node - 1) / 2;
}

/**
 * @brief Performs a preorder traversal on a heap.
 * 
 * @tparam ArrayLike Type of the heap container
 * @tparam FN Function to apply to each element during traversal
 * @param heapdata Heap container
 * @param heapnodes Number of nodes in the heap
 * @param node Current node index
 * @param fn Function to apply to each element
 */
template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    // Recursive preorder traversal on the heap
    if (node < heapnodes) {
        fn(heapdata[node]);
        heap_preorder(heapdata, heapnodes, heap_left(node), fn);
        heap_preorder(heapdata, heapnodes, heap_right(node), fn);
    }
}

/**
 * @brief Performs an inorder traversal on a heap.
 * 
 * @tparam ArrayLike Type of the heap container
 * @tparam FN Function to apply to each element during traversal
 * @param heapdata Heap container
 * @param heapnodes Number of nodes in the heap
 * @param node Current node index
 * @param fn Function to apply to each element
 */
template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    // Recursive inorder traversal on the heap
    if (node < heapnodes) {
        heap_inorder(heapdata, heapnodes, heap_left(node), fn);
        fn(heapdata[node]);
        heap_inorder(heapdata, heapnodes, heap_right(node), fn);
    }
}

/**
 * @brief Performs a postorder traversal on a heap.
 * 
 * @tparam ArrayLike Type of the heap container
 * @tparam FN Function to apply to each element during traversal
 * @param heapdata Heap container
 * @param heapnodes Number of nodes in the heap
 * @param node Current node index
 * @param fn Function to apply to each element
 */
template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    // Recursive postorder traversal on the heap
    if (node < heapnodes) {
        heap_postorder(heapdata, heapnodes, heap_left(node), fn);
        heap_postorder(heapdata, heapnodes, heap_right(node), fn);
        fn(heapdata[node]);
    }
}

/**
 * @brief Performs a level-order traversal on a heap.
 * 
 * @tparam ArrayLike Type of the heap container
 * @tparam FN Function to apply to each element during traversal
 * @param heapdata Heap container
 * @param heapnodes Number of nodes in the heap
 * @param fn Function to apply to each element
 */
template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike &heapdata, size_t heapnodes, FN fn) {
    // Level-order traversal on the heap using a queue
    if (heapnodes == 0) {
        return;
    }

    std::queue<size_t> q; // create queue
    q.push(0); // push root index

    while (!q.empty()) {
        size_t currentIdx = q.front();
        q.pop(); // set currentIdx & pop until found

        fn(heapdata[currentIdx]); // call fn

        size_t leftChild = heap_left(currentIdx);
        size_t rightChild = heap_right(currentIdx);

        if (leftChild < heapnodes) { // level order traversal
            q.push(leftChild);
        }
        if (rightChild < heapnodes) {
            q.push(rightChild);
        }
    }
}

/**
 * @brief Checks if a given array or container is a heap.
 * 
 * @tparam ArrayLike Type of the heap container
 * @tparam COMPARISON Comparison function to determine heap property
 * @param heapdata Heap container
 * @param nodes Number of nodes in the heap
 * @param compare Comparison function
 * @return true if the container is a heap, false otherwise
 */
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike &heapdata, size_t nodes, COMPARISON compare) {
    // Check if the container satisfies the heap property
    for (size_t i = 0; i < nodes; ++i) {
        size_t left_child = heap_left(i);
        size_t right_child = heap_right(i);

        if (left_child < nodes && compare(heapdata[left_child], heapdata[i]))
            return false;

        if (right_child < nodes && compare(heapdata[right_child], heapdata[i]))
            return false;
    }

    return true;
}

/**
 * @brief Performs the heap bubble-up operation.
 * 
 * @tparam RAIterator Random-access iterator type
 * @tparam COMPARE Comparison function to determine heap property
 * @param begin Iterator pointing to the beginning of the range
 * @param nodes Number of nodes in the heap
 * @param start Index of the node to start bubbling up from
 * @param compare Comparison function
 * @return size_t Number of swaps made during bubble-up
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    // Perform the heap bubble-up operation to maintain the heap property
    size_t swaps = 0;
    size_t current = start;
    while (current > 0) {
        size_t parent = heap_parent(current);
        if (!compare(*(begin + parent), *(begin + current))) {
            std::swap(*(begin + parent), *(begin + current));
            current = parent;
            swaps++;
        } else {
            break;
        }
    }
    return swaps;
}

/**
 * @brief Performs the heap bubble-down operation.
 * 
 * @tparam RAIterator Random-access iterator type
 * @tparam COMPARE Comparison function to determine heap property
 * @param begin Iterator pointing to the beginning of the range
 * @param nodes Number of nodes in the heap
 * @param start Index of the node to start bubbling down from
 * @param compare Comparison function
 * @return size_t Number of swaps made during bubble-down
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    // Perform the heap bubble-down operation to maintain the heap property
    size_t swaps = 0;
    size_t current = start;
    size_t left_child = heap_left(current);
    size_t right_child = heap_right(current);
    size_t smallest = current;

    if (left_child < nodes && compare(begin[left_child], begin[current])){
        smallest = left_child;
    }

    if (right_child < nodes && compare(begin[right_child], begin[smallest])){
        smallest = right_child;
    }

    if (smallest != current) {
        std::swap(begin[current], begin[smallest]);
        heap_bubble_down(begin, nodes, smallest, compare);
    }
    return swaps;
}

/**
 * @brief Inserts a new element into the heap and maintains the heap property.
 * 
 * @tparam T Type of elements in the heap
 * @tparam CONTAINER Type of the heap container
 * @tparam COMPARISON Comparison function to determine heap property
 * @param heapdata Heap container
 * @param nodes Number of nodes in the heap
 * @param key New element to be inserted
 * @param compare Comparison function
 */
template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER &heapdata, size_t &nodes, T key, COMPARISON compare) {
    // Insert the new element at the end
    heapdata.push_back(key);
    ++nodes;

    // Bubble up to maintain the heap property
    heap_bubble_up(heapdata.begin(), nodes, nodes - 1, compare);

    // If the container needs resizing, perform resizing
    if (nodes >= heapdata.size()) {
        heapdata.resize(nodes + 1);
    }
}

/**
 * @brief Extracts the root element from the heap and maintains the heap property.
 * 
 * @tparam CONTAINER Type of the heap container
 * @tparam COMPARISON Comparison function to determine heap property
 * @param heapdata Heap container
 * @param nodes Number of nodes in the heap
 * @param compare Comparison function
 * @return auto Extracted root element
 */
template <typename CONTAINER, typename COMPARISON>
auto heap_extract(CONTAINER &heapdata, size_t &nodes, COMPARISON compare) {
    // Check if the heap is empty
    if (nodes == 0) {
        throw std::out_of_range("Heap is empty");
    }

    // Save the root value to be returned later
    auto extracted = heapdata[0];

    // Move the last element to the root
    heapdata[0] = heapdata[nodes - 1];
    --nodes;

    // Perform heapify down to maintain the heap property
    heap_bubble_down(heapdata.begin(), nodes, 0, compare);

    return extracted;
}

/**
 * @brief Performs in-place heapify-up on a range of elements.
 * 
 * @tparam RAIterator Random-access iterator type
 * @tparam COMPARE Comparison function to determine heap property
 * @param begin Iterator pointing to the beginning of the range
 * @param end Iterator pointing to one past the end of the range
 * @param compare Comparison function
 * @return size_t Number of swaps made during heapify-up
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
    // Perform in-place heapify-up on the given range
    size_t swaps = 0;
    size_t nodes = std::distance(begin, end);

    for (size_t i = nodes - 1; i > 0; --i) {
        size_t current = i;
        size_t parent = heap_parent(current);

        while (current > 0 && compare(*(begin + current), *(begin + parent))) {
            std::iter_swap(begin + current, begin + parent);
            current = parent;
            parent = heap_parent(current);
            ++swaps;
        }
    }

    return swaps;
}

/**
 * @brief Performs in-place heapify-down on a range of elements.
 * 
 * @tparam RAIterator Random-access iterator type
 * @tparam COMPARE Comparison function to determine heap property
 * @param begin Iterator pointing to the beginning of the range
 * @param end Iterator pointing to one past the end of the range
 * @param compare Comparison function
 * @return size_t Number of swaps made during heapify-down
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
    // Perform in-place heapify-down on the given range
    size_t swaps = 0;
    size_t nodes = std::distance(begin, end);

    for (size_t i = nodes / 2; i > 0; --i) {
        size_t current = i;
        size_t left_child = heap_left(current);
        size_t right_child = heap_right(current);
        size_t smallest = current;

        if (left_child < nodes && compare(*(begin + left_child), *(begin + smallest)))
            smallest = left_child;

        if (right_child < nodes && compare(*(begin + right_child), *(begin + smallest)))
            smallest = right_child;

        while (smallest != current) {
            std::iter_swap(begin + current, begin + smallest);
            current = smallest;
            left_child = heap_left(current);
            right_child = heap_right(current);

            if (left_child < nodes && compare(*(begin + left_child), *(begin + current)))
                smallest = left_child;

            if (right_child < nodes && compare(*(begin + right_child), *(begin + smallest)))
                smallest = right_child;

            ++swaps;
        }
    }

    return swaps;
}

/**
 * @brief Sorts a range of elements using the heap sort algorithm.
 * 
 * @tparam RAIterator Random-access iterator type
 * @tparam COMPARE Comparison function to determine heap property
 * @param begin Iterator pointing to the beginning of the range
 * @param end Iterator pointing to one past the end of the range
 * @param compare Comparison function
 */
template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {
    // Perform heap sort on the given range
    size_t nodes = heapify_in_place_up(begin, end, compare);
    for (size_t i = nodes - 1; i > 0; --i) {
        std::swap(begin[0], begin[i]);
        heap_bubble_down(begin, i, 0, compare);
    }
}

#endif /* NIU_CSCI340_HEAP_H */
