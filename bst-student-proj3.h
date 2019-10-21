/**
 * file: bst-student-proj3.h
 * author: Joshua Kanagasabai
 * course: CSI 3334
 * assignment: project 3
 * due date: October 11, 2019
 * version: 1.0
 *
 * This file contains the function definitions
 * for BSTNode BST and EncryptionTree
  *
 **/



#ifndef BST_STUDENT_PROJ3
#define BST_STUDENT_PROJ3 

#include "bst-prof-proj3.h"

/* Place your implementation of the BSTNode, BST, and EncryptionTree classes
 * here.
 *
 * Your driver should #include this file, which (as you can see above) will also
 * #include the professor file.
 */

/**
 * printPreorder
 *
 * this function recursively prints out the preorder version
 * of the tree with indents separating each level
 *
 * Parameters:
 *   os: stream for order to be output
 *   indent: the sequence to be used as the indent
 *
 * Return: -
 */

template<class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const {
    os << indent << this->data << "\n";
    if(this->left)
        this->left->printPreorder(os,indent+"  ");
    else
        os << indent+"  " << "NULL" << "\n";
    if(this->right)
        this->right->printPreorder(os,indent+"  ");
    else
        os << indent+"  " << "NULL" << "\n";
}

/**
 * destructor for BSTNode
 *
 * this function recursively deletes the entire subtree
 * of the BSTNode
 *
 * Parameters:
 *
 * Return: -
 */

template<class Base>
BSTNode<Base>::~BSTNode() {
    delete this->left;
    delete this->right;
}
/**
 * minNode
 *
 * this function iteratively finds the minimum node
 * of the subtree of BSTNode, assumes the subtree is
 * ordered correctly
 *
 * Parameters:-
 *
 * Return: the minimum node
 */

template<class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const {
    BSTNode<Base> *temp;
    if(this->left)
        temp = this->left;
    else
        return this;

    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

/**
 * maxNode
 *
 * this function iteratively finds the maximum node
 * of the subtree of BSTNode, assumes the subtree is
 * ordered correctly
 *
 * Parameters:-
 *
 * Return: the maximum node
 */

template<class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const {
    BSTNode<Base> *temp;
    if(this->right)
        temp = this->right;
    else
        return this;

    while(temp->right){
        temp = temp->right;
    }
    return temp;
}

/**
 * insert
 *
 * this function inserts a node into the tree
 *
 * Parameters: node to be inserted
 *
 * Return: -
 */

template<class Base>
void BST<Base>::insert(const Base &item) {
    if(this->root==NULL)
        this->root=new BSTNode<Base>(item);
    else{
        BSTNode<Base> *current = this->root;
        bool go =true;
        while(go){
            if(current->getData() < item){
                if(current->getRight()==NULL) {
                    current->right = new BSTNode<Base>(item);
                    go=false;
                }
                else
                    current = current->right;
            }
            else if(item < current->getData()){
                if(current->getLeft()==NULL) {
                    current->left = new BSTNode<Base>(item);
                    go=false;
                }
                else
                    current = current->left;
            }
            else
                go = false;//word already in tree

        }
    }

}

/**
 * remove
 *
 * this function deletes a node from the tree
 *
 * Parameters: node to be deleted
 *
 * Return: -
 */

template<class Base>
void BST<Base>::remove(const Base &item) {
    const int ZERO_CHILD = 0;
    const int ONE_CHILD = 1;
    const int TWO_CHILD = 2;

    if(this->root) {
        bool go = true;
        bool isRoot = false;
        BSTNode<Base> *current = this->root;
        BSTNode<Base> *currentLast = this->root;
        //for when the removed node is the root
        if (!(this->root->data < item || item < this->root->data)) {
            //cout << "got here";
            isRoot = true;
            int total = 0;
            if (current->left)
                total++;
            if (current->right)
                total++;
            if (total == ZERO_CHILD) {//if root has no children
                delete this->root;
                this->root = NULL;
            } else if (total == ONE_CHILD) {//root has 1 child
                if (current->left != NULL) {
                    this->root = current->left;
                } else {
                    this->root = current->right;
                }
                current->left = current->right = NULL;
                delete current;
            } else if (total == TWO_CHILD) {// if root has 2 children
                //cout << "2 children";
                BSTNode<Base> *leftMost = current->right;
                BSTNode<Base> *leftMostParent = current;
                if (leftMost->left != NULL) {
                    while (leftMost->left) {
                        leftMostParent = leftMost;
                        leftMost = leftMost->left;
                    }
                    leftMostParent->left = leftMost->right;
                    leftMost->right = current->right;
                }
                leftMost->left = current->left;
                this->root = leftMost;
                current->left = current->right = NULL;
                delete current;
            }
        }

        if (!isRoot) {
            bool isIn = true;
            while (go) {
                if (current->getData() < item) {
                    if (current->getRight() == NULL) {
                        go = false;//item not in tree
                        isIn = false;
                    } else {
                        currentLast = current;
                        current = current->right;
                    }
                } else if (item < current->getData()) {
                    if (current->getLeft() == NULL) {
                        go = false;//item not in tree
                        isIn = false;
                    } else {
                        currentLast = current;
                        current = current->left;
                    }
                } else
                    go = false;//found the node to delete
            }//checks if the node is in the tree
            if (isIn) {
                int total = 0;
                if (current->left)
                    total++;
                if (current->right)
                    total++;
                if (total == ZERO_CHILD) {//node to delete is a leaf
                    if (currentLast->left == current) {
                        currentLast->left = NULL;
                        delete current;
                    } else if (currentLast->right == current) {
                        currentLast->right = NULL;
                        delete current;
                    }
                } else if (total == ONE_CHILD) {//node to delete has 1 child
                    BSTNode<Base> *gChild;
                    if (current->left != NULL) {
                        gChild = current->left;
                        current->left = NULL;
                    } else {
                        gChild = current->right;
                        current->right = NULL;
                    }
                    if (currentLast->left == current) {
                        currentLast->left = gChild;
                    } else {
                        currentLast->right = gChild;
                    }
                    delete current;

                } else if (total == TWO_CHILD) {//node to delete has 2 children
                    BSTNode<Base> *leftMost = current->right;
                    BSTNode<Base> *leftMostParent = current;
                    if (leftMost->left != NULL) {
                        while (leftMost->left) {
                            leftMostParent = leftMost;
                            leftMost = leftMost->left;
                        }
                        leftMostParent->left = leftMost->right;
                        leftMost->right = current->right;
                    }

                    leftMost->left = current->left;

                    if (currentLast->left == current) {
                        currentLast->left = leftMost;
                    } else {
                        currentLast->right = leftMost;
                    }

                    current->left = current->right = NULL;
                    delete current;
                }
            }
        }
    }

}

/**
 * encrypt
 *
 * this function encrypts a given
 * item using the codebook bst
 *
 * Parameters: item to be encrypted
 *
 * Return: string representing the encrypted item
 */
template<class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const {
    string output ="r";
    bool go = true;
    if(!this->root)
        return "?";

    if (!(this->root->getData() < item || item < this->root->getData())){
        //cout << "< worked";
        return output;
        }
    const BSTNode<Base>* current = this->root;
    while (go) {
        if (current->getData() < item) { // current->getData() < item
            if(current->getRight()==NULL){
                return "?";
                //output = "?";
                //go = false;
            }
            else{
                output += "1";
                current = current->getRight();
            }
        }
        else if (item < current->getData()) {
            if(current->getLeft()==NULL){
                return "?";
                //output = "?";
                //go = false;
            }
            else{
                output += "0";
                current = current->getLeft();
            }
        }
        else {
            go = false;
        }
    }
    return output;
}

/**
 * decrypt
 *
 * this function decrypts a given path
 *
 * Parameters: path to be decrypted
 *
 * Return: reference to the item that the parameter
 * was decrypted into
 */

template<class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const {
    if(!this->root)
        return NULL;
    const BSTNode<Base>* current = this->root;
    for(unsigned int i = 1 ;i < path.length();i++){
        if(path[i]=='0'){
            if (current->getLeft())
                current = current->getLeft();
            else
                return NULL;
        }
        if(path[i]=='1'){
            if (current->getRight())
                current = current->getRight();
            else
                return NULL;
        }
    }
    return &current->getData();
}


#endif

