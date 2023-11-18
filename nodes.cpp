#include "nodes.h"
#include <iostream>

int Node::evaluate() {
    return 0;
}

BinOp::BinOp(int value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

int BinOp::evaluate() {
    int result = 0; // Initialize result, change based on your logic

    switch (this->value) {
        case (int) BinOperation::PLUS:
            // Handle PLUS operation
            // Example: Evaluate the sum of the two children nodes
            result = children[0]->evaluate() + children[1]->evaluate();
            break;
        
        case (int) BinOperation::MINUS:
            // Handle MINUS operation
            // Example: Evaluate the subtraction of the two children nodes
            result = children[0]->evaluate() - children[1]->evaluate();
            break;

        case (int) BinOperation::TIMES:
            // Handle TIMES operation
            // Example: Evaluate the multiplication of the two children nodes
            result = children[0]->evaluate() * children[1]->evaluate();
            break;

        case (int) BinOperation::DIVIDE:
            // Handle DIVIDE operation
            // Example: Evaluate the division of the two children nodes
            result = children[0]->evaluate() / children[1]->evaluate();
            break;

        case (int) BinOperation::EQUALS:
            // Handle EQUALS operation
            // Example: Evaluate if the values of the children nodes are equal
            result = children[0]->evaluate() == children[1]->evaluate() ? 1 : 0;
            break;

        case (int) BinOperation::GREATER_THAN:
            // Handle GREATER_THAN operation
            // Example: Evaluate if the value of the first child node is greater than the second child node
            result = children[0]->evaluate() > children[1]->evaluate() ? 1 : 0;
            break;

        case (int) BinOperation::LESSER_THAN:
            // Handle LESSER_THAN operation
            // Example: Evaluate if the value of the first child node is lesser than the second child node
            result = children[0]->evaluate() < children[1]->evaluate() ? 1 : 0;
            break;

        case (int) BinOperation::AND:
            // Handle AND operation
            // Example: Evaluate the logical AND of the two children nodes
            result = children[0]->evaluate() && children[1]->evaluate() ? 1 : 0;
            break;

        case (int) BinOperation::OR:
            // Handle OR operation
            // Example: Evaluate the logical OR of the two children nodes
            result = children[0]->evaluate() || children[1]->evaluate() ? 1 : 0;
            break;

        default:
            // Handle default case if needed
            break;
    }

    return result;
}

UnOp::UnOp(int value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

int UnOp::evaluate() {
    int result = 0; // Initialize result, change based on your logic

    switch (this->value) {
        case (int) UnOperation::PLUS:
            // Handle PLUS operation
            // Example: Evaluate the value of the single child node
            result = children[0]->evaluate();
            break;
        
        case (int) UnOperation::MINUS:
            // Handle MINUS operation
            // Example: Evaluate the negation of the value of the single child node
            result = -children[0]->evaluate();
            break;

        case (int) UnOperation::NOT:
            // Handle NOT operation
            // Example: Evaluate the logical NOT of the value of the single child node
            result = !(children[0]->evaluate());
            break;

        case (int) UnOperation::INCREMENT:
            // Handle INCREMENT operation
            // Example: Evaluate the value of the single child node incremented by 1
            result = children[0]->evaluate() + 1;
            break;

        default:
            // Handle default case if needed
            break;
    }

    return result;
}

Number::Number(int value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

int Number::evaluate() {
    // Returns the numeric value
    return this->value;
}
