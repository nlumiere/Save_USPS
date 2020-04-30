// #include "hash.hpp"
#include "LinkedList.hpp"
#include "BinaryTree.hpp"
#include "hash.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;


//Initializes array and calls functions
int main(){
    const int SIZE = 40000;
    float insert[400];
    float insert2[400];
    float search[400];
    float search2[400];

    ifstream reader;
    reader.open("dataSetB.csv");
    int arr[SIZE];

    //cout << "hi" << endl;

    if(reader.is_open()){
        string line;
        getline(reader, line);
        int count = 0; 
        string temp = "";
        for(char c : line){
            if(count < 40000){
                if(c == ','){
                    arr[count] = stoi(temp);
                    temp = "";
                    count++;
                }
                else{
                    temp += c;
                }
            }
            else{
                break;
            }
        }
        arr[count] = stoi(temp);
    }
    reader.close();


    int num_reps = 50;
    ofstream writer;
    writer.open("linkedlist_insert_and_search_setB.csv");
    if(writer.is_open()){
        for(int jj = 0; jj < num_reps; jj++){
            writer << "Insert,";


            LinkedList ll = LinkedList();
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                ll.addNode(arr[ii]);
                if((ii+1)%100 ==0){
                    auto end = chrono::steady_clock::now();
                    insert[(ii)/100] = (chrono::duration_cast<chrono::nanoseconds>(end-start).count())/100;
                }
            }

            insert2[0] = insert[0];
            for(int ii = 1; ii < 400; ii++){
                insert2[ii] = insert[ii] - insert[ii-1];
            }

            for(int ii = 0; ii < 400; ii++){
                writer << insert2[ii];
                writer << ",";
            }
            writer << "\n";

        }

        //Creates and fills linked list for searching
        LinkedList ll = LinkedList();

        for(int ii = 0; ii < SIZE; ii++){
            ll.addNode(arr[ii]);
        }

        for(int jj = 0; jj < num_reps; jj++){
            writer << "Search,";

            //Searches for a node and keeps track of time, saving time to "search" array
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                ll.searchList(arr[ii]);
                if((ii+1)%100 ==0){
                    auto end = chrono::steady_clock::now();
                    search[ii/100] = (chrono::duration_cast<chrono::nanoseconds>(end-start).count())/100;
                }
            }
            auto end = chrono::steady_clock::now();

            //Prepares search2 to not be cumulative
            search2[0] = search[0];
            for(int ii = 1; ii < 400; ii++){
                search2[ii] = search[ii] - search[ii-1];
            }

            for(int ii = 0; ii < 400; ii++){
                writer << search2[ii];
                writer << ",";
            }

            writer << "\n";
        }

        writer.close();
    }

    // HashTable ht = HashTable(SIZE + 9);
    // auto start = chrono::steady_clock::now();
    // for(int ii = 0; ii < SIZE; ii++){
    //     ht.insertItemChain(arr[ii]);
    //     if(ii%100 ==0){
    //         auto end = chrono::steady_clock::now();
    //         insert[ii/100] = (chrono::duration_cast<chrono::nanoseconds>(end-start).count())/100;
    //     }
    // }
    // auto end = chrono::steady_clock::now();

    // insert2[0] = insert[0];
    // for(int ii = 1; ii < 400; ii++){
    //     insert2[ii] = insert[ii] - insert[ii-1];
    // }

    // for(int ii = 0; ii < 400; ii++){
    //     cout << insert2[ii] << endl;
    // }
    // ht.printTable();

    return 0;
}