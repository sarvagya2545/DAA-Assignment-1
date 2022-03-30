#include<stdio.h>
#include<stdlib.h>
using namespace std;

/// This is the node of the events
template<class T>
class AVLTreeNode {
    public:
    T val; //!< value stored in the node
    int height; ///!< height of the subtree rooted at this node
    AVLTreeNode<T>* left; ///!< pointer to the left child of node
    AVLTreeNode<T>* right; ///!< pointer to the right child of node

    /// @brief Default constructor for the AVLTreeNode
    AVLTreeNode<T>() {
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }

    /// @brief Constructor with value
    /// @param _val The node value
    AVLTreeNode<T>(T _val): val(_val) {
        // this->val = _val;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};
