#include <iostream>
#include <fstream>
#include <string>
#include "prePro.h"
#include "nodes.h"
using namespace std;

// Bison parser functions/variables
extern int yyparse();
extern FILE* yyin;
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern int yylex_destroy();

// astRoot global variable initialization
Node* astRoot = nullptr;

int main(int argc, char *argv[]) {
    // Error if file name not specified
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_filename>" << endl;
        return 1;
    }

    // Get the input file name from command-line arguments
    string inputFileName = argv[1];

    // Get processed field
    PrePro preprocessor(inputFileName);
    string preprocessedCode = preprocessor.preprocess();

    // Error if processed file is empty
    if (preprocessedCode.empty()) {
        cout << "Unable to open file " << inputFileName << endl;
        return 1;
    }

    // Initialize Bison's parser with preprocessed code as a string buffer
    yy_scan_string(preprocessedCode.c_str());

    // Call Bison's parser function and retrieve the AST root
    Node* root = nullptr;
    if (yyparse() == 0) {
        // Retrieve the AST root from the global variable set during parsing
        root = astRoot;
    } else {
        // Parsing failed, handle error
        cerr << "Parsing failed!" << endl;
        return 1;
    }

    // Clean up 
    yylex_destroy();

    // Evaluate AST root
    if (root) {
        // Create root level symbolTable
        SymbolTable* symbolTable = new SymbolTable();
        root->evaluate(*symbolTable); 
    }

    return 0;
}
