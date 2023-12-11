#ifndef PREPRO_H
#define PREPRO_H

#include <string>
using namespace std;

// Class responsible for the pre processing part of the compiler
// Receives inputFileName (const &string) at init
// Method: string preprocess() returns the processed file to Lexical analyses
class PrePro {
public:
    PrePro(const string& inputFileName);
    string preprocess();
private:
    string inputFileName;
};

#endif
