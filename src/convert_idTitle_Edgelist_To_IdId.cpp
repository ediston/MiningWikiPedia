/*
# Created by Vivek Dhiman
# Script will get edges from  a file in the form "<pageFrom id> <pageTo title>""
# and create edge list of the form "<pageFrom id> <pageTo id>""
#
Compile: g++ -O3 -o convert_idTitle_Edgelist_To_IdId convert_idTitle_Edgelist_To_IdId.cpp
Run like this:
# $ ./convert_idTitle_Edgelist_To_IdId <Id_Tile_Map_filename> <Id_title_EdgeList_filename>
#   args[1] is the <Id_Tile_Map_filename>
#   args[2] is the <Id_title_EdgeList_filename>
#---------------------------------------
  Steps taken by algo:
    1. Open <Id_Tile_Map_filename> 
    2. Read all Id, title mapping into idTitleMap
        and read title,id mapping into titleIdMap
    3. Create a new file and open filtered_Id_ID_EdgeList.csv
    4. Open the <Id_title_EdgeList_filename> file
    5. For each line, 
        .1 get the id and title
        .2 check if title exisits, and check if id exists
        .3 if not then continue
        .4 else write newest id and for both id and titles.
    6. Close the exisiting file

We should use the newest id for all future 

#--
*/
#include<iostream>
#include<map>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<set>
using namespace std;

int main (int argc, char const *argv[]){
   if (argc != 3){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << "<Id_Tile_Map_filename> <Id_title_EdgeList_filename> " << endl;
        exit(1);
    } 
    clock_t begin = clock();
    map <string, long long> titleIdMap;
    map <long long, string> idTitleMap;
    ifstream inFile;
    inFile.open( argv[1] );
    if (!inFile) {
        cout << "ERROR: unable to open input file" << endl;
        exit(1); // terminate with error
    } 
    long long id; string s;
    while (inFile >> id >> s){ // scan edgelist to populate  
        titleIdMap[s]  = id;
        idTitleMap[id] = s;
    }
    inFile.close(); inFile.clear();
    ifstream edgeListFile;
    edgeListFile.open( argv[2] );
    if(!edgeListFile){
        cout << "ERROR: unable to open Id_title_EdgeList_filename file"<< argv[2] << endl;
        exit(1); // terminate with error
    }        
    long totalLines = 7959934;
    long long n1 , n2;
    FILE * nwEdgeListFile = fopen( "filtered_Id_Id_EdgeList.csv", "w" );
    while(edgeListFile >> id >> s){
        totalLines--;
        if(totalLines%1000 == 0) cout << "Remaining:" << totalLines << endl;
        if(titleIdMap.count(s) == 0 || idTitleMap.count(id) == 0) continue;
        n1 = titleIdMap[idTitleMap[id]];
        n2 = titleIdMap[s];
        if(n1==n2) continue;
        if(n1>n2) swap(n1, n2);
        fprintf( nwEdgeListFile, "%ld %ld \n", n1, n2);
    } 
    edgeListFile.close(); edgeListFile.clear();
    fclose(nwEdgeListFile);
    cout << "Time taken = " << double(clock() - begin)/ CLOCKS_PER_SEC  << " seconds. "<< endl  ;
    return 0;
}
