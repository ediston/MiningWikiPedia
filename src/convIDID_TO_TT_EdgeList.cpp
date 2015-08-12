 /*Script to convert <id id> file to <title title> file
  * **/
#include <cstdlib>
#include <fstream>
#include<iostream>
#include<map>
using namespace std;

int main(int argc, char const *argv[]){
     if (argc != 4){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << " <Id_Page_Map> <id_id edgelistfile> <new title_title egeListFileName>" << endl;
        exit(1); 
     }
    string pTitle;
    int pID;
    map <int, string> pTitleIdMap;
    ifstream inFile;
    inFile.open( argv[1] );
    if (!inFile) {
       cout << "ERROR: unable to open input file" << endl;
        exit(1); // terminate with error
    }
    while(inFile >> pID >> pTitle){
        pTitleIdMap[pID]  = pTitle;
    }
    inFile.close(); inFile.clear();
    cout << "Map reading done" << endl;
    string pageName;

    ifstream edgeListFile;
    edgeListFile.open( argv[2] );
    if (!edgeListFile) {
        cout << "ERROR: unable to open edgeListFile file" << endl;
        exit(1); // terminate with error
    }
    string p1Title, p2Title;
    long n1, n2;
    FILE * newIdIdFile  = fopen( argv[3], "w" );
    while(edgeListFile >> n1 >>  n2){
        if(pTitleIdMap.count(n1) == 0 ) {cout << n1 << " not found" << endl; continue; }
        if(pTitleIdMap.count(n2) == 0 ) {cout << n2 << " not found" << endl; continue; }
        p1Title = pTitleIdMap[n1];
        p2Title = pTitleIdMap[n2];
        fprintf(newIdIdFile, "%s %s\n", p1Title.c_str(), p2Title.c_str());
    }
    pTitleIdMap.clear();
    edgeListFile.close(); edgeListFile.clear();
    fclose(newIdIdFile);

    return 0;
}
