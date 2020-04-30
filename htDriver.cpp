// #include "hash.hpp"
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



    // The number of times the experiment will be run 
    // I decided this was necessary as the run time recorded by my computer had a large amount of variability
    int num_reps = 500;
    ofstream writer;
    writer.open("hashtable_chaining_insert_and_search_setB.csv");
    if(writer.is_open()){
        for(int jj = 0; jj < num_reps; jj++){
            writer << "Insert,";

            HashTable ht = HashTable(SIZE + 9);
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                // Change this function to linear, quadratic or chain to determine the implementation of the hash table
                ht.insertItemChain(arr[ii]);
                if(ii%100 ==0){
                    auto end = chrono::steady_clock::now();
                    insert[ii/100] = (chrono::duration_cast<chrono::nanoseconds>(end-start).count())/100;
                }
            }
            auto end = chrono::steady_clock::now();

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

        HashTable ht = HashTable(SIZE + 9);
        for(int ii = 0; ii < SIZE; ii++){
            // Change this function to linear, quadratic or chain to determine the implementation of the hash table
            ht.insertItemChain(arr[ii]);
        }

        for(int ii = 0; ii < num_reps; ii++){
            writer << "Search,";

            //Searches for a node and keeps track of time, saving time to search array
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                // Change this function to linear, quadratic or chain to determine the implementation of the hash table
                ht.searchItemChain(arr[ii]);
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
    }

    // ht.printTable();

    return 0;
}