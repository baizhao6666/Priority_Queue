/**------------------------------------------
Project 5: Priority Queue
Course: CS 251, Spring 2023, UIC
System: CLion on MacOs
Author: Baizhao Zhao, starter code provided by Dr. Adam Koehler
-------------------------------------------*/
/// @file priorityqueue.h
///
///
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    /**
     * inorder traverse the tree and store the information into output
     * @param node current code
     * @param output an stringstream object to store information
     */
    void inorderTraverse(NODE* node, ostream& output) {
        // base case - return
        if (node == nullptr) {
            return;
        }

        // recursively traverse the tree
        inorderTraverse(node->left, output);
        // record the information
        output << node->priority << " value: " << node->value << endl;
        NODE* pCur = node->link;
        // if there are duplicated nodes
        while (pCur != nullptr) {
            output << pCur->priority << " value: " << pCur->value << endl;
            pCur = pCur->link;
        }
        inorderTraverse(node->right, output);
    }

    /**
     * postorder traverse the tree and delete every node
     * @param node current node
     */
    void postorderTraverse(NODE* &node){
        // base case - return
        if (node == nullptr) {
            return;
        }

        // recursively traverse the tree
        postorderTraverse(node->left);
        postorderTraverse(node->right);
        // delete current node
        NODE* pCur = node->link;
        // if there are duplicated nodes
        while (pCur != nullptr) {
            NODE* pTemp = pCur->link;
            delete pCur;
            pCur = pTemp;
            size--;
        }
        delete node;
        node = nullptr;
        size--;
    }

    /**
     * preorder traverse the tree and copy every node in "this" tree
     * @param node current node
     */
    void copy(NODE* node) {
        // base case - return
        if (node == nullptr) {
            return;
        }

        // insert a new node to "this" tree
        enqueue(node->value, node->priority);
        NODE* pTemp = node->link;
        // if there are duplicated nodes
        while (pTemp != nullptr) {
            enqueue(pTemp->value, pTemp->priority);
            pTemp = pTemp->link;
        }
        copy(node->left);
        copy(node->right);
    }

    /**
     * recursively compare two tree to see if they are equal
     * @param thisNode "this" tree
     * @param otherNode the tree to be compare
     * @return true if they are equal
     */
    bool compareTo(NODE* thisNode, NODE* otherNode) const {
        // if both nodes are null, means they are equal
        if (thisNode == nullptr && otherNode == nullptr) {
            return true;
        }
        // false when "this" node is null but not "other"
        if (thisNode == nullptr) {
            return false;
        }
        // false when "other" node is null but not "this"
        if (otherNode == nullptr) {
            return false;
        }
        // false when either value or priority is not equal
        if (thisNode->value != otherNode->value ||
            thisNode->priority != otherNode->priority) {
            return false;
        }

        // recursive step
        return compareTo(thisNode->link, otherNode->link) &&
                compareTo(thisNode->left, otherNode->left) &&
                compareTo(thisNode->right, otherNode->right);
    }
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = root;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        if (this != &other) {    // not copying itself
            // clear "this" tree;
            clear();

            // go over "other" tree and copy every node
            copy(other.root);
        }

        return *this;
        
        
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        postorderTraverse(root);
        
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        clear();
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        // create a new node
        NODE* newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->dup = false;
        newNode->link = nullptr;
        newNode->parent = nullptr;
        // if the tree is empty
        if (root == nullptr) {
            // make root be the new node
            root = newNode;
            size++;
            return;
        }

        // if there is more than 1 node in the tree
        // go over the tree
        NODE* pCur = root;
        NODE* pParent = root;
        while (pCur != nullptr) {
            // find the correct spot
            if (pCur->priority < priority) {
                pParent = pCur;
                pCur = pCur->right;
            } else if (pCur->priority > priority) {
                pParent = pCur;
                pCur = pCur->left;
            } else {
                break;
            }
        }
        // add the new node to the tree
        if (pCur == nullptr) { // reach the leaf node and no dup node
            // priority is greater than the previous node
            if (pParent->priority < priority) {
                pParent->right = newNode;
                newNode->parent = pParent;
            } else {
                // priority is less than the previous node
                pParent->left = newNode;
                newNode->parent = pParent;
            }
        } else {    // there are dup nodes
            // go to the end of list
            while (pCur->link != nullptr) {
                pCur = pCur->link;
            }
            if (!pCur->dup) {
                pCur->dup = true;
            }
            newNode->dup = true;
            pCur->link = newNode;
            newNode->parent = pCur;
        }
        size++;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        T valueOut = {};
        // if the queue is empty, return default value of T
        if (size == 0) {
            return valueOut;
        }
        begin();    // make curr node to be the highest priority in the queue
        if (curr == root) {
            if (root->link != nullptr) {    // if there are duplicated nodes on root
                NODE* rChild = root->right; // get the right child
                root = root->link;          // advance root to duplicated node
                root->right = rChild;       // link right child
                valueOut = curr->value;     // get valueOut
                delete curr;                // delete the memory
                curr = nullptr;
                size--;
                return valueOut;
            } else if (curr->right == nullptr) {    // if the root is the only node in the queue
                valueOut = root->value;             // get valueOut
                delete root;                        // delete the memory
                root = nullptr;
                curr = nullptr;
                size--;
                return  valueOut;
            }
            // the root is not the only node in queue
            valueOut = root->value;
            root = root->right;
            root->parent = nullptr;
        } else {
            valueOut = curr->value;
            NODE* parent = curr->parent;
            NODE* rightChild = curr->right;
            if (curr->link != nullptr) {        // if there are duplicated node on curr node
                NODE* pTemp = curr->link;       // get the duplicated node
                parent->left = pTemp;           // link it to parent
                pTemp->parent = parent;
                pTemp->right = rightChild;      // link the right child
                if (rightChild != nullptr) {
                    rightChild->parent = pTemp;
                }
            } else {                            // there is no duplicated node
                parent->left = rightChild;
                if (rightChild != nullptr) {
                    rightChild->parent = parent;
                }
            }
        }
        delete curr;        // delete the memory
        curr = nullptr;
        size--;             // update size
        return valueOut;
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        if (size == 0) {    // the tree is empty
            curr = nullptr;
        } else {            // the tree is not empty
            curr = root;    // find the left-most node
            while (curr->left != nullptr) {
                curr = curr->left;
            }
        }
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        // if the tree is empty
        if (curr == nullptr) {
            return false;
        }
        value = curr->value;
        priority = curr->priority;
        if (curr->link != nullptr) {    // if there are duplicated node
            curr = curr->link;
            return true;
        } else {                        // reach the end of duplicated node
            while (curr->parent != nullptr && curr->parent->link == curr) {
                curr = curr->parent;
            }
        }

        if (curr->right != nullptr) {           // if the right subtree is not empty
            // find the highest priority node in the right subtree
            curr = curr->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
        } else if (curr->right == nullptr) {    // if the right subtree is empty
            // travel up the tree and find a node which is the left child of its parent
            while (curr->parent != nullptr && curr != curr->parent->left) {
                curr = curr->parent;
            }
            // if we reach the root, means there is no more node available
            if (curr->parent == nullptr) {
                curr = nullptr;     // set curr to be nullptr
                return false;
            }
            curr = curr->parent;
        }
        return true;
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        string str;
        stringstream ss;    // stringstream object to store the string of tree
        inorderTraverse(root, ss);  // traverse the tree inorder
        str = ss.str();     // convert it to string
        return str;

    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        T valueOut = {};
        if (size == 0) {
            return valueOut;
        }
        begin();
        valueOut = curr->value;
        return valueOut;
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        // is their sizes are different
        if (size != other.size) {
            return false;
        }

        return compareTo(this->root, other.root);
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
