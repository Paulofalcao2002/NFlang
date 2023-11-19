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

using SymbolValue = variant<int, string>;
using SymbolTableType = unordered_map<string, SymbolValue>;

class SymbolTable {
public:
    SymbolTable();

    void create(const string& symbol);
    SymbolValue get(const string& symbol);
    void set(const string& symbol, const SymbolValue& value);

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

// Node for a block of statements
class Block : public Node {
public:
    Block(variant<int, string> value, vector<unique_ptr<Node>> children);
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
