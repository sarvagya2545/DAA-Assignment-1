#include <iostream>
#include "AVLTreeNode.h"
using namespace std;

// T is the value of node class
template<class T>
class AVLTree {
    public:
        AVLTreeNode<T> *root = NULL;
        int n;

        void insert(T val) {
            root = insertUtil(root, val);
        }

        void remove(T val) {
            root = removeUtil(root, val);
        }

        AVLTreeNode<T> *search(T val) {
            return searchUtil(root, val);
        }

        void inorder() {
            inorderUtil(root);
            cout << endl;
        }

    protected:
        int height(AVLTreeNode<T> *node) {
            if (node == NULL)
                return 0;
            return node->height;
        }

        // BAD IDEA! overload comparison operators instead
        // Compares the values of x and y with the current node
        // return 1 if new node is chronologically higher than current node
        // return 0 if new node has the same values as the current node
        // return -1 if new node is chronologically lower than current node
        // int compareEventNode(T* node, int x, int y) {
        //     if(node->y > y || (node->y == y && node->x < x)) {
        //         // curr node is chronologically higher
        //         return -1;
        //     } else if(node->x == x && node->y == y) {
        //         return 0;
        //     } else {
        //         // curr node is chronologically lower
        //         return 1;
        //     }
        // };

        AVLTreeNode<T> *rightRotation(AVLTreeNode<T> *node) {
            AVLTreeNode<T> *newNode = node->left;
            node->left = newNode->right;
            newNode->right = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        AVLTreeNode<T> *leftRotation(AVLTreeNode<T> *node) {
            AVLTreeNode<T> *newNode = node->right;
            node->right = newNode->left;
            newNode->left = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        void inorderUtil(AVLTreeNode<T> *head, int level = 0) {
            if (head == NULL)
                return;
            inorderUtil(head->left, level + 1);
            cout << head->val << " level = " << level << " \n";
            inorderUtil(head->right, level + 1);
        }

        AVLTreeNode<T> *insertUtil(AVLTreeNode<T> *root, T val) {
            if (root == NULL) {
                n += 1;
                AVLTreeNode<T> *temp = new AVLTreeNode<T>(val);
                return temp;
            }

            if (root->val > val)
                root->left = insertUtil(root->left, val);
            else if (root-> val < val)
                root->right = insertUtil(root->right, val);

            root->height = 1 + max(height(root->left), height(root->right));

            // balance heights
            int bal = height(root->left) - height(root->right);
            if (bal > 1) {
                if (root->left->val > val) {
                    return rightRotation(root);
                } else {
                    root->left = leftRotation(root->left);
                    return rightRotation(root);
                }
            } else if (bal < -1) {
                if (root->right->val < val) {
                    return leftRotation(root);
                } else {
                    root->right = rightRotation(root->right);
                    return leftRotation(root);
                }
            }

            return root;
        }

        AVLTreeNode<T> *removeUtil(AVLTreeNode<T> *node, T val) {
            if (node == NULL)
                return NULL;

            if (node->val > val) {
                node->left = removeUtil(node->left, val);
            } else if (node->val < val) {
                node->right = removeUtil(node->right, val);
            } else {
                // delete the current node
                AVLTreeNode<T> *r = node->right;
                if (node->right == NULL) {
                    AVLTreeNode<T> *l = node->left;
                    delete (node);
                    node = l;
                } else if (node->left == NULL) {
                    delete (node);
                    node = r;
                } else {
                    while (r->left != NULL)
                        r = r->left;

                    node->val = r->val;

                    node->right = removeUtil(node->right, r->val);
                }
            }
            
            // balance the AVL tree
            if (node == NULL)
                return node;

            node->height = 1 + max(height(node->left), height(node->right));
            
            int bal = height(node->left) - height(node->right);
            if (bal > 1) {
                if (height(node->left) >= height(node->right)) {
                    return rightRotation(node);
                } else {
                    node->left = leftRotation(node->left);
                    return rightRotation(node);
                }
            } else if (bal < -1) {
                if (height(node->right) >= height(node->left)) {
                    return leftRotation(node);
                } else {
                    node->right = rightRotation(node->right);
                    return leftRotation(node);
                }
            }
            return node;
        }

        AVLTreeNode<T> *searchUtil(AVLTreeNode<T> *head, T val) {
            if (head == NULL)
                return NULL;
            if (head->val == val)
                return head;
            if (head->val > val)
                return searchUtil(head->left, val);
            if (head->val < val)
                return searchUtil(head->right, val);
        }
};

// int main() {
//     AVLTree<int>* root = new AVLTree<int>();
//     root->insert(5);
//     root->insert(1);
//     root->insert(2);
//     root->insert(3);
//     root->insert(3);
//     root->insert(4);
//     root->inorder();
//     root->remove(5);
//     root->inorder();
//     return 0;
// }