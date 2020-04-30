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
    reader.open("dataSetA.csv");
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

    //Number of times I'll run the experiment
    int num_reps = 500;
    ofstream writer;
    writer.open("binarytree_insert_and_search_setA_2.csv");
    if(writer.is_open()){

        //Will average all the times the experiment runs for more accurate curve
        for(int jj = 0; jj < num_reps; jj++){
            writer << "Insert,";

            BinaryTree bt = BinaryTree();

            //Determines time it takes to add all the nodes to the tree
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                bt.addNode(arr[ii]);
                if((ii+1)%100 ==0){
                    auto end = chrono::steady_clock::now();
                    insert[ii/100] = (chrono::duration_cast<chrono::nanoseconds>(end-start).count())/100;
                }
            }

            //Prepares insert2 array (not efficient, I know)
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

        //Creates and fills binary tree for searching
        BinaryTree bt = BinaryTree();

        for(int ii = 0; ii < SIZE; ii++){
            bt.addNode(arr[ii]);
        }

        for(int jj = 0; jj < num_reps; jj++){
            writer << "Search,";

            //Searches for a node and keeps track of time, saving time to search array
            auto start = chrono::steady_clock::now();
            for(int ii = 0; ii < SIZE; ii++){
                TreeNode* t = bt.search(arr[ii]);
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
    writer.close();
    // bt.printTree();

    return 0;
}