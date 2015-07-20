# MiningWikiPedia
<h1>Goal: Mining Wikipedia to get useful results <h1>
<h5>[NOTE: As Simple wiki is a smaller wikipedia, I am going to use Simple Wiki. But I am guessing all the steps listed below can be applied to whole Wikipedia as well.]</h5>

<h2>How to get Simple Wikipedia(SW) data?</h2>
------------------------------------------------------------------------------------------
<h3>Step1: How to get Id title mapping for Wikipedia</h3>
Example: What is the page id for "August" page?
<p>
Step1.1: <a href="http://dumps.wikimedia.org/simplewiki/" target="_blank">Go to the page for latest dump.</a></br>
Step1.2: Download <b>Base per-page data (id, title, old restrictions, etc)</b> or simplewiki-date-page.sql.gz file</br>
Step1.3: Run: $ zcat simplewiki-date-page.sql.gz | python sqlDumpTo_ID_Title_Map.py > SWPageIDTitleMap.csv</br>
Step1.4: Clean the file. Wiki DB still have some page titles which no more exist. So remove such title. Run $ python checkWebPageExists.py SWPageIDTitleMap.csv</br>
sqlDumpTo_ID_Title_Map.py can be found in the src folder
</p>
------------------------------------------------------------------------------------------
<h3>Step2: How to get Links to create graph for Wikipdeia</h3>
Example: What are the the page ids linked on "August" page?
<p>
Step2.1: <a href="http://dumps.wikimedia.org/simplewiki/" target="_blank">Go to the page for latest dump.</a></br>
Step2.2: Download <b>page-to-page link records</b> or simplewiki-date-pagelinks.sql.gz  file</br>
Step2.3: Run: $ zcat simplewiki-date-pagelinks.sql.gz | python sqlDumpTo_ID_Title_Map.py > SW_ID_Title_Links.csv</br>
sqlDumpTo_ID_Title_Map.py can be found in the src folder
</p>
------------------------------------------------------------------------------------------
<h3>Step3: Pre Process Edge list</h3>
<p>
Step3.1: Let's firstly remove all page-ids from "SWPageIDTitleMap.csv" which are no more live.</br> 
&nbsp;&nbsp;&nbsp;&nbsp;*  Run: $ python checkWebPageExists.py SWPageIDTitleMap.csv </br> 
&nbsp;&nbsp;&nbsp;&nbsp;*  This will create a new file "filtered_SWPageIDTitleMap.csv".</br>
&nbsp;&nbsp;&nbsp;&nbsp;*  Note: This step might take a lot of time. For simple wiki it took almost 24 hours.</br>
Step3.2: Convert Id-title edge list to id id edge list.</br>
&nbsp;&nbsp;&nbsp;&nbsp;*  Run: $ python convert_idTitle_Edgelist_To_IdId.py filteredSWPageIDTitleMap.csv SW_ID_Title_Links.csv </br>
&nbsp;&nbsp;&nbsp;&nbsp;*  This will create an unsorted, filtered Edge List. But for most of the work we need a sorted edge list, done in next step</br>
&nbsp;&nbsp;&nbsp;&nbsp;*  Filtered here means that the page titles and page ids which are not there in "filtered_SWPageIDTitleMap.csv" will be removed </br>
Step3.3: Remove Duplicate and same node edges like "A  A"     </br>
&nbsp;&nbsp;&nbsp;&nbsp;Compile: $ g++ -O3 -o remDupAndSort removeDupAndSort.cpp</br>
&nbsp;&nbsp;&nbsp;&nbsp;Usage  : $ ./remDupAndSort filtered_Id_Id_EdgeList.csv finalSWEdgeList.csv</br>
</p>
</br>
------------------------------------------------------------------------------------------
<h4>Step 4: Get list of disambiguation</h4>
<p>Disambiguation pages will form the ground truth. All such pages should be definitely in different clusters.</p>
<p>
Step 4.1: <a href="http://dumps.wikimedia.org/simplewiki/" target="_blank">Go to the page for latest dump.</a></br>
Step 4.2: Download <b>Wiki category membership link records</b>simplewiki-date-categorylinks.sql.gz file</br>
Step 4.3: Run: $ zcat simplewiki-date-categorylinks.sql.gz | python sqlDumpTo_Disamb_Id.py > disamb.csv</br>
Step 4.4: Count total disambg edges in finalSWEdgeList.csv</br>
&nbsp;&nbsp;&nbsp;&nbsp;Compile: $ g++ -O3 -o countDisamEdgeNodes countDisamEdgeNodes.cpp</br>
&nbsp;&nbsp;&nbsp;&nbsp;Usage  : $ ./countDisamEdgeNodes filtered_Id_Id_EdgeList.csv disamb.csv</br>
------------------------------------------------------------------------------------------
<h1>Results, SW DB of <a href="http://dumps.wikimedia.org/simplewiki/20150603/" target="_blank">June, 2015</a> </h1>
<table>
 <tr>
  <td>Total Edges</td>
  <td>2699230</td>
 </tr>
 <tr>
  <td>Total Disamb edges</td>
  <td>19404</td>
 </tr>
</table> 
</p>


