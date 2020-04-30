#include "hash.hpp"
#include <iostream>

using namespace std;

HashTable::HashTable(int bsize){
    tableSize = bsize;
    table = new node*[tableSize];
    for(int ii = 0; ii < tableSize; ii++){
        table[ii] = NULL;
    }
    numOfcolision = 0;
}

int HashTable::getSize(){
    cout << "test" << endl;
    for(int ii = 0; ii < tableSize; ii++){
        cout << table[ii] << endl;
    }
    cout << "test" << endl;
    return tableSize;
}

node* HashTable::createNode(int k, node *next){
    node *n = new node();
    n->key = k;
    n->next = next;
    return n;
}

bool HashTable::insertVerify(int modKey){
    if(table[modKey] == NULL){
        return false;
    }
    return true;
}


//The one I don't like
bool HashTable::insertItemLinear(int k){
    unsigned int modKey = hashFunction(k);
    while(table[modKey] != NULL){
        modKey++;
        modKey %= tableSize;
    }
    table[modKey] = createNode(k, NULL);
    return(insertVerify(modKey));
}

//The one I think is wack
bool HashTable::insertItemQuadratic(int k){
    unsigned int modKey = hashFunction(k);
    int count = 1;
    while(table[modKey] != NULL){
        modKey += count*count;
        modKey %= tableSize;
        count++;
    }
    table[modKey] = createNode(k, NULL);
    return insertVerify(modKey);
}

//The one I like
void HashTable::insertItemChain(int k){
    unsigned int modKey = hashFunction(k);
    if(table[modKey] != NULL){
        node *temp = table[modKey];
        node *newNode = createNode(k, NULL);
        newNode->next = temp;
        table[modKey] = newNode;
        return;
    }
    table[modKey] = createNode(k, NULL);
}

unsigned int HashTable::hashFunction(int key){
    return key = key % tableSize;
}

void HashTable::printTable(){
    for(int ii = 0; ii < tableSize; ii++){
        if(table[ii] != NULL){
            if(table[ii]->next != NULL){
                node *curr = table[ii];
                while(curr != NULL){
                    cout << curr->key << " ";
                    curr = curr->next;
                }
                cout << endl;
            }
            else{
                cout << table[ii]->key << " " << endl;
            }
        }
        else{
            cout << "NULL" << endl;
        }
    }
}

node* HashTable::searchItemLinear(int key){
    int modKey = hashFunction(key);
    while(table[modKey]->key != key){
        modKey++;
        modKey %= tableSize;
        if(modKey == hashFunction(key)) return NULL;
    }
    return table[modKey];
}

node* HashTable::searchItemQuadratic(int key){
    int modKey = hashFunction(key);
    int count = 1;
    while(table[modKey]->key != key){
        modKey += count*count;
        count++;
        modKey %= tableSize;
        if(count >= tableSize) return NULL;
    }
    return table[modKey];
}

node* HashTable::searchItemChain(int key){
    int modKey = hashFunction(key);
    if(table[modKey]->next != NULL){
        node *curr = table[modKey];
        while(curr->next != NULL){
            curr = curr->next;
            if(curr->key == key){
                return curr;
            }
        }
    }
    return NULL;
}