#include <iostream>
#include "AVLTreeNode.h"
using namespace std;

// T is the value of node class
template<class T>
class AVLTree {
    public:
        AVLTreeNode<T> *root = NULL;

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
        }

        AVLTreeNode<T>* maxNode(AVLTreeNode<T>* node = NULL) {
            if(!node) node = this->root;

            while(node->right != NULL) {
                node = node->right;
            }

            return node;
        }

        AVLTreeNode<T>* minNode(AVLTreeNode<T>* node = NULL) {
            if(!node) node = this->root;

            while(node->left != NULL) {
                node = node->left;
            }

            return node;
        }

        AVLTreeNode<T>* leftNeighbour(T _val) {
            return leftNeighbourUtil(root, _val);
        }

        AVLTreeNode<T>* rightNeighbour(T _val) {
            return rightNeighbourUtil(root, _val);
        }

        vector<AVLTreeNode<T>* > neighbours(T _val) {
            vector<AVLTreeNode<T>*> n;
            n.push_back(leftNeighbourUtil(root, _val));
            n.push_back(rightNeighbourUtil(root, _val));
            return n;
        }

    protected:
        int height(AVLTreeNode<T> *node) {
            if (node == NULL)
                return 0;
            return node->height;
        }

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
            cout << "Node value: " << head->val << " level = " << level << " \n";
            inorderUtil(head->right, level + 1);
        }

        AVLTreeNode<T> *insertUtil(AVLTreeNode<T> *root, T val) {
            if (root == NULL) {
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

        AVLTreeNode<T> *leftNeighbourUtil(AVLTreeNode<T> *node, T _val, AVLTreeNode<T> *pre = NULL) {
            if(node == NULL)
                return NULL;

            if(node->val == _val) {
                // if node has left sub tree, the max node of it is the left neighbour
                if(node->left != NULL) {
                    return maxNode(node->left);
                }
                // else return the predecessor
                return pre;
            } else if(node->val > _val) {
                return leftNeighbourUtil(node->left, _val, pre);
            } else if(node->val < _val) {
                // possible value for predecessor
                pre = node;
                return leftNeighbourUtil(node->right, _val, pre);
            }
        }


        AVLTreeNode<T> *rightNeighbourUtil(AVLTreeNode<T> *node, T _val, AVLTreeNode<T> *suc = NULL) {
            if(node == NULL)
                return NULL;

            if(node->val == _val) {
                // if node has right sub tree, the min node of it is the right neighbour
                if(node->right != NULL) {
                    return minNode(node->right);
                }
                // else return the successor
                return suc;
            } else if(node->val > _val) {
                // possible value for successor
                suc = node;
                return rightNeighbourUtil(node->left, _val, suc);
            } else if(node->val < _val) {
                return rightNeighbourUtil(node->right, _val, suc);
            }
        }
};