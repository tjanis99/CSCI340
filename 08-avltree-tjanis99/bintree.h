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
#ifndef LEHUTA_BINTREE_H_IMPL
#define LEHUTA_BINTREE_H_IMPL

#include "bintree.decl.h"
#include <queue>
// height of tree, defined as the number of edges in the longest path
// from the root to a leaf. If you're off the tree, this should return -1.
/**
 * @brief Calculates the height of the tree.
 * 
 * @tparam NODE 
 * @param node The root node of the tree.
 * @return int The height of the tree.
 */
template <typename NODE>
int height(NODE * node) {
    if (node == nullptr) {
        return -1; // If the node is null, the tree has a height of -1.
    }

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return 1 + std::max(leftHeight, rightHeight); // Return the maximum height of the left and right subtrees plus 1.
}

/**
 * @brief Counts the number of nodes in the tree.
 * 
 * @tparam NODE 
 * @param root The root node of the tree.
 * @return int The number of nodes in the tree.
 */
template <typename NODE>
int count(NODE * root) {
    if (root == nullptr) {
        return 0; // If the root is null, the tree has zero nodes.
    }

    return 1 + count(root->left) + count(root->right); // Return the count of nodes in the left and right subtrees plus 1.
}

/**
 * @brief Performs a preorder traversal of the tree and applies a function to each node.
 * 
 * @tparam NODE 
 * @tparam FN 
 * @param root The root node of the tree.
 * @param fn The function to apply to each node.
 */
template <typename NODE, typename FN>
void preorder(NODE *root, FN fn) {
    if (root == nullptr) {
        return; //check root
    }

    fn(root);   //preorder traversal
    preorder(root->left, fn);
    preorder(root->right, fn);
}

/**
 * @brief Performs an inorder traversal of the tree and applies a function to each node.
 * 
 * @tparam NODE 
 * @tparam FN 
 * @param root The root node of the tree.
 * @param fn The function to apply to each node.
 */
template <typename NODE, typename FN>
void inorder(NODE *root, FN fn) {
    if (root == nullptr) {
        return; //check root
    }

    inorder(root->left, fn); //inorder traveral
    fn(root);
    inorder(root->right, fn);
}

/**
 * @brief Performs a postorder traversal of the tree and applies a function to each node.
 * 
 * @tparam NODE 
 * @tparam FN 
 * @param root The root node of the tree.
 * @param fn The function to apply to each node.
 */
template <typename NODE, typename FN>
void postorder(NODE *root, FN fn) {
    if (root == nullptr) {
        return;
    }
    //post order traversal
    postorder(root->left, fn);
    postorder(root->right, fn);
    fn(root);
}

/**
 * @brief Performs a level-order traversal of the tree and applies a function to each node.
 * 
 * @tparam NODE 
 * @tparam FN 
 * @param root The root node of the tree.
 * @param fn The function to apply to each node.
 */
template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn) {
    if (root == nullptr) {
        return;
    }

    std::queue<NODE*> q; //create queue
    q.push(root); //push root

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop(); //set current & pop until found

        fn(current); //call fn

        if (current->left) { //level order traveral
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
}

/**
 * @brief Deletes the entire tree and sets the root node to null.
 * 
 * @tparam BINTREENODE 
 * @param node A reference to the root node of the tree to delete.
 */
template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    if (node == nullptr) {
        return;
    }

    delete_tree(node->left); //delete children
    delete_tree(node->right);

    delete node; //delete pointer
    node = nullptr; // Delete each node in the tree and set the root node to null.
}

#endif