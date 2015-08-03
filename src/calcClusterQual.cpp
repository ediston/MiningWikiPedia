/*
By Vivek Dhiman

- Scirpt will be used to calculate the quality of the clusters.
- For a given page of list_of_items (e.g. List_of_colors) and pages on the the list page (e.g. Red, Blue, White)
- Let's say there are n links on the list page
- then how good the clustering is w.r.t to this page is 
- total pairs found in the same cluster / total possile cluster
- for example if we are looking for colors: red, white, yellow, green, blue. 
- n = 5
- total possible pairs are nC2 = 10
- and let's say we have three clusters
- red, white, x, a ,b c
- yellow, green, blue, l, m, n, o, z
- blue, red
- so we have these pairs with both elements in same cluster:
-- red, white; red, blue; yellow,green; blue,green; yellow,blue;
- so total found pairs  = 5
- so quality is 5/10 = 0.5
- For l different lists, quality is 
- Quality of Clusters = Sum of (Quality of each list)/(total number of lists)

*/
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <utility>   // for pairs
#include <algorithm> // for swap
#define LIST 0
#define DISAMB 1
using namespace std;



int main (int argc, char const *argv[]){
    //************* make sure args are present:
    if (argc != 5){
        cout << "ERROR: something wrong with the inputs" << endl;
        cout << "usage:\n    " << argv[0] << "<List_FileName <clusters_filename> <outputfile> <mode>" << endl;
        exit(1);
    } 
    int mode = atoi(argv[4]);
    if(mode!=LIST  && mode!=DISAMB){
    	cout << "ERROR: something wrong with the mode" << endl;
        cout << "usage:\n    " << argv[0] << "<List_FileName <clusters_filename> <outputfile> 0 or 1" << endl;
        exit(1);
    }
    clock_t begin = clock();
    ifstream listFile;
    listFile.open( argv[1] );
    if (!listFile) {
        cout << "ERROR: unable to open listFile" << endl;
        exit(1); // terminate with error
    }
    map< int, set<pair <int,int> > > pairsFound;
    map<int, set<pair <int,int> > > :: iterator pairsFoundIt;
    map< int, int> listSize;
    map< int, int> pageToListPageMap;
    long long ni, nj;
    // List has to be store like this
    // <list page id> <page id on the list page>
    while (listFile >> ni >> nj){ // scan edgelist to populate 
        if(ni==nj) continue;
        pageToListPageMap[nj] = ni;
        listSize[ni]++;
    }
    listFile.close(); listFile.clear();
    cout << "total lists :" << listSize.size() << endl ;
    //----
    string line;
    ifstream clusterFile;
    clusterFile.open( argv[2] );
    int num  = 0;
    set<int> :: iterator it1, it2;
    int listPageId, pageId1, pageId2;
    while(getline(clusterFile, line)){
    	map<int, set<int> > pageFound;
    	map<int, set<int> > :: iterator pFIt;
    	num = 0;
    	for(int i=0; i<line.length(); i++){
    		if(line[i] < '0' || line[i] >'9'){
    			if(pageToListPageMap.count(num)){
    				pageFound[pageToListPageMap[num]].insert(num);
    			}
    			num = 0;
    		}else{	
    			num = num*10 + (line[i] - '0');
    		}
    	}
    	if(num>0){
    		if(pageToListPageMap.count(num)){
    			pageFound[pageToListPageMap[num]].insert(num);
    		}
    	}
    	for(pFIt = pageFound.begin(); pFIt != pageFound.end(); pFIt++){
    		listPageId = (*pFIt).first;
    		for(it1 = ((*pFIt).second).begin(); it1!=((*pFIt).second).end(); it1++){
    			for(it2 = it1; it2!=((*pFIt).second).end(); it2++){
    				pageId1 = *it1;
    				pageId2 = *it2;
    				if(pageId1==pageId2) continue;
    				if(pageId1>pageId2) swap(pageId1, pageId2);
    				pairsFound[listPageId].insert(make_pair(pageId1, pageId2));
    			}
    		}
    	}
    	pageFound.clear();
    }
    float totalQual = 0, qual;
    float nLists = 0;
    float totPossPairs;
    FILE * resultFile = fopen( argv[3], "w" );
    for(pairsFoundIt = pairsFound.begin(); pairsFoundIt != pairsFound.end(); pairsFoundIt++){
    	listPageId = (*pairsFoundIt).first;
    	totPossPairs = (listSize[listPageId]*(listSize[listPageId]-1))/2;
    	qual = ((float) pairsFound[listPageId].size())/totPossPairs;
    	if(mode == LIST){
    		fprintf( resultFile, "For list %d, \tquality = %.6f \n", listPageId, qual);
		}else{
    		fprintf( resultFile, "For list %d, \tquality = %.6f \n", listPageId, 1-qual);
		}
    	//cout << "For list" << listPageId << ", quality: " << qual << endl;
    	totalQual += qual;
    }
	nLists = listSize.size();
    totalQual = totalQual/nLists;
    if(mode == LIST){
    	cout << "Over all quality of clusters for the given lists : " << totalQual*100 << "%%" << endl;
    	fprintf( resultFile, "Over all quality of clusters for the given %d lists is %.6f .\n", 
    				(int)nLists, totalQual*100);
	}else{
		cout << "Over all quality of clusters for the given lists : " << (1-totalQual)*100 << "%%" << endl;
    	fprintf( resultFile, "Over all quality of clusters for the given %d lists is %.6f .\n", 
    		(int)nLists, (1-totalQual)*100);
	}
    fprintf( resultFile, "Time taken = %f seconds. \n", 
    			double(clock() - begin)/ CLOCKS_PER_SEC  );
    cout << "Time taken = " << double(clock() - begin)/ CLOCKS_PER_SEC  << " seconds. "<< endl  ;
    fclose(resultFile);
    pairsFound.clear();
   
    return 0;
}






