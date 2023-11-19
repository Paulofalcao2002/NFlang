#include "nodes.h"
#include <iostream>
#include <limits> 
#include <variant>
#include <string>
#include <stdexcept>
#include <unordered_map>
using namespace std;

SymbolType getSymbolTypeFromString(const string& type) {
    if (type == "athlete") {
        return SymbolType::ATHLETE;
    }
    if (type == "play") {
        return SymbolType::PLAY;
    }
    if (type == "number") {
        return SymbolType::NUMBER;
    }
    if (type == "down") {
        return SymbolType::DOWN;
    }
    return SymbolType::EMPTY;
}

SymbolTable::SymbolTable() {}

void SymbolTable::create(const string& symbol, SymbolType type) {
    if (table.find(symbol) != table.end()) {
        throw runtime_error("Symbol already declared");
    }

    if (type == SymbolType::ATHLETE) {
        table[symbol] = make_pair(type, "");
    } else if (type == SymbolType::PLAY) {
        table[symbol] = make_pair(type, "");
    } else if (type == SymbolType::NUMBER) {
        table[symbol] = make_pair(type, 0);
    } else if (type == SymbolType::DOWN) {
        table[symbol] = make_pair(type, "firstdown");
    } else {
        table[symbol] = make_pair(type, 0);
    }
}

variant<int, string> SymbolTable::get(const string& symbol) {
    auto it = table.find(symbol);
    if (it == table.end()) {
        throw runtime_error("Symbol not in table");
    }

    return it->second.second;
}

void SymbolTable::set(const string& symbol, const variant<int, string> value) {
    auto it = table.find(symbol);
    if (it == table.end()) {
        throw runtime_error("Symbol not in the table");
    }

    SymbolType symbolType = it->second.first;

    if (symbolType == SymbolType::ATHLETE && !holds_alternative<string>(value)) {
        throw runtime_error("Type mismatch for athlete type variable");
    }

    // TODO
    // if (type == SymbolType::PLAY && !holds_alternative<string>(value)) {
    //     throw runtime_error("Type mismatch for athlete type variable");
    // }

    if (symbolType == SymbolType::NUMBER && !holds_alternative<int>(value)) {
        throw runtime_error("Type mismatch for number type variable");
    }

    if (symbolType == SymbolType::DOWN && holds_alternative<string>(value)) {
        const string* strPtr = get_if<string>(&value);
        string strValue = *strPtr;
        if (strValue != "firstdown" && strValue != "seconddown" &&
            strValue != "thirddown" && strValue != "fourthdown") {
            throw runtime_error("Type mismatch for DOWN type variable");
        }
    } else if (symbolType == SymbolType::DOWN && holds_alternative<int>(value)) {
        throw runtime_error("Type mismatch for DOWN type variable");
    }

    it->second.second = value;
}

variant<int, string> Node::evaluate(SymbolTable& symbolTable) {
    return 0;
}

Block::Block(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Block::evaluate(SymbolTable& symbolTable) {
    // Evaluate each of the childs
    for (const auto& child : children) {
        child->evaluate(symbolTable);
    }

    return 0; 
}

WhenConditional::WhenConditional(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> WhenConditional::evaluate(SymbolTable& symbolTable) {
    // Evaluate condition
    variant<int, string> condition = children[0]->evaluate(symbolTable);

    if (holds_alternative<string>(condition)) {
        throw invalid_argument("Semantic: when condition must be a boolean");
    }

    // if condition execute if block, else is executed when condition isn´t met and 
    // else block exists
    if (get<int>(condition)) {
        children[1]->evaluate(symbolTable);
    } else if (children.size() > 2) {
        children[2]->evaluate(symbolTable);
    }

    return 0; 
}

VarDeclaration::VarDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> VarDeclaration::evaluate(SymbolTable& symbolTable) {
    // Variable declaration, defines the type of the variable and can assign a value
    variant<int, string> identifier = children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    symbolTable.create(get<string>(identifier), getSymbolTypeFromString(get<string>(this->value)));

    if (children.size() == 1) {
        return 0;
    }

    variant<int, string> value = children[1]->evaluate(symbolTable);

    symbolTable.set(get<string>(identifier), value);

    return 0;
}

Assignment::Assignment(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Assignment::evaluate(SymbolTable& symbolTable) {
    // Assign the value of the expression to a variable in the symbol table
    variant<int, string> identifier = children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    variant<int, string> value = children[1]->evaluate(symbolTable);

    symbolTable.set(get<string>(identifier), value);

    return 0;
}

Call::Call(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Call::evaluate(SymbolTable& symbolTable) {
    // Prints in the std out the value of the expression
    variant<int, string> child = children[0]->evaluate(symbolTable);

    if (holds_alternative<string>(child)) {
        cout << get<string>(child) << endl;
    } else {
        cout << get<int>(child) << endl;
    }

    return 0;
}


BinOp::BinOp(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> BinOp::evaluate(SymbolTable& symbolTable) {
    int result = 0; // Initialize result, change based on your logic

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    variant<int, string> left_child = children[0]->evaluate(symbolTable);
    variant<int, string> right_child = children[1]->evaluate(symbolTable);

    switch (get<int>(this->value)) {
        case (int) BinOperation::PLUS:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform + operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform + operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) + get<int>(right_child);
            break;
        
        case (int) BinOperation::MINUS:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform - operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform - operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) - get<int>(right_child);
            break;

        case (int) BinOperation::TIMES:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform * operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform * operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) * get<int>(right_child);
            break;

        case (int) BinOperation::DIVIDE:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform / operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform / operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) / get<int>(right_child);
            break;

        case (int) BinOperation::EQUALS:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform equals operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform equals operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) == get<int>(right_child) ? 1 : 0;
            break;

        case (int) BinOperation::GREATER_THAN:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform > operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform > operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) > get<int>(right_child) ? 1 : 0;
            break;

        case (int) BinOperation::LESSER_THAN:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform < operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform < operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) < get<int>(right_child) ? 1 : 0;
            break;

        case (int) BinOperation::AND:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform and operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform and operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) && get<int>(right_child) ? 1 : 0;
            break;

        case (int) BinOperation::OR:
            if (holds_alternative<string>(left_child)) {
                throw invalid_argument("Semantic: Cannot perform or operation in string: " + get<string>(left_child));
            }
            if (holds_alternative<string>(right_child)) {
                throw invalid_argument("Semantic: Cannot perform or operation in string: " + get<string>(right_child));
            }

            result = get<int>(left_child) || get<int>(right_child) ? 1 : 0;
            break;

        default:
            break;
    }

    return result;
}

UnOp::UnOp(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> UnOp::evaluate(SymbolTable& symbolTable) {
    int result = 0; // Initialize result, change based on your logic

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    variant<int, string> child = children[0]->evaluate(symbolTable);

    switch (get<int>(this->value)) {
        case (int) UnOperation::PLUS:
            if (holds_alternative<string>(child)) {
                throw invalid_argument("Semantic: Cannot perform + unary operation in string: " + get<string>(child));
            }
            result = get<int>(child);
            break;
        
        case (int) UnOperation::MINUS:
            if (holds_alternative<string>(child)) {
                throw invalid_argument("Semantic: Cannot perform - unary operation in string: " + get<string>(child));
            }
            result = -get<int>(child);
            break;

        case (int) UnOperation::NOT:
            if (holds_alternative<string>(child)) {
                throw invalid_argument("Semantic: Cannot perform not unary operation in string: " + get<string>(child));
            }
            result = !get<int>(child);
            break;

        case (int) UnOperation::INCREMENT:
            if (holds_alternative<string>(child)) {
                throw invalid_argument("Semantic: Cannot perform >> unary operation in string: " + get<string>(child));
            }
            result = get<int>(child) + 1;
            break;

        default:
            break;
    }

    return result;
}

Signal::Signal(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Signal::evaluate(SymbolTable& symbolTable) {
    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Returns the numeric value
    int input;
    cin >> input;
    return input;
}

Number::Number(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Number::evaluate(SymbolTable& symbolTable) {
    // Returns the numeric value
    return this->value;
}

String::String(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> String::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return this->value;
}

Identifier::Identifier(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> Identifier::evaluate(SymbolTable& symbolTable) {
    // Returns the identifier value in the symbolTable
    if (holds_alternative<int>(this->value)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    return symbolTable.get(get<string>(this->value));
}

NoOp::NoOp(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
}

variant<int, string> NoOp::evaluate(SymbolTable& symbolTable) {
    // Returns 0
    return this->value;
}