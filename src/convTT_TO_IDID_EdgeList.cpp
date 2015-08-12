 /*Script to convert <title title> file to <id id> file
  * **/
#include <cstdlib>
#include <fstream>
#include<iostream>
#include<map>
using namespace std;

int main(int argc, char const *argv[]){
     if (argc != 4){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << " <Id_Page_Map> <title _ tile egeListFileName> <new id_id edgelistfile>" << endl;
        exit(1); 
     }
    string pTitle;
    int pID;
    map <string, int> pTitleIdMap;
    ifstream inFile;
    inFile.open( argv[1] );
    if (!inFile) {
       cout << "ERROR: unable to open input file" << endl;
        exit(1); // terminate with error
    }
    while(inFile >> pID >> pTitle){
        pTitleIdMap[pTitle] = pID;
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
    while(edgeListFile >> p1Title >>  p2Title){
        if(pTitleIdMap.count(p1Title) == 0 ) {cout << p1Title << " not found" << endl; continue; }
        if(pTitleIdMap.count(p2Title) == 0 ) {cout << p2Title << " not found" << endl; continue; }
        n1 =  pTitleIdMap[p1Title];
        n2 =  pTitleIdMap[p2Title];
        if(n1>n2) swap(n1, n2);
        fprintf(newIdIdFile, "%ld %ld\n", n1, n2);
    }
    pTitleIdMap.clear();
    edgeListFile.close(); edgeListFile.clear();
    fclose(newIdIdFile);

    return 0;
}
