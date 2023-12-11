// Header file for the Nodes for the AST (Abstract syntax tree)
// Also define helper classes and functions used in the semantic phase of the compiler

#ifndef NODES_H
#define NODES_H

#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <unordered_map>
using namespace std;

// All types of Binary Operations that can be performed
enum class BinOperation {
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    EQUALS,
    GREATER_THAN,
    LESSER_THAN,
    AND,
    OR
};

// All types of Unary Operations that can be performed
enum class UnOperation {
    PLUS,
    MINUS,
    NOT,
    INCREMENT
};

// All types in NFLang
enum class SymbolType { 
    ATHLETE, 
    PLAY,
    NUMBER,
    DOWN,
    EMPTY 
};

// Types of values that can be returned from a node
// (Int) represents types NUMBER and EMPTY in NFLang
// (String) represents types ATHLETE and DOWN
// (Map) represents type PLAY
using NodeValue = variant<int, string, unordered_map<string, variant<int, string>>>;

// Helper functions designed to translate SymbolType
SymbolType getSymbolTypeFromString(const string& type);
string getSymbolTypeName(SymbolType symbolType);

// Helper functions designed to translate type DOWN
string incrementDown(const string& down);
int getDownOrder(const string& down);

// Type that defines SymbolTable map
using SymbolTableType = unordered_map<string, pair<SymbolType, NodeValue>>;

// Class used to store variables in NFLang
// Each scope level (function and root) has a symbol table
class SymbolTable {
public:
    SymbolTable();

    // create symbol in a table given a symbolName and type (related to VarDec node). 
    // Raises error if symbol is already created
    void create(const string& symbol, SymbolType type);

    // get the value of a symbol in a table. Raises error if symbol is not created
    pair<SymbolType, NodeValue> get(const string& symbol);

    // sets the value of a symbol in a table. Raises error if symbol is not created
    void set(const string& symbol, const NodeValue value);

private:
    SymbolTableType table;
};

// Base class for all nodes
// All nodes must have three properties: value, children and isReturnNode
// All nodes must have evaluate method
class Node {
public:
    NodeValue  value;
    vector<unique_ptr<Node>> children;
    bool isReturnNode;

    virtual pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable);
};

// Type of values stored in FunctionTable
using FunctionValue = tuple<SymbolType, Node*>;

// Class used to store functions defined in NFLang.
// The scope of this table is always root level
class FunctionTable {
private:
    static unordered_map<string, FunctionValue> table;

public:
    // create a new function in the table. Raises error if function is already created
    static void create(const string& name, SymbolType type, Node* nodePtr);

    // get function from table. Raises error if function is not created
    static FunctionValue get(const string& name);
};

// Node for the PLAY dictionary.
// This node contains 0 to n childs, that represents the assignment of a position to a value,
// in the Play. The evaluate method returns the play represented as a unordered map.
class Play : public Node {
public:
    Play(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for the return of a function.
// This node contains 1 child, that is the expression to the right of the result keyword.
// Return the evaluate of this child. Should always have isReturnNode as true.
class Result : public Node {
public:
    Result(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a function declaration.
// This node contains 2 to 2 + n childs, being n the number of arguments in the function.
// The first child is a VarDec of the function (function name and type).
// Each argument child is also a VarDec of the argument (argument name and type).
// The last child is the function block. The evaluate method of this class creates the 
// function in FunctionTable
class FunctionDeclaration : public Node {
public:
    FunctionDeclaration(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a function call.
// This class has 0 to n childs, being n the number of arguments passed in the call.
// Each child is a generic Node, resulting from the general expression in the syntax analysis.
// The evaluate method of this class retrieves the function from FunctionTable, declare each  n argument of 
// the function as the result of the evaluate method of child n. Then executes the function block
class FunctionCall : public Node {
public:
    FunctionCall(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a block of statements.
// This class has 0 to n child, being n the number of statements inside the block.
// The evaluate method of the class consists of the evaluate of each child. If a child is a 
// return node, the block becomes a return node as well and don't evaluate any of the subsequent childs
class Block : public Node {
public:
    Block(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for drive loop.
// This class has 3 childs. The first child is the declaration with assignment of the value in 
// the drive loop. The second child is generic node, result of the boolean expression of the limit value of the
// loop. The last child is the block of the loop. 
// The execution of the drive loop, execute the block child while loop variable <= limit value. At each iteration,
// the loop variable is incremented by one.
// When the block is a return node, the drive loop becomes a return node.
class Drive : public Node {
public:
    Drive(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for playuntil loop.
// This class has 2 childs. The first child is a generic Node of the condition of the loop.
// The second child is the block of the loop. The evaluate method executes the block until 
// the condition of the first child is met.
// When the block is a return node the playuntil becomes a return node.
class PlayUntil : public Node {
public:
    PlayUntil(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for when conditional operation.
// This class has 2 to 3 childs. The first child represents the when conditional, the
// second child represents the then block, the third child represents the otherwise block.
// The evaluate method gets the value of the boolean expression and execute the corresponding block.
// When the executed block is a returnNode WhenConditional becomes a return node.
class WhenConditional : public Node {
public:
    WhenConditional(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a variable declaration operation.
// This class has 1 to 2 children. The first child is the identifier of the variable being declared, the
// second child is the expression being assigned to the variable.
// The evaluate method of this class creates the variable in its symbol table and (optional)
// assign its value.
class VarDeclaration : public Node {
public:
    VarDeclaration(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};


// Node for a assignment operation.
// This class has 2 to 3 children. The first child is the identifier of the variable, the middle child (optional)
// is the position of the play being assigned, the last child is the assignment value.
// The evaluate method of this class sets the new value to the variable into is symbol table.
class Assignment : public Node {
public:
    Assignment(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a call (print) operation.
// This class has 1 child, that is the expression being printed. The evaluate of this class, prints into
// the stdout the value of the expression. Plays have a special treatment here, so they can be printed nicely.
class Call : public Node {
public:
    Call(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for binary operations (e.g., +, -, *, /, logical AND, logical OR, etc.).
// This class has 2 children, the left and right expression of the binOp. The evaluate of this class
// performs the binOp operation, raising error if the operation is invalid.
class BinOp : public Node {
public:
    BinOp(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for unary operations (e.g., unary minus, logical NOT, etc.).
// This class has 1 child, the expression of the unOp. The evaluate of this class
// performs the unOp operation, raising error if the operation is invalid.
class UnOp : public Node {
public:
    UnOp(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a signal.
// This class has no children. The evaluate of the class calls a cin operation, 
// retrieving a value in the stdin. This value must be numeric.
class Signal : public Node {
public:
    Signal(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value.
// This class has no children. The evaluate of the class returns the number stored in the 
// value property.
class Number : public Node {
public:
    Number(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a string value.
// This class has no children. The evaluate of the class returns the string stored in the 
// value property.
class String : public Node {
public:
    String(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a down value.
// This class has no children. The evaluate of the class returns the down stored in the 
// value property.
class Down : public Node {
public:
    Down(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};


// Node for a identifier.
// This class has no children. The evaluate of the class returns the value stored in the 
// symbol table for the identifier it represents.
class Identifier : public Node {
public:
    Identifier(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue>evaluate(SymbolTable& symbolTable) override;
};

// Node for a empty line.
// This class has no children. The evaluate of the class returns the 0.
class NoOp : public Node {
public:
    NoOp(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

#endif // NODES_H
