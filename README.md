# MiningWikiPedia
<h1>Goal: Mining Wikipedia to get useful results <h1>
<h2>1. Parse Wiki DB</h2> 
<p>Read parsingWikiDB.md</p>
<h2>2. Run Link Clustering</h2>
<p>Read runLinkCluster.md</p>

<h2>3. Making sense of data</h2>

<h3>Step 1: Create the Jaccard Co-efficients </h3>

<p>Example: ./linkedList finalSWEdgeList.csv finalSWEdgeList.jacc <br>
Above example uses linkedlist implementation
</p>
<table>
<tr><td>
Time taken by my implementation</td><td> 8743.57 seconds
</td></tr>
<tr><td>
Time taken by author's implementation</td><td> 21914.4 seconds
</td></tr>
<tr><td>
finalSWEdgeList.jacc file size  </td><td> 61G
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
