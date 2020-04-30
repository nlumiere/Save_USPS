#include "BinaryTree.hpp"
#include <iostream>

using namespace std;


BinaryTree::BinaryTree(){
    root = NULL;
}


TreeNode* BinaryTree::createNode(int k){
    TreeNode *tn = new TreeNode();
    tn->key = k;
    tn->left = NULL;
    tn->right = NULL;
    return tn;
}


void BinaryTree::addNode(int k){
    TreeNode *tn = new TreeNode();
    tn->key = k;

    if(root == NULL){
        root = tn;
        return;
    }

    TreeNode *curr = root;
    while(curr != NULL){
        if(k < curr->key){
            if(curr->left != NULL){
                curr = curr->left;
            }
            else{
                curr->left = tn;
                return;
            }
        }
        else{
            if(curr->right != NULL){
                curr = curr->right;
            }
            else{
                curr->right = tn;
                return;
            }
        }
    }
}


TreeNode* BinaryTree::search(int k){
    if(root == NULL) return NULL;

    TreeNode *curr = root;
    while(curr != NULL){
        if(k < curr->key){
            curr = curr->left;
        }
        else if(k == curr->key){
            return curr;
        }
        else{
            curr = curr->right;
        }
    }
    return NULL;
    
}


void inOrder(TreeNode *curr){
    if(curr == NULL) return;
    inOrder(curr->left);
    cout << curr->key << " ";
    inOrder(curr->right);
}


void BinaryTree::printTree(){
    if(root == NULL){
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "Inorder traversal of tree: " << endl;
    cout << "Root: " << root->key << "   ";
    inOrder(root);
}