#include <iostream>
#include <fstream>
#include "converterJSON.h"
#include "nlohmann/json.hpp"

const char* noConfigFileException::what() const noexcept {
    return "Config file is missing";
}

const char* emptyConfigFieldException::what() const noexcept {
    return "Config file is empty";
}

ConverterJSON::ConverterJSON() {
    std::ifstream configFile("config.json");
    if (!configFile.is_open()) {
        throw noConfigFileException();
    } else {
        nlohmann::json configParameters;
        configFile >> configParameters;
        if(configParameters["config"].is_null()) {
            throw emptyConfigFieldException();
        }
    }
}

std::vector<std::string> ConverterJSON::getTextDocuments() {
    std::ifstream configFile("config.json");
    std::vector<std::string> resourceFilesContent;
    nlohmann::json configParameters;
    configFile >> configParameters;
    
    for (int i = 0; i < configParameters["files"].size(); i++) {
        std::string path = configParameters["files"][i];
        std::ifstream textFile(path);

        if(textFile.is_open()) {
            std::string currentFileContent;
            textFile.seekg (0, textFile.end);
            int length = textFile.tellg();
            textFile.seekg (0, textFile.beg);
            char * buffer = new char [length];
            textFile.read(buffer, length);
            currentFileContent.assign(buffer, length);
            delete[] buffer;

            for(int j = 0; j < currentFileContent.length(); j++) {
                if(!isalnum(currentFileContent[j]) && currentFileContent[j] != ' ') {
                    currentFileContent.erase(currentFileContent.begin() + j);
                }
                if (isupper(currentFileContent[j])) {
                    currentFileContent[j] = tolower(currentFileContent[j]);
                }
            }

            resourceFilesContent.push_back(currentFileContent);
            textFile.close();
        } else {
            std::cerr << "No resource files in config.json or incorrect path of resource files\n";
        }
    } 

    configFile.close();
    if (resourceFilesContent.empty()) {
        std::cerr << "No files in the directory specified in config.json->files\n";
    }
    return resourceFilesContent;
}

std::string ConverterJSON::getName() {
    std::ifstream configFile("config.json");
    nlohmann::json configParameters;
    configFile >> configParameters;
    configFile.close();
    return configParameters["config"]["name"];
}

int ConverterJSON::getResponsesLimit() {
    std::ifstream configFile("config.json");
    nlohmann::json configParameters;
    configFile >> configParameters;

    if(configParameters["config"]["max_responses"].is_null()) {
        configFile.close();
        return 5;
    }

    configFile.close();
    return configParameters["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests() {
    std::ifstream requestsFile("requests.json");
    std::vector<std::string> requestsList;

    if (requestsFile.is_open()) {
        nlohmann::json requests;
        requestsFile >> requests;

        for (int i = 0; i < requests["requests"].size(); i++) {
            requestsList.push_back(requests["requests"][i]);
        }

    }
    requestsFile.close();
    if (requestsList.empty()) {
        std::cerr << "No requests specified in requests.json->requests\n";
    }
    return requestsList;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>>answers) {
    std::ofstream answersFile("answers.json");
    if (answersFile.is_open()) {
        nlohmann::ordered_json answersDict;

        for (int i = 0; i < answers.size(); i++) {

            if (answers[i].empty()) {
                answersDict["answers"]["request" + std::to_string(i + 1)]["result"] = false;
            } else {
                answersDict["answers"]["request" + std::to_string(i + 1)]["result"] = true;
                
                for (int j = 0; j < answers[i].size(); j++) {
                    if (answers[i].size() == 1) {
                        answersDict["answers"]["request" + std::to_string(i + 1)][std::to_string(answers[i][j].doc_id)] = answers[i][j].rank;
                    } else {
                        answersDict["answers"]["request" + std::to_string(i + 1)]["relevance"][std::to_string(answers[i][j].doc_id)] = answers[i][j].rank;
                    }
                }
            }
        }

        answersFile << std::setw(4) << answersDict;
    } else {
        std::cerr << "File answers.json could not be created";
    }
}