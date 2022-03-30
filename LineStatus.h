#include<stdio.h>
#include<stdlib.h>
using namespace std;

class LineStatus {
    public:
    AVLTree<Segment> status;

    LineStatus() {
        
    }

    void insert(Segment s) {
        status.insert(s);
    }

    void remove(Segment s) {
        status.remove(s);
    }

    void print() {
        status.inorder();
    }

    Segment leftNeighbour(Segment s) {
        
    }

    Segment rightNeighbour(Segment s) {
        
    }

    vector<Segment> neighbours(Point p) {
        
    }

    protected:
    // AVLTreeNode<Segment> *leftNeighbourUtil(AVLTreeNode<Segment> *node, Point p, AVLTreeNode<Segment> *pre = NULL) {
    //     if(node == NULL)
    //         return NULL;

    //     if(node->val == _val) {
    //         // if node has left sub tree, the max node of it is the left neighbour
    //         if(node->left != NULL) {
    //             return maxNode(node->left);
    //         }
    //         // else return the predecessor
    //         return pre;
    //     } else if(node->val > _val) {
    //         return leftNeighbourUtil(node->left, _val, pre);
    //     } else if(node->val < _val) {
    //         // possible value for predecessor
    //         pre = node;
    //         return leftNeighbourUtil(node->right, _val, pre);
    //     }
    // }


    // AVLTreeNode<Segment> *rightNeighbourUtil(AVLTreeNode<Segment> *node, Point p, AVLTreeNode<Segment> *suc = NULL) {
    //     if(node == NULL)
    //         return NULL;

    //     if(node->val == _val) {
    //         // if node has right sub tree, the min node of it is the right neighbour
    //         if(node->right != NULL) {
    //             return minNode(node->right);
    //         }
    //         // else return the successor
    //         return suc;
    //     } else if(node->val > _val) {
    //         // possible value for successor
    //         suc = node;
    //         return rightNeighbourUtil(node->left, _val, suc);
    //     } else if(node->val < _val) {
    //         return rightNeighbourUtil(node->right, _val, suc);
    //     }
    // }
};