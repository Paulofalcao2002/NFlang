#include "prePro.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

PrePro::PrePro(const string& inputFileName) : inputFileName(inputFileName) {}

string PrePro::preprocess() {
    // Open input file
    ifstream inputFile(inputFileName);
    // Return empty string on file opening error
    if (!inputFile.is_open()) {
        return ""; 
    }

    // Process lines
    string preprocessedCode;
    string line;
    while (getline(inputFile, line)) {
        size_t commentPos = line.find('#');
        if (commentPos != string::npos) {
            // Remove comment portion
            line = line.substr(0, commentPos); 
        }

        // Add filtered lines
        preprocessedCode += line + '\n';
    }

    inputFile.close();

    // If the preprocessed code doesn't end with a newline, add one
    if (!preprocessedCode.empty() && preprocessedCode.back() != '\n') {
        preprocessedCode += '\n';
    }

    return preprocessedCode;
}
