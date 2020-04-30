#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include "hash.hpp"

using namespace std;

class LinkedList{
    
    int length;
    node* head;

public:
    //Sets head to null, length to 0
    LinkedList();

    //Adds a node to the list, with the given key
    bool addNode(int key);

    //Traverses the linkedlist and prints the contents of all the nodes
    void printList();

    //Traverses the linkedlist and returns a pointer to the node with a matching key
    node* searchList(int key);

};
#endif