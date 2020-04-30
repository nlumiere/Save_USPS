#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    int numOfcolision =0;
    node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor



    // inserts a key into hash table

    // If collision occurs, adds key at next available index
    bool insertItemLinear(int key);

    // If collision occurs, increments count by one and slots in key at next available (modKey + count^2) index
    bool insertItemQuadratic(int key);

    // If collision occurs, adds key to a linked list at the end of the list at that index
    void insertItemChain(int key);

    // Ensures item is inserted successfully
    bool insertVerify(int modKey);



    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getSize();

    // Runs the hash function on the key, checks to see if resulting index is equal to key
    // Returns node if found, returns NULL if not found.
    node* searchItemLinear(int key);
    node* searchItemQuadratic(int key);

    //Iterates through linked list connected to index of hashtable to find node with matching key
    node* searchItemChain(int key);
};

#endif
