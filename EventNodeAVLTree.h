#include <iostream>
#include "EventNode.h"
using namespace std;

class EventAVLTree {
    public:
        EventNode *root = NULL;
        int n;

        void insert(int x, int y) {
            root = insertUtil(root, x, y);
        }

        void remove(int x, int y) {
            root = removeUtil(root, x, y);
        }

        EventNode *search(int x, int y) {
            return searchUtil(root, x, y);
        }

        void inorder() {
            inorderUtil(root);
            cout << endl;
        }

    protected:
        int height(EventNode *node) {
            if (node == NULL)
                return 0;
            return node->height;
        }

        // Compares the values of x and y with the current node
        // return 1 if new node is chronologically higher than current node
        // return 0 if new node has the same values as the current node
        // return -1 if new node is chronologically lower than current node
        int compareEventNode(EventNode* node, int x, int y) {
            if(node->y > y || (node->y == y && node->x < x)) {
                // curr node is chronologically higher
                return -1;
            } else if(node->x == x && node->y == y) {
                return 0;
            } else {
                // curr node is chronologically lower
                return 1;
            }
        };

        EventNode *rightRotation(EventNode *node) {
            EventNode *newNode = node->left;
            node->left = newNode->right;
            newNode->right = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        EventNode *leftRotation(EventNode *node) {
            EventNode *newNode = node->right;
            node->right = newNode->left;
            newNode->left = node;
            node->height = 1 + max(height(node->left), height(node->right));
            newNode->height = 1 + max(height(newNode->left), height(newNode->right));
            return newNode;
        }

        void inorderUtil(EventNode *head) {
            if (head == NULL)
                return;
            inorderUtil(head->left);
            cout << head->x << "," << head->y << " ";
            inorderUtil(head->right);
        }

        EventNode *insertUtil(EventNode *root, int x, int y) {
            if (root == NULL) {
                n += 1;
                EventNode *temp = new EventNode(x, y);
                return temp;
            }

            int res = compareEventNode(root, x, y);

            if (res == -1)
                root->left = insertUtil(root->left, x, y);
            else if (res == 1)
                root->right = insertUtil(root->right, x, y);

            root->height = 1 + max(height(root->left), height(root->right));

            // balance heights
            int bal = height(root->left) - height(root->right);
            if (bal > 1) {
                if (compareEventNode(root->left, x, y) == -1) {
                    return rightRotation(root);
                } else {
                    root->left = leftRotation(root->left);
                    return rightRotation(root);
                }
            } else if (bal < -1) {
                if (compareEventNode(root->right, x, y) == 1) {
                    return leftRotation(root);
                } else {
                    root->right = rightRotation(root->right);
                    return leftRotation(root);
                }
            }

            return root;
        }

        EventNode *removeUtil(EventNode *node, int x, int y) {
            if (node == NULL)
                return NULL;

            int res = compareEventNode(node, x, y);

            if (res == -1) {
                node->left = removeUtil(node->left, x, y);
            } else if (res == 1) {
                node->right = removeUtil(node->right, x, y);
            } else {
                // delete the current node
                EventNode *r = node->right;
                if (node->right == NULL) {
                    EventNode *l = node->left;
                    delete (node);
                    node = l;
                } else if (node->left == NULL) {
                    delete (node);
                    node = r;
                } else {
                    while (r->left != NULL)
                        r = r->left;

                    node->x = r->x;
                    node->y = r->y;

                    node->right = removeUtil(node->right, r->x, r->y);
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

        EventNode *searchUtil(EventNode *head, int x, int y) {
            if (head == NULL)
                return NULL;
            int res = compareEventNode(head, x, y);
            if (res == 0)
                return head;
            if (res == -1)
                return searchUtil(head->left, x, y);
            if (res == 1)
                return searchUtil(head->right, x, y);
        }
};