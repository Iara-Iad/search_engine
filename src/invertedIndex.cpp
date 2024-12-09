#include <thread>
#include <sstream>
#include <mutex>
#include <iostream>
#include "invertedIndex.h"

std::mutex dictAccess;

void updateWithOneDoc(std::string doc, int docIndex, InvertedIndex* ptr) {
    std::stringstream ss(doc);
    std::string word;

    while (!ss.eof()) {
        ss >> word;
        bool indexPresent = false;

        dictAccess.lock();
        if(ptr->freqDictionary.count(word) > 0) {
            for (int i = 0; i < ptr->freqDictionary[word].size(); i++) {
                if (ptr->freqDictionary[word][i].doc_id == docIndex) {
                    ptr->freqDictionary[word][i].count += 1;
                    dictAccess.unlock();
                    indexPresent = true;
                    break;
                }
            }
        }
        dictAccess.unlock();

        if (!indexPresent) {
            Entry entry;
            entry.count = 1;
            entry.doc_id = docIndex;
            dictAccess.lock();
            ptr->freqDictionary[word].push_back(entry);
            dictAccess.unlock();
        }
    }
}

void InvertedIndex:: updateDocumentBase(std::vector<std::string> inputDocs) {   
    std::vector<std::thread> threads;
    for (int i = 0; i < inputDocs.size(); i++) {
        threads.emplace_back(updateWithOneDoc, inputDocs[i], i, this);
    }

    for (int i = 0; i < inputDocs.size(); i++) {
        threads[i].join();
    }
}

std::vector<Entry> InvertedIndex:: getWordCount(const std::string& word) {
    for (std::map<std::string, std::vector<Entry>>::iterator it = freqDictionary.begin(); it != freqDictionary.end(); it++){
        if (it->first == word){
            return it->second;
        }
    }
    return {};
}