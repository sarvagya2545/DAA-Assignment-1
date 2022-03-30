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
};