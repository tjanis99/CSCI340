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
#ifndef NIU_CSCI_340_AVLTREE_H
#define NIU_CSCI_340_AVLTREE_H

#include "avltree.decl.h"

/**
 * @brief Check if the tree is an AVL tree.
 *
 * This function checks if the tree rooted at 'root' is an AVL tree.
 *
 * @param root A pointer to the root node of the tree.
 * @return True if the tree is an AVL tree, false otherwise.
 */

template <typename NODE>
bool is_avl(NODE *root) {
    if (root == nullptr) {
        return true;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }

    return is_avl(root->left) && is_avl(root->right);
}

/**
 * @brief Rotate the tree to the left.
 *
 * This function performs a left rotation on the tree rooted at 'pivot'.
 *
 * @param pivot A pointer to the root node of the tree to be rotated.
 */

template <typename NODEP>
void rotate_left(NODEP * &pivot)
{
        NODEP * curr = pivot;        
        pivot = pivot->right;           
        pivot->parent = curr->parent;
        curr->right = nullptr;       

        if (height(pivot->left) > height(pivot->right))
        {
                int hold = pivot->data;
                pivot->data = pivot->left->data;
                pivot->left->data = hold;

                pivot->right = pivot->left;
                pivot->left = nullptr;
        }

        if (pivot->left != nullptr)
        {
                NODEP * low = pivot->left;
                low->parent = curr;
                if (curr->data > low->data)
                        curr->left = low;
                else
                        curr->right = low;
        }

        curr->parent = pivot;
        pivot->left = curr;

        if (pivot->parent != nullptr)
        {
                if (pivot->data > pivot->parent->data)
                        pivot->parent->right = pivot;
                else
                        pivot->parent->left = pivot;
        }
}

/**
 * @brief Rotate the tree to the right.
 *
 * This function performs a right rotation on the tree rooted at 'pivot'.
 *
 * @param pivot A pointer to the root node of the tree to be rotated.
 */

template <typename NODEP>
void rotate_right(NODEP * &pivot)
{
        NODEP * curr = pivot;       
        pivot = pivot->left;            
        pivot->parent = curr->parent;
        curr->left = nullptr;        

        
        if (height(pivot->right) > height(pivot->left))
        {
                int hold = pivot->data;
                pivot->data = pivot->right->data;
                pivot->right->data = hold;

                pivot->left = pivot->right;
                pivot->right = nullptr;
        }

        if (pivot->right != nullptr)
        {
                NODEP * low = pivot->right;
                low->parent = curr;
                if (curr->data > low->data)
                        curr->left = low;
                else
                        curr->right = low;
        }


        curr->parent = pivot;
        pivot->right = curr;

   
        if (pivot->parent != nullptr)
        {
                if (pivot->data < pivot->parent->data)
                        pivot->parent->left = pivot;
                else
                        pivot->parent->right = pivot;
        }
}


/**
 * @brief Fix the AVL tree.
 *
 * This function fixes the AVL tree rooted at 'root' after an insert operation.
 *
 * @param root A pointer to the root node of the AVL tree.
 * @param node The node that was inserted.
 * @return The number of rotations performed to fix the tree.
 */

template <typename NODEP>
int fix_avl_tree(NODEP * & root, NODEP *node)
{
        int numProb = 0;
        int bal = 0;
        bool left;
        NODEP * problem;

        auto findProblem = [&problem, &bal, &left](NODEP * node)
        {
                bal = height(node->left) - height(node->right);

                if ((bal > 1) || (bal < -1))    
                        problem = node;
                if (bal < -1)       
                        left = true;
                if (bal > 1)        
                        left = false;
        };

        while (!is_avl(root))
        {
                preorder(root, findProblem);

                if (left)
                        rotate_left(problem);
                else
                        rotate_right(problem);

                if (problem->parent == nullptr)
                        root = problem;

                numProb++;
        }

        return numProb;
}

#endif /* NIU_CSCI_340_AVLTREE_H */