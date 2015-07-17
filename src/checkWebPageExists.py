'''
# Created by Vivek Dhiman
# Script will remove bad wiki pages from the <id page mapping> file
# while creating a filtered_<id page mapping> file
#---------------------------------------
# Run like this:
# $ python3.4 this_script.py args[1]
    OR
# $ python3.4 this_script.py <filename>
#   args[1] is the filename
#---------------------------------------
    Steps taken by algo:
    1. Create and open filtered_<filename>
    2. Open the <filename> file
    3. For each line, 
        3.1 get the id and title
        3.2 check if title exisits
        3.3 if not then continue
        3.4 else write id title to the new file
    4. Close the exisiting filr
#--
'''
import urllib2
import datetime
import math
import sys
def getCompleteURL(pageTitle):
    return 'https://simple.wikipedia.org/wiki/' + pageTitle

def checkIfWebPageExisits(url):
    try:
        urllib2.urlopen(url)
        return True
    except urllib2.HTTPError, e:
        #print(e.code)
        return False
    except urllib2.URLError, e:
        return False
    return False

def main(argv):
    args = list(argv)
    inFileName = args[1]
    newFileName = "filtered"+ inFileName
    try:
        fi = open(inFileName)
    except IOError,e:
        print(e.code)
        exit(0)
    totalPages = 0
    newFile = open(newFileName, 'w')
    lines = fi.readlines()
    for line in lines:
        line = line.rstrip()
        row = line.split(' ')
        id = row[0]
        title = row[1]
        url = getCompleteURL(title)
        if checkIfWebPageExisits(url) == False:
            print(title)
            continue
        totalPages = totalPages + 1 
        newFile.write(id + " " + title + "\n")
    newFile.close()
    fi.close()
    print("totalPages = " + str(totalPages))
    return 
    
if __name__ == "__main__":
    main(sys.argv)

