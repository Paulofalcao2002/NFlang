#ifndef NODES_H
#define NODES_H

#include <vector>
#include <memory>
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

// Base class for all nodes
class Node {
public:
    int value; // Value can be None (you can use a sentinel value to represent None)
    std::vector<unique_ptr<Node>> children;

    virtual int evaluate();
};

// Node for binary operations (e.g., +, -, *, /, logical AND, logical OR, etc.)
class BinOp : public Node {
public:
    BinOp(int value, vector<unique_ptr<Node>> children);
    int evaluate() override;
};

// Node for unary operations (e.g., unary minus, logical NOT, etc.)
class UnOp : public Node {
public:
    UnOp(int value, vector<unique_ptr<Node>> children);

    int evaluate() override;
};

// Node for a numeric value
class Number : public Node {
public:
    Number(int value, vector<unique_ptr<Node>> children);

    int evaluate() override;
};

#endif // NODES_H
