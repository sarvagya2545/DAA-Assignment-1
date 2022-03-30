#include<stdio.h>
#include<stdlib.h>
using namespace std;

/// Class representation for Status Queue
class LineStatus {
    public:
    /// AVL tree representation for status queue
    AVLTree<Segment> status;

    LineStatus() {
        
    }

    /// @brief insert function
    /// @param s Segment
    void insert(Segment s) {
        status.insert(s);
    }

    /// @brief remove function 
    /// @param s Segment
    void remove(Segment s) {
        status.remove(s);
    }

    /// @brief prints the inorder representation fo the status structure
    void print() {
        status.inorder();
    }

    /// @brief left neighbour
    /// @param Segment s
    /// @returns pair<bool, Segment> to show if the left neighbour exists and the segment which is the left neighbour
    pair<bool, Segment> leftNeighbour(Segment s) {
        AVLTreeNode<Segment>* predecessor = status.leftNeighbourAVL(s);
        if(predecessor == NULL) {
            return make_pair(false, s);
        }
        return make_pair(true, predecessor->val);
    }

    /// @brief right neighbour
    /// @param Segment s
    /// @returns pair<bool, Segment> to show if the right neighbour exists and the segment which is the right neighbour
    pair<bool, Segment> rightNeighbour(Segment s) {
        AVLTreeNode<Segment>* successor = status.rightNeighbourAVL(s);
        if(successor == NULL) {
            return make_pair(false, s);
        }
        return make_pair(true, successor->val);
    }

    /// @brief left & right neighbour of the point p
    /// @param Point p
    /// @returns pair<bool, vector<Segment>> to show if the left & right neighbour exists and the vector<Segment> which is the left & the right neighbour
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
    /// @brief Utility function to find the neighbours of a particular node in the status structure
    /// @param node an AVLTreeNode<Segment>
    /// @param p Point p
    /// @param pre AVLTreeNode<Segment> pointer which points to predecessor of the node at the end of execution
    /// @param suc AVLTreeNode<Segment> pointer which points to successor of the node at the end of execution
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