//***************************************************************************
//
//  Trevor Janis
//  Z1839641
//  CSCI 340-1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************
#ifndef NIU_CSCI340_AVL_SET_H
#define NIU_CSCI340_AVL_SET_H

#include "avl_set.decl.h"
#include "avltree.h"
#include "bintree.h"
/**
 * @brief Iterator class for AVL set.
 *
 * Provides functionalities for traversing an AVL set.
 */
template <typename T>
avl_iterator<T>::avl_iterator(const avl_iterator<T> &source)
    : pos(source.pos), prev(source.prev), next(source.next) {
    // Copy constructor
};

/**
 * @brief Prefix increment operator for avl_iterator.
 *
 * @return Reference to the incremented avl_iterator.
 */
template <typename T>
avl_iterator<T> &avl_iterator<T>::operator++() {
    // Prefix increment - go forward one
    if (pos) {
        if (pos->right) {
            pos = pos->right;
            while (pos->left)
                pos = pos->left;
        } else {
            prev = pos;
            pos = pos->parent;
            while (pos && prev == pos->right) {
                prev = pos;
                pos = pos->parent;
            }
        }
    }

    return *this;
}
/**
 * @brief Postfix increment operator for avl_iterator.
 *
 * @return A copy of the avl_iterator before incrementing.
 */
template <typename T>
avl_iterator<T> avl_iterator<T>::operator++(int) {
    // Postfix increment - go forward one
    avl_iterator<T> temp(*this);
    ++(*this);
    return temp;
}
/**
 * @brief Prefix decrement operator for avl_iterator.
 *
 * @return Reference to the decremented avl_iterator.
 */
template <typename T>
avl_iterator<T> &avl_iterator<T>::operator--() {
    // Prefix decrement - go back one
    if (pos) {
        if (pos->left) {
            pos = pos->left;
            while (pos->right)
                pos = pos->right;
        } else {
            next = pos;
            pos = pos->parent;
            while (pos && next == pos->left) {
                next = pos;
                pos = pos->parent;
            }
        }
    } else {
        // If we are already at the end, move to the last element
        pos = prev;
    }

    return *this;
}
/**
 * @brief Postfix decrement operator for avl_iterator.
 *
 * @return A copy of the avl_iterator before decrementing.
 */
template <typename T>
avl_iterator<T> avl_iterator<T>::operator--(int) {
    // Postfix decrement - go back one
    avl_iterator<T> temp(*this);
    --(*this);
    return temp;
}
/**
 * @brief Dereference operator for avl_iterator.
 *
 * @return Reference to the data stored in the avl_iterator's current position.
 */
template <typename T>
T &avl_iterator<T>::operator*() {
    // Dereference
    if (pos) {
        return pos->data;
    }

    // Return a default value if pos is null
    static T x = T();
    return x;
}
/**
 * @brief Equality comparison operator for avl_iterator.
 *
 * @param other Another avl_iterator to compare with.
 * @return True if the two iterators are equal, false otherwise.
 */
template <typename T>
bool avl_iterator<T>::operator==(const avl_iterator<T> &other) const {
    // Equality check
    return true;
}

 /**
     * @brief Constructor for avl_set.
     *
     * Initializes the set with values from the provided range.
     *
     * @tparam InputIterator Type of iterator for the input range.
     * @param start Iterator pointing to the beginning of the range.
     * @param end Iterator pointing to the end of the range.
     */
template <typename T>
template <typename InputIterator>
avl_set<T>::avl_set(InputIterator start, InputIterator end) {
    for (InputIterator it = start; it != end; ++it) {
        insert(*it);
    }
}

// Destructor
template <typename T>
avl_set<T>::~avl_set() {
    clear();
}

  /**
     * @brief Get iterator pointing to the beginning of the avl_set.
     *
     * @return Iterator pointing to the first element.
     */
template <typename T>
avl_iterator<T> avl_set<T>::begin() {
    if (root == nullptr) {
        return avl_iterator<T>(nullptr); // If the tree is empty, return end()
    }

    NODE *current = root;
    while (current->left) {
        current = current->left;
    }

    return avl_iterator<T>(current);
}

  /**
     * @brief Get iterator pointing one past the end of the avl_set.
     *
     * @return Iterator pointing one past the last element.
     */
template <typename T>
avl_iterator<T> avl_set<T>::end() {
    return avl_iterator<T>(nullptr);
}
    /**
     * @brief Get reverse iterator pointing to the beginning of the avl_set.
     *
     * @return Reverse iterator pointing to the last element.
     */
template<typename T>
std::reverse_iterator<avl_iterator<T>> avl_set<T>::rbegin() {
    return std::reverse_iterator<avl_iterator<T>>(end());
}

/**
     * @brief Get reverse iterator pointing one past the end of the avl_set.
     *
     * @return Reverse iterator pointing one past the first element.
     */
template<typename T>
std::reverse_iterator<avl_iterator<T>> avl_set<T>::rend() {
    return std::reverse_iterator<avl_iterator<T>>(begin());
}

/**
     * @brief Inorder traversal of the avl_set.
     *
     * Applies a given function to each element during traversal.
     *
     * @tparam FN Type of the function to apply.
     * @param fn The function to apply to each element.
     */
template <typename T>
template <typename FN>
void avl_set<T>::inorder(FN fn) const {
    ::inorder(root, fn);
}

/**
     * @brief Preorder traversal of the avl_set.
     *
     * Applies a given function to each element during traversal.
     *
     * @tparam FN Type of the function to apply.
     * @param fn The function to apply to each element.
     */
template <typename T>
template <typename FN>
void avl_set<T>::preorder(FN fn) const {
    ::preorder(root, fn);
}

 /**
     * @brief Postorder traversal of the avl_set.
     *
     * Applies a given function to each element during traversal.
     *
     * @tparam FN Type of the function to apply.
     * @param fn The function to apply to each element.
     */
template <typename T>
template <typename FN>
void avl_set<T>::postorder(FN fn) const {
    ::postorder(root, fn);
}

 /**
     * @brief Levelorder traversal of the avl_set.
     *
     * Applies a given function to each element during traversal.
     *
     * @tparam FN Type of the function to apply.
     * @param fn The function to apply to each element.
     */
template <typename T>
template <typename FN>
void avl_set<T>::levelorder(FN fn) const {

	::levelorder(root,fn);

}
////////////////////////////////////////////////////////////////
//Utility


template <typename T>
void avl_set<T>::clear() {
    ::delete_tree(root);
}

/**
 * @brief Insert a value into the AVL set.
 *
 * This function inserts a value into the AVL set using the bst_insert function.
 *
 * @tparam T The type of elements in the set.
 * @param value The value to be inserted.
 * @return A pair containing an iterator (set to nullptr) and a boolean (set to false).
 */
template <typename T>
std::pair<avl_iterator<T>, bool> avl_set<T>::insert(const value_type& value) {
		bst_insert(root,value);
		return std::make_pair(nullptr, false);

}

/**
 * @brief Erase a key from the AVL set.
 *
 * This function is not currently implemented and always returns 0.
 *
 * @tparam T The type of elements in the set.
 * @param key The key to be erased.
 * @return Always returns 0.
 */
template <typename T>
typename avl_set<T>::size_type avl_set<T>::erase(const key_type& key) {
    return 0;
}

/**
 * @brief Count occurrences of a key in the AVL set.
 *
 * This function checks if the key is present in the AVL set using bst_find.
 *
 * @tparam T The type of elements in the set.
 * @param key The key to be counted.
 * @return 1 if the key is found, 0 otherwise.
 */
template <typename T>
typename avl_set<T>::size_type avl_set<T>::count(const key_type& key) {
    return (bst_find(root, key) != nullptr) ? 1 : 0;
}

/**
 * @brief Get the height of the AVL set.
 *
 * This function calls the height function to get the height of the AVL set.
 *
 * @tparam T The type of elements in the set.
 * @return The height of the AVL set.
 */
template <typename T>
int avl_set<T>::height() const {
	return ::height(root);
}

/**
 * @brief Check if the AVL set is a binary search tree.
 *
 * This function calls the is_bst function to check if the AVL set is a binary search tree.
 *
 * @tparam T The type of elements in the set.
 * @return True if the AVL set is a binary search tree, false otherwise.
 */
template <typename T>
bool avl_set<T>::is_bst() const {
	return ::is_bst(root);
}

/**
 * @brief Check if the AVL set is an AVL tree.
 *
 * This function calls the is_avl function to check if the AVL set is an AVL tree.
 *
 * @tparam T The type of elements in the set.
 * @return True if the AVL set is an AVL tree, false otherwise.
 */
template <typename T>
bool avl_set<T>::is_avl() const {
	return ::is_avl(root);
}

/**
 * @brief Get the size of the AVL set.
 *
 * This function returns the number of nodes in the AVL set.
 *
 * @tparam T The type of elements in the set.
 * @return The size of the AVL set.
 */
template <typename T>
typename avl_set<T>::size_type avl_set<T>::size() const {
    return node_count;
}

#endif