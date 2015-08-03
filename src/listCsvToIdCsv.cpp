/*Script to check what links
 * exist on a given page Id
 * */
#include <cstdlib>
#include <fstream>
#include<iostream>
#include<map>
using namespace std;

int main(int argc, char const *argv[]){
     if (argc != 4){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << " <Id_Page_Map> <EdgeListFileName>" << endl;
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
    FILE * newIdIdFile  = fopen( argv[3], "w" );  
    string p1Title, p2Title;
    long n1, n2;
    while(edgeListFile >> p1Title >>  p2Title){
        n1 =  pTitleIdMap[p1Title];
        n2 =  pTitleIdMap[p2Title];
        fprintf(newIdIdFile, "%ld %ld\n", n1, n2);
    }
    fclose(newIdIdFile);
    edgeListFile.close(); edgeListFile.clear();
    pTitleIdMap.clear();
    return 0;
}
