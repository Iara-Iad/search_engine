#pragma once

#include <vector>
#include <string>
#include "invertedIndex.h"

struct RelativeIndex {
    int doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const { //needed to pass tests
      return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
    InvertedIndex index;
    int limitAnswers;
  public:

/**
* @param idx the reference on InvertedIndex classs, which is transfered to class constructor 
* to make SearchServer know the frequency of words in request
*/
SearchServer(InvertedIndex& idx, int& limAnswers);
/**
* The method of search query processing
* @param queriesInput the search requests taken from requests.json file
* @return the sorted list of relevant answers for requests
*/
std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queriesInput);
};