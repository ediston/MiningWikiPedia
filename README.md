# MiningWikiPedia
Goal: Mining Wikipedia to get useful results
------------------------------------------------------------------------------------------
<h5>[NOTE: As Simple wiki is a smaller wikipedia, I am going to use Simple Wiki. But I am guessing all the steps listed below can be applied to whole Wikipedia as well.]</h5>
------------------------------------------------------------------------------------------
<h2>Step1: How to get Simple Wikipedia(SW) data?</h2>
<h3>How to get Id titile mapping for Wikipedia</h3>
What is the page id for "August" page?

Step1.1: [Go to the page for latest dump](http://dumps.wikimedia.org/simplewiki/).</br>
Step1.2: Download Base per-page data (id, title, old restrictions, etc) or simplewiki-date-page.sql.gz file</br>
Step1.3: Run: $ zcat simplewiki-date-page.sql.gz | python sqlDumpTo_ID_Title_Map.py > SWPageIDTitleMap.csv

sqlDumpTo_ID_Title_Map.py can be found in the src folder
------------------------------------------------------------------------------------------
