<h1 align="center">Local Search Engine</h1>

## Description

This search engine is a console application that performs searches and can be customized via JSON files. The search is performed on local files. 

## Description of the technology stack used

Visual Studio Code editor, MinGW 11.0.0 compiler and CMake 3.30.3 builder were used to create the project. The project is written in C++. JSON for Modern C++ library is used to work with JSON files. Google Test library is used for unit tests

## Short instruction

To search local files, it is necessary to specify file paths in the config.json file in the files field. Each document should contain no more than 1000 words with a maximum length of 100 characters each. The maximum number of responses per question can be set in the max_responses field, otherwise it will be set to 5. 

The questions themselves should be written in the requests.json file in the requests field. As the resource files are converted to lower case, the requests are also to be in lower case.
 
The list of relevant documents will be presented in the answers.json file in descending order of relevance. If there are no relevant documents for a query, the answer will be false.

If there is no config.json file or no config field, the search will not start.