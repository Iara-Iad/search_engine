#include <iostream>
#include "invertedIndex.h"
#include "searchServer.h"
#include "converterJSON.h"

int main() {
    try {
        ConverterJSON converter;
        std::cout << converter.getName() << std::endl;
        int limAnswers = converter.getResponsesLimit();
        InvertedIndex idx;
        idx.updateDocumentBase(converter.getTextDocuments());
        SearchServer searcher(idx, limAnswers);
        converter.putAnswers(searcher.search(converter.getRequests()));
        return 0;
    }
    catch(const noConfigFileException& exp1) {
        std::cerr << "Exception: " << exp1.what();
    }
    catch(const emptyConfigFieldException& exp2) {
        std::cerr << "Exception: " << exp2.what();
    }
}