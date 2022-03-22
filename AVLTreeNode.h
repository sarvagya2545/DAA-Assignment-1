#include<stdio.h>
#include<stdlib.h>
using namespace std;

// This is the node of the events
template<class T>
class AVLTreeNode {
    public:
    T val;
    int height; // height because AVL tree used
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode<T>() {
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }

    AVLTreeNode<T>(T _val) {
        this->val = _val;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};
