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
#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"

#include <vector>
#include <queue>
#include <string>

/**
 * @brief Function for preorder traversal of the binary tree.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root 
 * @param fn 
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
  if (root)
  {
    fn(root); // Visit the current node
    preorder(root->left, fn); // Recursively traverse the left subtree
    preorder(root->right, fn); // Recursively traverse the right subtree
  }
}

/**
 * @brief // Function for inorder traversal of the binary tree.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root 
 * @param fn 
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
  if(root)
  {
    inorder(root->left, fn); // Recursively traverse the left subtree
    fn(root); // Visit the current node
    inorder(root->right, fn); // Recursively traverse the right subtree
  }  
}

/**
 * @brief Function for postorder traversal of the binary tree.

 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root 
 * @param fn 
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
  if (root)
  {
    postorder(root->left, fn); // Recursively traverse the left subtree
    postorder(root->right, fn); // Recursively traverse the right subtree
    fn(root); // Visit the current node
  }
}

/**
 * @brief Function for level-order traversal of the binary tree.

 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root 
 * @param fn 
 */
template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
    std::queue<BINTREENODE*> q;
    BINTREENODE *p = root;

    if (p != nullptr)
    {
      q.push(p);
      while (!q.empty())
      {
        p = q.front();
        q.pop();
        fn(p); // Visit the current node
        if (p->left != nullptr)
        {
          q.push(p->left); // Enqueue left child
        }
        if (p->right != nullptr)
        {
          q.push(p->right); // Enqueue right child
        }
      }
    }
}

/**
 * @brief Function to return all direct children of the given node.
 * 
 * @tparam BINTREENODE 
 * @param node 
 * @return std::vector <BINTREENODE *> 
 */
template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {
  std::vector<BINTREENODE*> children;
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
        return children;
    }

    if (node->left != nullptr) {
        children.push_back(node->left);
        BINTREENODE* sibling = node->left->right;
        while (sibling != nullptr) {
            children.push_back(sibling);
            sibling = sibling->right;
        }
    }
    return children;
}

/**
 * @brief Function to find the parent node of a given node in a tilted binary tree.

 * 
 * @tparam BINTREENODE 
 * @param node 
 * @return BINTREENODE* 
 */
template <typename BINTREENODE>
BINTREENODE* tilted_find_parent(BINTREENODE *node) {
    if (node && node->parent) {
        while (node->parent->right == node) {
            node = node->parent;
        }
        if (node->parent->left == node) {
            return node->parent;
        }
    }
    return nullptr;
}

/**
 * @brief Function for level-order traversal of a binary tree with a tilted structure.
 * 
 * @tparam BINTREENODE 
 * @tparam FN 
 * @param root 
 * @param fn 
 */
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {
  if (!root)
  {
    return;
  }

  std::queue<BINTREENODE*> q;
  q.push(root);

  while (!q.empty())
  {
    BINTREENODE* current = q.front();
    q.pop();
    fn(current); // Visit the current node
    BINTREENODE* child = current->left;
    while (child)
    {
      q.push(child);
      child = child->right;
    }
  }
}

/**
 * @brief Function to delete a binary tree, freeing the memory.

 * 
 * @tparam BINTREENODE 
 * @param node 
 */
template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    if (node == nullptr) {
        return; // Nothing to do for an empty tree or subtree
    }

    // Delete left and right subtrees (post-order traversal)
    delete_tree(node->left);
    delete_tree(node->right);

    // Delete the current node
    delete node;
}

#endif
