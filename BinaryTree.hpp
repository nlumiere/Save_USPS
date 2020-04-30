#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

struct TreeNode
{
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

class BinaryTree{
    TreeNode* root;
public:
    //Initializes root to null
    BinaryTree();

    //Creates a node
    TreeNode* createNode(int key);

    //Adds a node to the tree
    void addNode(int key);

    //Searches the tree for a specific key, returns node
    TreeNode* search(int key);

    //Displays the tree
    void printTree();
};
#endif
