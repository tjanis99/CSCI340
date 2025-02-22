#ifndef NIU_CSCI340_HEAP_PRIORITY_QUEUE_H
#define NIU_CSCI340_HEAP_PRIORITY_QUEUE_H

#include "heap_priority_queue.decl.h"

/**
 * @brief Construct a new heap priority queue<T, CONTAINER, COMPARE>::heap priority queue object
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @tparam ITERATOR Iterator type for initializing the priority queue with a range of elements
 * @param begin Iterator pointing to the beginning of the range
 * @param end Iterator pointing to one past the end of the range
 */
template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T, CONTAINER, COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end)
    : data(begin, end), nodes(data.size()), compare() {
    // Initialize the priority queue with elements from the given range
    // and perform in-place heapify-down to ensure the heap property is satisfied
    heapify_in_place_down(data.begin(), data.end(), compare);
}

/**
 * @brief Access the top element of the priority queue.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @return T& Reference to the top element
 */
template <class T, class CONTAINER, class COMPARE>
T& heap_priority_queue<T, CONTAINER, COMPARE>::top() {
    // Check if the priority queue is empty before accessing the top element
    if (empty()) {
        throw std::out_of_range("Priority queue is empty");
    }
    return data[0];
}

/**
 * @brief Check if the priority queue is empty.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @return true if the priority queue is empty, false otherwise
 */
template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T, CONTAINER, COMPARE>::empty() const {
    return nodes == 0;
}

/**
 * @brief Get the size of the priority queue.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @return size_t Number of elements in the priority queue
 */
template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T, CONTAINER, COMPARE>::size() const {
    return nodes;
}

/**
 * @brief Push an element onto the priority queue.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @param x Element to be pushed onto the priority queue
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::push(const T& x) {
    // Insert the new element at the end and perform in-place heapify-up
    data.push_back(x);
    ++nodes;
    heapify_in_place_up(data.begin(), data.end(), compare);
}

/**
 * @brief Pop the top element from the priority queue.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::pop() {
    // Check if the priority queue is empty before popping
    if (empty()) {
        throw std::out_of_range("Priority queue is empty");
    }

    // Swap the root with the last element, pop the last element, and perform in-place heapify-down
    std::swap(data[0], data.back());
    data.pop_back();
    --nodes;

    heapify_in_place_down(data.begin(), data.end(), compare);
}

/**
 * @brief Dump the data of the priority queue to an ostream.
 * 
 * @tparam T Type of elements in the priority queue
 * @tparam CONTAINER Type of the container used to store elements
 * @tparam COMPARE Comparison function to determine the order of elements
 * @param ost Output stream to which the data is dumped
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T, CONTAINER, COMPARE>::dump_data(std::ostream& ost) const {
    // Output the elements of the priority queue
    ost << "[ ";
    for (size_t i = 0; i < nodes; ++i) {
        ost << data[i] << " ";
    }
    ost << "]";
}

#endif /* NIU_CSCI340_HEAP_PRIORITY_QUEUE_H */
