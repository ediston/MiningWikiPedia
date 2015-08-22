# MiningWikiPedia
<h1>Goal: Mining Wikipedia to get useful results <h1>
<h2>1. Parse Wiki DB</h2> 
<p>Read parsingWikiDB.md</p>
------------------------------------------------------------------------------------------
<h2>2. Run Link Clustering</h2>

<h3>Step 1: Create the Jaccard Co-efficients </h3>

<p>Example: ./linkedList finalSWEdgeList.csv finalSWEdgeList.jacc <br>
Above example uses linkedlist implementation
</p>
<table>
<tr><td>
Time taken by linked link implementation, undirected</td><td> 8743.57 seconds
</td></tr>
<tr><td>
Time taken by linked link implementation, directed</td><td> 1171.27 seconds
</td></tr>
<tr><td>
Time taken by author's implementation, undirected</td><td> 21914.4 seconds
</td></tr>
<tr><td>
finalSWEdgeList.jacc file size  </td><td> 61G
</td></tr>
<tr><td>
Directed finalDirSWEL.jaccs file size  </td><td> 24G
</td></tr>
</table> 
<h3>Step 2: Create edge id map <h3>
<h6>[Observation1: File size can be dramatically decreased if we can use id's for edges, then we have three numbers <b>[edgeid1] [edgeid2] [jacc]</b> ]<h6>
<h6>[Observation2: File size can be dramatically decreased if we can store output in a single line]<h6>
<p>
This will reduce the size of the jaccs file
</p>
<h6>Why?</h6>
<p>
1. We have smaller run-time memory.</br>
2. Also smaller storage is required</br></br>
</p>
<h6>How?</h6>
<p>
Steps:</br>
1. Go through the .jaccs file</br>
2. Read in a new line, edge edge jacc</br>
3. For a new edge, increment the index and store mapping in a map</br>
4. For an exisiting edge, use the stored mapped index</br>
5. Replace line by id id jacc</br>
</p>
</p>
<p>
./createEdgesToEdgeIDJaccsFile network.pairs network.jaccs networkEdgeIdMap.csv newnetwork.jaccs
</p> 
<p>
<table>
<tr>
 <th>RESULTS, undirected</th>
  
</tr>
<tr><td>
Time taken to create new file:</td><td> 4476.1 seconds
</td></tr> 
<tr><td>
New finalSWEdgeList.jacc file size  </td><td> 42G
</td></tr>
<tr><td>
File size reduced by  </td><td> 31.14%
</td></tr>
<tr>
 <td>
 Total edge edge pairs in jacc file
 </td>
 <td>
  1,828,446,173
 </td>
</tr>
</table>
</p>
<p>
<table>
<tr>
 <th>RESULTS, Directed </th>
  
</tr>
<tr><td>
Time taken to create new file:</td><td> 1229.9 seconds
</td></tr> 
<tr><td>
New newfinalDirSWEL.jaccs file size  </td><td> 17G
</td></tr>
<tr><td>
File size reduced by  </td><td> 29.1%
</td></tr>
<tr>
 <td>
 Total edge edge pairs in jacc file
 </td>
 <td>
    693,943,606
 </td>
</tr>
</table>
</p>
----------------------------------
<h3>Step 3: Sort various thresholds</h3>
<p></br>
Compile:$ g++ -O3 -o createSortedJaccsFile createdSortedJaccsFile.cpp </br>
Run:  $ ./createSortedJaccsFile newnetwork.jaccs sortedjaccs.csv</br>
Run:  $ /home/vdhiman/linkClusteringRepo/Link-Clustering-Algorithm/Step3/createSortedJaccsFile newfinalSWEdgeListbkup.jacc finalSortedSWEdgeList.jacc sortedjaccs.csv > runtimeSortedjaccs </br>
Done writing sorted New NW JaccsFile! Time taken = 1590.54 seconds. 
Total Time taken = 5283.32 seconds. 
 
</p>
<table>
<tr>
 <th>RESULTS</th>
 <th></th>
</tr>
<tr>
 <td>
  Unique jaccs
 </td>
 <td>
 217712
 </td>
</tr> 
<tr>
 <td>
  Min. jacc  
 </td>
 <td> 
 0.000057
 </td>
</tr>
<tr>
 <td>
  Max. jacc  
 </td>
 <td>  
 1.000000
 </td>
 </tr>
 <tr>
  <td>
   Time taken
  </td>
  <td>
   1315.53 seconds ≈ 22 Minutes 
  </td>
 </tr>
</table>
</p>
----------------------------------
<h3>Step 4: Run clustering</h3>
<p>
Example:  $ g++ -std=c++0x -O3 -o calcDensityForDiffThresh calcDensityForDiffThresh.cpp </br>
          $ ./calcDensityForDiffThresh networkEdgeIdMap.csv network.jaccs sortedjaccs.csv  Nthresholds threshDensity.csv MODE</br>
</br>
Example: $ /home/vdhiman/linkClusteringRepo/Link-Clustering-Algorithm/Step3/calcDensityForDiffThresh networkEdgeIdMap.csv finalSortedSWEdgeList.jacc sortedjaccs.csv 500 threshDensity500.csv > runtimeDensityForDiffThresh500 &

<table>
<tr>
 <th>RESULTS</th>
 <th></th>
</tr>
<tr>
 <td>
  highest D 
 </td>
 <td>
 0.380500 at thresh = 0.476230
 </td> 
 </tr>
</table>
</p>

<img src="https://cloud.githubusercontent.com/assets/4389099/8891292/ecd117c4-3323-11e5-957c-6d89742a7a99.png"
 alt="SimpleWiki D vs Threshold" style="width:304px;height:228px;">  

----------------------------------
