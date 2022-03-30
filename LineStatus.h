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

    pair<bool, Segment> leftNeighbour(Segment s) {
        AVLTreeNode<Segment>* predecessor = status.leftNeighbourAVL(s);
        if(predecessor == NULL) {
            return make_pair(false, s);
        }
        return make_pair(true, predecessor->val);
    }

    pair<bool, Segment> rightNeighbour(Segment s) {
        AVLTreeNode<Segment>* successor = status.rightNeighbourAVL(s);
        if(successor == NULL) {
            return make_pair(false, s);
        }
        return make_pair(true, successor->val);
    }

    pair<bool,vector<Segment>> neighbours(Point p) {
        AVLTreeNode<Segment> *pre = NULL, *suc = NULL;
        neighboursUtil(status.root, p, pre, suc);
        
        vector<Segment> neighbrs;
        if(pre == NULL || suc == NULL) {
            return make_pair(false, neighbrs);
        }
        neighbrs.push_back(pre->val);
        neighbrs.push_back(suc->val);
        return make_pair(true, neighbrs);
    }

    protected:
    void neighboursUtil(AVLTreeNode<Segment> *node, Point p, AVLTreeNode<Segment> *&pre, AVLTreeNode<Segment> *&suc) {
        if(node == NULL) {
            return;
        }

        float node_x = node->val.x(Segment::sweeplineY);
        float point_x = p.x;
        if(node_x < point_x) {
            pre = node;
            neighboursUtil(node->right, p, pre, suc);
        } else if(node_x > point_x) {
            suc = node;
            neighboursUtil(node->left, p, pre, suc);
        } else {
            // node_x == point_x
            if(node->left != NULL) {
                pre = status.maxNode(node->left);
            }

            if(node->right != NULL) {
                suc = status.minNode(node->right);
            }

            return;
        }
    }

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