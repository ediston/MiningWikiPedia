# MiningWikiPedia
<h1>Goal: Mining Wikipedia to get useful results <h1>
<h5>[NOTE: As Simple wiki is a smaller wikipedia, I am going to use Simple Wiki. But I am guessing all the steps listed below can be applied to whole Wikipedia as well.]</h5>

<h2>How to get Simple Wikipedia(SW) data?</h2>
------------------------------------------------------------------------------------------
<h3>Step1:How to get Id title mapping for Wikipedia</h3>
Example: What is the page id for "August" page?
<p>
Step1.1: <a href="http://dumps.wikimedia.org/simplewiki/" target="_blank">Go to the page for latest dump.</a></br>
Step1.2: Download <b>Base per-page data (id, title, old restrictions, etc)</b> or simplewiki-date-page.sql.gz file</br>
Step1.3: Run: $ zcat simplewiki-date-page.sql.gz | python sqlDumpTo_ID_Title_Map.py > SWPageIDTitleMap.csv</br>
Step1.4: Clean the file. Wiki DB still have some page titles which no more exist. So remove such title. Run $ python checkWebPageExists.py SWPageIDTitleMap.csv</br>
sqlDumpTo_ID_Title_Map.py can be found in the src folder
</p>
------------------------------------------------------------------------------------------
<h3>Step2:How to get Links to create graph for Wikipdeia</h3>
Example: What are the the page ids linked on "August" page?
<p>
Step2.1: <a href="http://dumps.wikimedia.org/simplewiki/" target="_blank">Go to the page for latest dump.</a></br>
Step2.2: Download <b>page-to-page link records</b> or simplewiki-date-pagelinks.sql.gz  file</br>
Step2.3: Run: $ zcat simplewiki-date-pagelinks.sql.gz | python sqlDumpTo_ID_Title_Map.py > SW_ID_Title_Links.csv</br>
sqlDumpTo_ID_Title_Map.py can be found in the src folder
</p>
------------------------------------------------------------------------------------------
