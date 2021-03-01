/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

/**
 * Private helper function for mirror.
 * @param root
 */
template <typename T>
void BinaryTree<T>::mirror(Node* root)
{
    if (root == NULL) {
        return;
    }
    Node* left_tmp = root->left;
    Node* right_tmp = root->right;
    root->right = left_tmp;
    root->left = right_tmp;
    mirror(root->left);
    mirror(root->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    return isOrderedIterative(root);
}
/** isOrdered iterative helper
 * @param root
 * @return True if an in-order traversal of the tree would produce a nondecreasing list output values, and false otherwise.
 */ 
template <typename T>
bool BinaryTree<T>::isOrderedIterative(Node* root) const {
    InorderTraversal<T> iot(root);
    std::vector<int> elements;
    for (typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        elements.push_back((*it)->elem);
    }
    for (unsigned i = 0; i < elements.size() - 1; i++) {
        if (elements[i] > elements[i+1]) {
            return false;
        }
    }
    
   
    return true;

}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* root) const
{
    // your code here
    bool right_ordered = false, left_ordered = false;
    int right_element, left_element;
    if (root == NULL) {
        return true;
    }
    if (root->left) {
        left_ordered = isOrderedRecursive(root->left);
        right_element = rightMost(root->left);
    }
    else {
        left_ordered = true;
        right_element = root->elem;
    }
    if (root->right) {
        right_ordered = isOrderedRecursive(root->right);
        left_element = leftMost(root->right);
    }
    else {
        right_ordered = true;
        left_element = root->elem;
    }
    if (left_ordered && right_ordered && left_element >= root->elem && right_element <= root->elem) {
        return true;
    }
    return false;
}

template <typename T>
T BinaryTree<T>::leftMost(const Node* root) const
{
    if (root->left == NULL)
        return root->elem;
    return leftMost(root->left);
}

template <typename T>
T BinaryTree<T>::rightMost(const Node* root) const
{
    if (root->right == NULL)
        return root->elem;
    return rightMost(root->right);

}

