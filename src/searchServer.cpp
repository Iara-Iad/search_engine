#include <vector>
#include <sstream>
#include <iostream>
#include "searchServer.h"
#include "invertedIndex.h"

int partition(std::vector<RelativeIndex>& vec, int start, int supElem) {
	int i = start;
	while(i < supElem) {
		if(vec[i].rank < vec[supElem].rank && i == supElem-1) {
			std::swap(vec[i], vec[supElem]);
			supElem--;
		}
		else if(vec[i].rank < vec[supElem].rank)
		{
			std::swap(vec[supElem - 1], vec[supElem]);
			std::swap(vec[i], vec[supElem]);
			supElem--;
		}
		
		else i++;
	}
	return supElem;
}

void quickSort(std::vector<RelativeIndex>& vec, int start, int end) {
	if(start < end)	{
		int supElem = partition(vec, start, end);
		
		quickSort(vec, start, supElem - 1);
		quickSort(vec, supElem + 1, end);
	}
}

SearchServer::SearchServer(InvertedIndex& idx, int& limAnswers) : index(idx), limitAnswers(limAnswers) {}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput) {
    std::vector<std::vector<RelativeIndex>> result;    

    for (int i = 0; i < queriesInput.size(); i++) {
        std::map<std::string, int> uniqueWords;
        std::multimap<int, std::string> listOfSortedWords;
        std::vector<RelativeIndex> relativeIndexVec;
        std::stringstream ss(queriesInput[i]);
        std::string currentWord;
        while (!ss.eof()) { 
            ss >> currentWord;
            uniqueWords[currentWord] = 1; // creates the list of unique words
        }

        for (auto& word : uniqueWords) {
            std::vector<Entry> wordCount = index.getWordCount(word.first);
            if (wordCount.empty()) { // if no such word in all documents than not count its frequency
                continue;
            }
            int count = 0;
            for (auto& entry : wordCount) {
                count += entry.count;
            }
            listOfSortedWords.emplace(count, word.first); // words in their frequency order
        }

        if (!listOfSortedWords.empty()) {        
            std::map<int, int> relevantDocIds;
            int maxAbsRelevance = 0;
            for(auto& word : listOfSortedWords) {
                std::vector<Entry> wordCount = index.getWordCount(word.second);
                for(auto entry : wordCount) {  
                    relevantDocIds[entry.doc_id] += entry.count; // fills the docIds map with all relevant docs and counts words from request in this docs
                    if (relevantDocIds[entry.doc_id] > maxAbsRelevance) {
                        maxAbsRelevance = relevantDocIds[entry.doc_id]; 
                    }
                }
            }

            for (auto& doc : relevantDocIds) {
                RelativeIndex newPair;
                newPair.doc_id = doc.first;
                newPair.rank = (float)doc.second / maxAbsRelevance;
                relativeIndexVec.push_back(newPair); // creates an unsorted RelativeIndex vector with filled docIds and their relevance
            }

            quickSort(relativeIndexVec, 0, relativeIndexVec.size() - 1);
        }

        if (relativeIndexVec.size() > limitAnswers) {
            relativeIndexVec.resize(limitAnswers);
        }
        result.push_back(relativeIndexVec);
    }  

    return result;
}
