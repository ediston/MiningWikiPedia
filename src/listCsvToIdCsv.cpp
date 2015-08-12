 /*Script to convert <title title> file to <id id> file
  * **/
#include <cstdlib>
#include <fstream>
#include<iostream>
#include<map>
using namespace std;

int main(int argc, char const *argv[]){
     if (argc != 5){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << " <Id_Page_Map> <Id Id edge list> <bad EdgeListFileName> <new file>" << endl;
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

    map<pair<long long, long long>, bool> exists;
    ifstream badEdgeListFile;
    badEdgeListFile.open( argv[3] );
    if (!badEdgeListFile) {
        cout << "ERROR: unable to open edgeListFile file" << endl;
        exit(1); // terminate with error
    }
    string p1Title, p2Title;
    long n1, n2;
    while(badEdgeListFile >> p1Title >>  p2Title){
        if(pTitleIdMap.count(p1Title) == 0 ) {cout << p1Title << " not found" << endl; continue; }
        if(pTitleIdMap.count(p2Title) == 0 ) {cout << p2Title << " not found" << endl; continue; }
        n1 =  pTitleIdMap[p1Title];
        n2 =  pTitleIdMap[p2Title];
        if(n1>n2) swap(n1, n2);
        exists[make_pair(n1, n2)] = false;
    }
    badEdgeListFile.close(); badEdgeListFile.clear();
    pTitleIdMap.clear();
    cout << "Done with converting from titles to ids " << endl; 
    FILE * newIdIdFile  = fopen( argv[4], "w" );
    ifstream edgeListFile;
    edgeListFile.open( argv[2] );
    while(edgeListFile >> n1 >> n2){
        if(exists.count(make_pair(n1, n2))){
            fprintf(newIdIdFile, "%ld %ld\n", n1, n2);
            cout << exists.size() << " links remaining" << endl;
            exists.erase(make_pair(n1, n2));
            if(exists.size() == 0) break;
        }
    }
    edgeListFile.close(); edgeListFile.clear();
    fclose(newIdIdFile);

    return 0;
}
