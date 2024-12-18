#pragma once

#include <vector>
#include <string>
#include <map>

struct Entry {
    size_t doc_id;
    size_t count;
    bool operator ==(const Entry& other) const { // is needed to pass tests
      return (doc_id == other.doc_id &&
      count == other.count);
    }
};

class InvertedIndex {
    std::vector<std::string> docs; // the list of docucuments content
    std::map<std::string, std::vector<Entry>> freqDictionary; // frequency map
    friend void updateWithOneDoc(std::string doc, int docIndex, InvertedIndex* ptr);

  public:
    InvertedIndex() = default;

    /**
    * Update or fill the document base, in which a search will be made
    * @param inputDocs the documents content
    */
    void updateDocumentBase(std::vector<std::string> inputDocs);

    /** 
    * This method determines the number of occurrences of the word 
    * in the loaded database of documents
    * @param word the word, which number of occurences is needed to be count
    * @return the prepared list of word frequency
    */
    std::vector<Entry> getWordCount(const std::string& word);
};
