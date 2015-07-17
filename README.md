# MiningWikiPedia
<h1>Goal: Mining Wikipedia to get useful results <h1>
<h5>[NOTE: As Simple wiki is a smaller wikipedia, I am going to use Simple Wiki. But I am guessing all the steps listed below can be applied to whole Wikipedia as well.]</h5>

<h2>How to get Simple Wikipedia(SW) data?</h2>
------------------------------------------------------------------------------------------
<h3>Step1:How to get Id title mapping for Wikipedia</h3>
What is the page id for "August" page?
<p>
Step1.1: <a href="http://dumps.wikimedia.org/simplewiki/">Go to the page for latest dump.</a></br>
Step1.2: Download Base per-page data (id, title, old restrictions, etc) or simplewiki-date-page.sql.gz file</br>
Step1.3: Run: $ zcat simplewiki-date-page.sql.gz | python sqlDumpTo_ID_Title_Map.py > SWPageIDTitleMap.csv
sqlDumpTo_ID_Title_Map.py can be found in the src folder
</p>
------------------------------------------------------------------------------------------
