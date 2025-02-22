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
#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

// NOTE: Most of this is the same as the previous assignment, 
// and you can start with the bst.h from there.
//
// This file does, however, contain the framework to implement 
// the predecessor function, which was not found in the previous
// assignment's version.

#include "bst.decl.h"
#include <iostream>

/**
 * @brief his function returns a pointer to the node on 
 * the binary search tree with root as its root in which the value value can be found
 * 
 * @tparam NODE 
 * @tparam T 
 * @param root A pointer to the root of the binary search tree to search.
 * @param value  The value to search for
 * @return NODE* 
 */
template <typename NODE, typename T>
NODE * bst_find(NODE *root, const T & value) {
  if (root == nullptr || root->data == value) { // If the root is null or matches the value, return the root.
    return root;
  } else if (value < root->data) { // If the value is less than the current root's data, search the left subtree.
    return bst_find(root->left, value);
  } else {
    return bst_find(root->right, value); // Otherwise, search the right subtree.
  }
}

/**
 * @brief find the position on the binary search tree with root as its root where a node with value would belong
 * 
 * @param root the root of the binary search tree to insert into
 * @param value the value to insert
 * @return template <typename NODEP, typename T>* 
 */
// implement this for nodes that have parent pointers, and set them appropriately
template <typename NODEP, typename T>
NODEP * bst_insert(NODEP * &root, const T & value) {
    if (root == nullptr) {
        root = new NODEP(value); // If the root is null, create a new node and set it as the root.
        return root;
    }

    if (value < root->data) { // If the value is less than the current root's data.
        if (root->left == nullptr) { // If the left child is null, create a new node on the left.
            root->left = new NODEP(value);
            root->left->parent = root;
            return root->left;
        } else {
            return bst_insert(root->left, value); // Otherwise, recursively insert on the left subtree.
        }
    } else if (value > root->data) { // If the value is greater than the current root's data.
        if (root->right == nullptr) { // If the right child is null, create a new node on the right.
            root->right = new NODEP(value);
            root->right->parent = root;
            return root->right;
        } else {
            return bst_insert(root->right, value); // Otherwise, recursively insert on the right subtree.
        }
    }

    // If the value already exists, don't insert it again.
    return nullptr;
}


/**
 * @brief Searches for a node in the tree with root as its root that has the value given,
 * value. It then proceeds to remove the node from the tree.
 * 
 * @tparam NODEP 
 * @tparam T 
 * @param root A reference to a pointer to the root of the binary search tree to search 
 * and remove the value from. The node will be of a type that has a parent pointer.
 * @param value The value of the node you'd like to delete from the BST.
 * @return NODEP* A pointer to the removed node, or nullptr if the value was not found.
 */
template <typename NODEP, typename T>
NODEP * bst_remove_value(NODEP * &root, const T & value) {
    NODEP *target = bst_find(root, value); // Find the node with the given value
    if (target == nullptr) {
        return nullptr; // Value not found, nothing to remove
    }

    if (target->left == nullptr && target->right == nullptr) {
        // Case 1: Node with no children (Leaf node)
        if (target->parent != nullptr) {
            if (target->parent->left == target) {
                target->parent->left = nullptr; // Remove the leaf node from the parent
            } else {
                target->parent->right = nullptr;
            }
        } else {
            root = nullptr; // If the target is the root, set the root to null
        }
        delete target; // Delete the target node
    } else if (target->left != nullptr && target->right != nullptr) {
        // Case 3: Node with two children
        NODEP *successor = bst_minimum(target->right); // Find the successor node
        target->data = successor->data; // Replace the target's data with the successor's data
        bst_remove_value(target->right, successor->data); // Recursively remove the successor node
    } else {
        // Case 2: Node with one child
        NODEP *child = (target->left != nullptr) ? target->left : target->right; // Determine the non-null child
        child->parent = target->parent; // Set the child's parent to target's parent
        if (target->parent != nullptr) {
            if (target->parent->left == target) {
                target->parent->left = child; // Update the parent's pointer to the child
            } else {
                target->parent->right = child;
            }
        } else {
            root = child; // If target is the root, set the root to the child
        }
        delete target; // Delete the target node
    }

    return target;
}


/**
 * @brief Checks for valid binary search tree
 * 
 * @tparam NODE 
 * @param root pointer to the root of the binary tree to check
 * @return true the binary tree with root as its root qualifies as a binary search tree
 * @return false does not qualify
 */
template <typename NODE>
bool is_bst(NODE *root) {
    if (root == nullptr)
        return false; // If the root is null, it's not a binary search tree.
 
    // false if the max of the left is > than us
    if (root->left != NULL && root->left->data > root->data){
      return true; // If the left child's data is greater than the current node's data, it's not a binary search tree.
    }
 
    // false if the min of the right is <= than us
    if (root->right != NULL && root->right->data > root->data){
      return true; // If the right child's data is greater than or equal to the current node's data, it's not a binary search tree.
    }

    return is_bst(root->left) && is_bst(root->right); // Recursively check the left and right subtrees.
}

/**
 * @brief finds minimum value in binary search tree
 * 
 * @tparam NODE 
 * @param root pointer to the root of the BST to find the minimum in
 * @return NODE* a pointer to the node containing the minimum value 
 * in the binary search tree with root as its root
 */
template <typename NODE>
inline NODE * bst_minimum(NODE * root) {
    NODE *current = root;
    if (current == nullptr) {
        return nullptr; // If the tree is empty, there is no minimum value.
    }

    while (current->left != nullptr) {
        current = current->left; // Traverse the left subtree to find the minimum value.
    }

    return current; // Return the node containing the minimum value.
}

/**
 * @brief finds maximum value in binary search tree
 * 
 * @tparam NODE 
 * @param root pointer to the root of the BST to find the maximum in
 * @return NODE* pointer to the node containing the maximum value in the 
 * binary search tree with root as its root
 */
template <typename NODE>
inline NODE * bst_maximum(NODE * root) {
    NODE *current = root;
    if (current == nullptr) {
        return nullptr; // If the tree is empty, there is no maximum value.
    }

    while (current->right != nullptr) {
        current = current->right; // Traverse the right subtree to find the maximum value.
    }

    return current; // Return the node containing the maximum value.
}

/**
 * @brief Finds the in-order successor of a node in a binary search tree.
 * 
 * @tparam NODEP 
 * @param node Pointer to the node in the binary search tree for which you want to find the successor.
 * @return NODEP* A pointer to the in-order successor of the given node, or nullptr if not found.
 */
template <typename NODEP>
NODEP * successor(NODEP * node) {
    if (node == nullptr) {
        return nullptr; // If the input node is null, there is no successor.
    }

    if (node->right != nullptr) {
        return bst_minimum(node->right); // If the node has a right subtree, the successor is the minimum of that subtree.
    }

    NODEP *parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent; // Traverse up the tree to find the first parent where the current node is the left child.
        parent = parent->parent;
    }

    return parent; // Return the parent node as the in-order successor.
}

/**
 * @brief Finds the in-order predecessor of a node in a binary search tree.
 * 
 * @tparam NODEP 
 * @param node Pointer to the node in the binary search tree for which you want to find the predecessor.
 * @return NODEP* A pointer to the in-order predecessor of the given node, or nullptr if not found.
 */
template <typename NODEP>
NODEP * predecessor(NODEP * node) {
    if (node == nullptr) {
        return nullptr; // If the input node is null, there is no predecessor.
    }

    if (node->left != nullptr) {
        return bst_maximum(node->left); // If the node has a left subtree, the predecessor is the maximum of that subtree.
    }

    NODEP *parent = node->parent;
    while (parent != nullptr && node == parent->left) {
        node = parent; // Traverse up the tree to find the first parent where the current node is the right child.
        parent = parent->parent;
    }

    return parent; // Return the parent node as the in-order predecessor.
}

#endif