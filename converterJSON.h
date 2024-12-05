#pragma once

#include <vector>
#include <string>
#include <exception>
#include "searchServer.h"

class noConfigFileException : public std::exception {
  public:
    const char* what() const noexcept override;
};

class emptyConfigFieldException : public std::exception {
  public:
    const char* what() const noexcept override;
};

class ConverterJSON {
  public:
    ConverterJSON();

    /**
    * The method to get the content of files
    * @return a list with content of files listed in config.json
    */
    std::vector<std::string> getTextDocuments();

    /**
    * The method to get the name of the search engine
    * @return a string with name field from config.json
    */
    std::string getName();

    /**
    * The method reads max_responses field from config.json
    * to set limits for the number of answers for one request
    * @return the maximum number of responses for one request
    */
    int getResponsesLimit();
    
    /**
    * The method of getting requests from requests.json file
    * @return the list of requests from requests.json file
    */
    std::vector<std::string> getRequests();

    /**
    * Put the results of searching requests to answers.json file
    */
    void putAnswers(std::vector<std::vector<RelativeIndex>>answers);
};