/*
By Vivek Dhiman
1. Open the exisiting Id id file
2. if ids on the edge are same then just ignore the edge
3. Else store in the set, set automatically takes care of duplicate edges
    and sorting
4. Write edges in set to a new file
-------Example-------
Compile: $ g++ -O3 -o remDupAndSort removeDupAndSort.cpp
Usage  : $ ./remDupAndSort filtered_Id_Id_EdgeList.csv finalSWEdgeList.csv
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
        cout << "usage:\n    " << argv[0] << "<Id ID filename> <new Id ID filename>" << endl;
        exit(1);
    } 
    //************* got the args
    clock_t begin = clock(); 
    
    //************* start load edgelist
    ifstream inFile;
    inFile.open( argv[1] );
    if (!inFile) {
        cout << "ERROR: unable to open input file" << endl;
        exit(1); // terminate with error
    }
    long long edgeId = 0;
    set< pair<long long, long long> > edges; // O(log n) access too slow? 
    set< pair<long long, long long> > :: iterator sit;
    long long ni, nj;
    while (inFile >> ni >> nj){ // scan edgelist to populate 
        if(ni==nj) continue;
        if (ni > nj) swap(ni,nj); // undirected!
        edges.insert(make_pair(ni,nj));
    }
    inFile.close(); inFile.clear();
    //------------- Let's write to the new file
    edgeId = 0;
    FILE * newIdIdFile  = fopen( argv[2], "w" );  
    for(sit = edges.begin(); sit!=edges.end(); sit++){
        ni = (*sit).first;
        nj = (*sit).second;
        fprintf(newIdIdFile, "%ld %ld %ld\n", ni, nj);
        edgeId++;
    }
    fclose(newIdIdFile);
    edges.clear();
    //************* end load edgelist
    cout << "Total Edges:" << edgeId  << endl;
    cout << "Time taken = " << double(clock() - begin)/ CLOCKS_PER_SEC  << " seconds. "<< endl;
    return 0;
}

