/*
By Vivek Dhiman
1. Open the exisiting disambiguase_id file and read in all disambiguos edges in a map
2. Open the final id_id edges file
3. Go through each edge and check if any of the pageId is in the map
4. If yes then increment the count
5. else continue
4. Write total edges with atleast one disambig node
-------Example-------
Compile: $ g++ -O3 -o countDisamEdgeNodes countDisamEdgeNodes.cpp
Usage  : $ ./countDisamEdgeNodes filtered_Id_Id_EdgeList.csv disamb.csv
-----------
*/
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <utility>   // for pairs
#include <algorithm> // for swap
using namespace std;

int main (int argc, char const *argv[]){
    //************* make sure args are present:
    if (argc != 3){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << "<final Id ID filename> <disamb filename>" << endl;
        exit(1);
    } 
    //************* got the args
    clock_t begin = clock(); 
   
    map <long long, bool> disambPageids;
    ifstream disFile;
    disFile.open( argv[2] );
    if (!disFile) {
        cout << "ERROR: unable to open disFile file" << endl;
        exit(1); // terminate with error
    }
    long long ni, nj;
    while (disFile >> ni){
        disambPageids[ni] = true;
    }
    disFile.close(); disFile.clear();
    //************* start load edgelist
    ifstream inFile;
    inFile.open( argv[1] );
    if (!inFile) {
        cout << "ERROR: unable to open input file" << endl;
        exit(1); // terminate with error
    }
    long long totDis = 0;
    while (inFile >> ni >> nj){ // scan edgelist to populate 
        if(disambPageids[ni] || disambPageids[nj]) totDis++;
    }
    inFile.close(); inFile.clear();
    //------------- Let's write to the new file
    disambPageids.clear();
    //************* end load edgelist
    cout << "Total Disamb edges:" << totDis  << endl;
    cout << "Time taken = " << double(clock() - begin)/ CLOCKS_PER_SEC  << " seconds. "<< endl;
    return 0;
}

