Run analyseClusters.cpp
# Analyse Wikipedia
<h1>Goal: Analyse Wikipedia to get some results <h1>
 

<h3>Step 1: Make a list of bad links </h3>
A list of sample bad links is <a href="https://github.com/ediston/MiningWikiPedia/blob/master/data/BadLinks.csv" >here</a>

<h3>Step 2: Convert [page_title page_title] to [page_id page_id] list file </h3>
Example run: $ ./listCsvToIdCsv filteredSWPageIDTitleMap.csv badEdgeList.csv badEdgeListIdId.csv </br>
This example is for Simple Wiki. There are 72 bad links in badEdgeListIdId.csv

<h4>Step 3: Check if all links exist<h4>

 
