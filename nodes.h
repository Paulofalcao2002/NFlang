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

SymbolType getSymbolTypeFromString(const string& type);

using SymbolTableType = unordered_map<string, pair<SymbolType, variant<int, string>>>;

class SymbolTable {
public:
    SymbolTable();

    void create(const string& symbol, SymbolType type);
    variant<int, string> get(const string& symbol);
    void set(const string& symbol, const variant<int, string> value);

private:
    SymbolTableType table;
};

// Base class for all nodes
class Node {
public:
    variant<int, string>  value; // Value can be None (you can use a sentinel value to represent None)
    std::vector<unique_ptr<Node>> children;

    virtual variant<int, string> evaluate(SymbolTable& symbolTable);
};

using FunctionValue = tuple<SymbolType, Node*>;

class FunctionTable {
private:
    static unordered_map<string, FunctionValue> table;

public:
    static void create(const string& name, SymbolType type, Node* nodePtr);
    static FunctionValue get(const string& name);
};

// Node for a function declaration
class FunctionDeclaration : public Node {
public:
    FunctionDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a function call
class FunctionCall : public Node {
public:
    FunctionCall(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a block of statements
class Block : public Node {
public:
    Block(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for drive loop
class Drive : public Node {
public:
    Drive(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for playuntil loop
class PlayUntil : public Node {
public:
    PlayUntil(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for when conditional operation
class WhenConditional : public Node {
public:
    WhenConditional(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a variable declaration operation
class VarDeclaration : public Node {
public:
    VarDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};


// Node for a assignment operation
class Assignment : public Node {
public:
    Assignment(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a call (print) operation
class Call : public Node {
public:
    Call(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for binary operations (e.g., +, -, *, /, logical AND, logical OR, etc.)
class BinOp : public Node {
public:
    BinOp(variant<int, string> value, vector<unique_ptr<Node>> children);
    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for unary operations (e.g., unary minus, logical NOT, etc.)
class UnOp : public Node {
public:
    UnOp(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value
class Signal : public Node {
public:
    Signal(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value
class Number : public Node {
public:
    Number(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a numeric value
class String : public Node {
public:
    String(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a identifier
class Identifier : public Node {
public:
    Identifier(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

// Node for a empty line
class NoOp : public Node {
public:
    NoOp(variant<int, string> value, vector<unique_ptr<Node>> children);

    variant<int, string> evaluate(SymbolTable& symbolTable) override;
};

#endif // NODES_H
