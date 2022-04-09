#include <iostream>
#include "AVLTreeNode.h"
using namespace std;

/// @brief Implementation for balanced BST using AVL Tree
template<class T>
class AVLTree {
    public:
        /// root node 
        AVLTreeNode<T> *root = NULL;

        /// @brief Insert function to insert a node
        /// @param val of type T (template) 
        void insert(T val) {
            root = insertUtil(root, val);
        }

        /// @brief Remove function to remove a node
        /// @param val of type T (template) 
        void remove(T val) {
            root = removeUtil(root, val);
        }

        /// @brief Search function
        /// @param val of type T (template) 
        /// @returns a node pointer of type AVLTreeNode<T>* pointing to the found node
        AVLTreeNode<T> *search(T val) {
            return searchUtil(root, val);
        }

        /// @brief Function to print an inorder traversal of the binary search tree
        void inorder() {
            inorderUtil(root);
        }

        /// @brief Function to get the max node of the AVL tree or the subtree rooted at the node given
        /// @param node The root of the subtree
        /// @returns Pointer of type AVLTreeNode<T> which points to the max node
        AVLTreeNode<T>* maxNode(AVLTreeNode<T>* node = NULL) {
            if(!node) node = this->root;

            while(node->right != NULL) {
                node = node->right;
            }

            return node;
        }

        /// @brief Function to get the min node of the AVL tree or the subtree rooted at the node given
        /// @param node The root of the subtree
        /// @returns Pointer of type AVLTreeNode<T> which points to the min node
        AVLTreeNode<T>* minNode(AVLTreeNode<T>* node = NULL) {
            if(!node) node = this->root;

            while(node->left != NULL) {
                node = node->left;
            }

            return node;
        }


        /// @brief Function to get the left neighbour of the value given in the node
        /// @param _val a value of type T
        /// @returns Pointer of type AVLTreeNode<T> which points to the left neighbour of _val
        AVLTreeNode<T>* leftNeighbourAVL(T _val) {
            return leftNeighbourUtil(root, _val);
        }

        /// @brief Function to get the right neighbour of the value given in the node
        /// @param _val a value of type T
        /// @returns Pointer of type AVLTreeNode<T> which points to the right neighbour of _val
        AVLTreeNode<T>* rightNeighbourAVL(T _val) {
            return rightNeighbourUtil(root, _val);
        }

        /// @brief Function to get both the left & right neighbours of the value given in the node
        /// @param _val a value of type T
        /// @returns vector containing 2 pointers of type AVLTreeNode<T> which point to the left & right neighbours of the AVL tree
        vector<AVLTreeNode<T>* > neighbours(T _val) {
            vector<AVLTreeNode<T>*> n;
            n.push_back(leftNeighbourUtil(root, _val));
            n.push_back(rightNeighbourUtil(root, _val));
            return n;
        }

    protected:
        /// @brief Function to get height of the subtree rooted at the node
        /// @param node of type AVLTreeNode<T>*  
        /// @returns integer value representing the height of the subtree rooted at the node
        int height(AVLTreeNode<T> *node) {
            if (node == NULL)
                return 0;
            return node->height;
        }

        /// @brief Function to right rotate the AVLtree at node
        /// @param node of type AVLTreeNode<T>*  
        /// @returns node pointer of type AVLTreeNode<T> which contains a new subtree with right rotation done
        AVLTreeNode<T> *rightRotation(AVLTreeNode<T> *node) {
            AVLTreeNode<T> *newNode = node->left;
            node->left = newNode->right;
            newNode->right = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        /// @brief Function to left rotate the AVLtree at node
        /// @param node of type AVLTreeNode<T>*  
        /// @returns node pointer of type AVLTreeNode<T> which contains a new subtree with left rotation done
        AVLTreeNode<T> *leftRotation(AVLTreeNode<T> *node) {
            AVLTreeNode<T> *newNode = node->right;
            node->right = newNode->left;
            newNode->left = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        /// @brief Utility function for inorder traversal
        /// @param head of type AVLTreeNode<T>*  
        /// @param level integer to show the level(depth) of the nodes in the binary search tree
        void inorderUtil(AVLTreeNode<T> *head, int level = 0) {
            if (head == NULL)
                return;
            inorderUtil(head->left, level + 1);
            cout << "Node value: " << head->val << " level = " << level << " \n";
            inorderUtil(head->right, level + 1);
        }

        /// @brief Utility function to insert a node in the AVL tree
        /// @param root of type AVLTreeNode<T>* representing the current node 
        /// @param val value which need to be inserted
        /// @returns node pointer of type AVLTreeNode<T> which contains a new subtree with the element inserted
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

        /// @brief Utility function to remove a node in the AVL tree
        /// @param node of type AVLTreeNode<T>* representing the current node 
        /// @param val value which need to be removed
        /// @returns node pointer of type AVLTreeNode<T> which contains a new subtree with the element removed
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
                if (height(node->left->left) - height(node->left->right) >= 0) {
                    return rightRotation(node);
                } else {
                    node->left = leftRotation(node->left);
                    return rightRotation(node);
                }
            } else if (bal < -1) {
                if (height(node->right->left) - height(node->right->right) <= 0) {
                    return leftRotation(node);
                } else {
                    node->right = rightRotation(node->right);
                    return leftRotation(node);
                }
            }
            return node;
        }

        /// @brief Utility function to search a node in the AVL tree
        /// @param head of type AVLTreeNode<T>* representing the current node 
        /// @param val value which need to be searched
        /// @returns a pointer to the node of the searched value
        AVLTreeNode<T> *searchUtil(AVLTreeNode<T> *head, T val) {
            if (head == NULL)
                return NULL;
            if (head->val == val)
                return head;
            if (head->val > val)
                return searchUtil(head->left, val);
            if (head->val < val)
                return searchUtil(head->right, val);

            return NULL;
        }

        /// @brief Utility function to find the left neighbour in the AVL tree
        /// @param node of type AVLTreeNode<T>* representing the current node 
        /// @param val value which need to be searched
        /// @returns a pointer to the left neighbour of val
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

            return NULL;
        }

        /// @brief Utility function to find the right neighbour in the AVL tree
        /// @param node of type AVLTreeNode<T>* representing the current node 
        /// @param val value which need to be searched
        /// @returns a pointer to the right neighbour of val
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

            return NULL;
        }
};