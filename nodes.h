#ifndef NODES_H
#define NODES_H

#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <unordered_map>
using namespace std;

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

enum class UnOperation {
    PLUS,
    MINUS,
    NOT,
    INCREMENT
};

enum class SymbolType { 
    ATHLETE, 
    PLAY,
    NUMBER,
    DOWN,
    EMPTY 
};

using NodeValue = variant<int, string, unordered_map<string, variant<int, string>>>;

SymbolType getSymbolTypeFromString(const string& type);
string getSymbolTypeName(SymbolType symbolType);
string incrementDown(const string& down);
int getDownOrder(const string& down);

using SymbolTableType = unordered_map<string, pair<SymbolType, NodeValue>>;

class SymbolTable {
public:
    SymbolTable();

    void create(const string& symbol, SymbolType type);
    pair<SymbolType, NodeValue> get(const string& symbol);
    void set(const string& symbol, const NodeValue value);

private:
    SymbolTableType table;
};

// Base class for all nodes
class Node {
public:
    NodeValue  value; // Value can be None (you can use a sentinel value to represent None)
    vector<unique_ptr<Node>> children;
    bool isReturnNode;

    virtual pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable);
};

using FunctionValue = tuple<SymbolType, Node*>;

class FunctionTable {
private:
    static unordered_map<string, FunctionValue> table;

public:
    static void create(const string& name, SymbolType type, Node* nodePtr);
    static FunctionValue get(const string& name);
};

// Node for the return of a function
class Play : public Node {
public:
    Play(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for the return of a function
class Result : public Node {
public:
    Result(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a function declaration
class FunctionDeclaration : public Node {
public:
    FunctionDeclaration(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a function call
class FunctionCall : public Node {
public:
    FunctionCall(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a block of statements
class Block : public Node {
public:
    Block(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for drive loop
class Drive : public Node {
public:
    Drive(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for playuntil loop
class PlayUntil : public Node {
public:
    PlayUntil(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for when conditional operation
class WhenConditional : public Node {
public:
    WhenConditional(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a variable declaration operation
class VarDeclaration : public Node {
public:
    VarDeclaration(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};


// Node for a assignment operation
class Assignment : public Node {
public:
    Assignment(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a call (print) operation
class Call : public Node {
public:
    Call(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for binary operations (e.g., +, -, *, /, logical AND, logical OR, etc.)
class BinOp : public Node {
public:
    BinOp(NodeValue value, vector<unique_ptr<Node>> children);
    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for unary operations (e.g., unary minus, logical NOT, etc.)
class UnOp : public Node {
public:
    UnOp(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value
class Signal : public Node {
public:
    Signal(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value
class Number : public Node {
public:
    Number(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a string value
class String : public Node {
public:
    String(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

// Node for a down value
class Down : public Node {
public:
    Down(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};


// Node for a identifier
class Identifier : public Node {
public:
    Identifier(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue>evaluate(SymbolTable& symbolTable) override;
};

// Node for a empty line
class NoOp : public Node {
public:
    NoOp(NodeValue value, vector<unique_ptr<Node>> children);

    pair<SymbolType, NodeValue> evaluate(SymbolTable& symbolTable) override;
};

#endif // NODES_H
