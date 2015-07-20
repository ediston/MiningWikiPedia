'''
# Created by Vivek Dhiman
# Script will get edges from  a file in the form "<pageFrom id> <pageTo title>""
# and create edge list of the form "<pageFrom id> <pageTo id>""
#
Run like this:
# $ python3.4 this_script.py args[1] args[2]
    OR
# $ python3.4 this_script.py <Id_Tile_Map_filename> <Id_title_EdgeList_filename>
#   args[1] is the <Id_Tile_Map_filename>
#   args[2] is the <Id_title_EdgeList_filename>

#---------------------------------------
  Steps taken by algo:
    1. Open <Id_Tile_Map_filename>
    2. Read all Id, title mapping
    3. 
    2. Create a new file and open filtered_Id_ID_EdgeList.csv
    2. Open the <filename> file
    3. For each line, 
        3.1 get the id and title
        3.2 check if title exisits
        3.3 if not then continue
        3.4 else write id id to the new file
    4. Close the exisiting filr
#--
''' 
import datetime
import math
import sys

def main(argv):
    args = list(argv)
    if len(args) < 3:
        print("Usage: python3.4 " + args[0]  + " <Id_Tile_Map_filename> <Id_title_EdgeList_filename>")
        exit(0)
    idTitleMapFileName = args[1]
    idTitleEdgeListFileName = args[2]
    newFileName = "filtered_Id_Id_EdgeList.csv"
    try:
        idTitleMapFi = open(idTitleMapFileName)
    except IOError,e:
        print("Error for " + idTitleMapFileName  + ", " +e.code)
        exit(0)  
    #------------------------------------------
    # --- go throught the file and create a map
    titleToIdMap = {}
    lines = idTitleMapFi.readlines()
    for line in lines:
        line = line.rstrip()
        row = line.split(' ')
        pageId = row[0]
        title = row[1]
        titleToIdMap[title] = pageId
    idTitleMapFi.close()     
    #------------------------------------------
    #  Make sure idTitleEdgeFile exists
    totalEdges = 0
    try:
        idTitleEdgeFi = open(idTitleEdgeListFileName)
    except IOError,e:
        print("Error for " + idTitleEdgeListFileName  + ", " +e.code)
        exit(0) 
    #-------- map
    adjList = {}
    # Create a new file
    newFile = open(newFileName, 'w')
    newFile.close()
    lines = idTitleEdgeFi.readlines()
    edgeId = 0
    for line in lines:
        line = line.rstrip()
        row = line.split(' ')
        fromPageId = row[0]
        ToPageTitle = row[1]
        # if the key doesn't exist or
        # if the value doesnt exist in the map
        # skip this edge
        if not titleToIdMap.has_key(ToPageTitle) or not (fromPageId in titleToIdMap.values()):
            continue
        ToPageId = titleToIdMap[ToPageTitle]
        if ToPageId == fromPageId:
            continue
        newFile = open(newFileName, 'a+')
        if int(fromPageId) > int(ToPageId) :
            newFile.write(ToPageId + " " + fromPageId + " " + str(edgeId) + "\n")
        else:
            newFile.write(fromPageId + " " + ToPageId + " " + str(edgeId) + "\n")
        newFile.close()
        edgeId = edgeId + 1
        totalEdges = totalEdges + 1
    #-- close the files
    idTitleEdgeFi.close()
    #-- do -------------
    print("totalPages = " + str(totalPages))
    return 

if __name__ == "__main__":
    main(sys.argv)


