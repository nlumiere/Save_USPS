#include "LinkedList.hpp"
#include <iostream>
using namespace std;

/**
 * See LinkedList.hpp for documentation
 */

LinkedList::LinkedList(){
    head = NULL;
}

bool LinkedList::addNode(int k){
    node *n = new node();
    n->key = k;
    if(head == NULL){
        head = n;
    }
    else{
        node *curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
    }
    return true;
}

void LinkedList::printList(){
    if(head == NULL) return;
    node *curr = head;
    while(curr != NULL){
        cout << curr->key << endl;
        curr = curr->next;
    }
}

node* LinkedList::searchList(int i){
    if(head == NULL) return NULL;
    node *curr = head;
    while(curr != NULL){
        if(curr->key == i){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}