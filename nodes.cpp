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

void FunctionTable::create(const string& name, SymbolType type, Node* nodePtr) {
    if (table.find(name) != table.end()) {
        throw runtime_error("Function already declared");
    }

    table[name] = make_tuple(type, nodePtr);
}

FunctionValue FunctionTable::get(const string& name) {
    auto it = table.find(name);
    if (it == table.end()) {
        throw runtime_error("Function not in table");
    }

    return it->second;
}

unordered_map<string, FunctionValue> FunctionTable::table;

Result::Result(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = true;
}

variant<int, string> Result::evaluate(SymbolTable& symbolTable) {
    return children[0]->evaluate(symbolTable); 
}

FunctionDeclaration::FunctionDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> FunctionDeclaration::evaluate(SymbolTable& symbolTable) {
    variant<int, string> functionName = children[0]->children[0]->value;

    if (holds_alternative<int>(functionName)) {
        throw invalid_argument("Semantic: function identifier in declaration must be a string");
    }

    variant<int, string> functionType = children[0]->value;

    if (holds_alternative<int>(functionType)) {
        throw invalid_argument("Semantic: function type in declaration must be a string");
    }

    FunctionTable::create(get<string>(functionName), getSymbolTypeFromString(get<string>(functionType)), this);

    return 0; 
}

FunctionCall::FunctionCall(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> FunctionCall::evaluate(SymbolTable& symbolTable) {
    if (holds_alternative<int>(this->value)) {
        throw invalid_argument("Semantic: function identifier in call must be a string");
    }

    // Retrieve function declaration
    FunctionValue functionDeclaration = FunctionTable::get(get<string>(this->value));

    // Create symbol table for function
    SymbolTable* functionSymbolTable = new SymbolTable();

    int i = 0;
    Node* functionDeclarationNode = get<Node*>(functionDeclaration);

    if (functionDeclarationNode->children.size() - 2 != children.size()) {
        throw invalid_argument("Semantic: function being called with invalid number or arguments");
    }

    for (auto& child: children) {
        functionDeclarationNode->children[i + 1]->evaluate(*functionSymbolTable);
        variant<int, string> argument = child->evaluate(symbolTable);

        if (holds_alternative<int>(functionDeclarationNode->children[i + 1]->children[0]->value)) {
            throw invalid_argument("Semantic: argument name must be an identifier string");
        }

        functionSymbolTable->set(
            get<string>(functionDeclarationNode->children[i + 1]->children[0]->value),
            argument
        );

        i++;
    }

    variant<int, string> result = functionDeclarationNode->children[i + 1]->evaluate(*functionSymbolTable);

    // TODO: Return type checking

    return result; 
}

Block::Block(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> Block::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate each of the childs
    for (const auto& child : children) {
        variant<int, string> result = child->evaluate(symbolTable);
        if (child->isReturnNode) {
            this->isReturnNode = true;
            return result;
        }
    }

    return 0; 
}

Drive::Drive(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> Drive::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluates the variable declaration and assignment
    children[0]->evaluate(symbolTable);


    variant<int, string> identifier = children[0]->children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: drive identifier must be a string");
    }

    // Gets loop variable value
    variant<int, string> driveVar = symbolTable.get(get<string>(identifier));

    // Temporary
    if (holds_alternative<string>(driveVar)) {
        throw invalid_argument("Semantic: drive loop value must be a number");
    }

    // Gets limit value
    variant<int, string> limitValue = children[1]->evaluate(symbolTable);

    // Temporary
    if (holds_alternative<string>(limitValue)) {
        throw invalid_argument("Semantic: drive loop value must be a number");
    }

    variant<int, string> result = 0;

    while (get<int>(driveVar) <= get<int>(limitValue)) {
        // Evaluates loop block
        result = children[2]->evaluate(symbolTable);

        if (children[2]->isReturnNode) {
            this->isReturnNode = true; 
            return result;
        }

        // Increments loops variable
        symbolTable.set(get<string>(identifier), get<int>(driveVar) + 1);

        // Gets loop variable value
        driveVar = symbolTable.get(get<string>(identifier));

        // Temporary
        if (holds_alternative<string>(driveVar)) {
            throw invalid_argument("Semantic: drive loop value must be a number");
        }
    }

    return result; 
}

PlayUntil::PlayUntil(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> PlayUntil::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    variant<int, string> condition = children[0]->evaluate(symbolTable);
    
    if (holds_alternative<string>(condition)) {
        throw invalid_argument("Semantic: playuntil condition must be a boolean");
    }

    variant<int, string> result = 0;

    // While stop condition isn't met
    while (!get<int>(condition)) {
        // Execute block
        result = children[1]->evaluate(symbolTable);

        if (children[1]->isReturnNode) {
            this->isReturnNode = true;
            return result;
        }

        // Reevaluate condition
        condition = children[0]->evaluate(symbolTable);

        if (holds_alternative<string>(condition)) {
            throw invalid_argument("Semantic: playuntil condition must be a boolean");
        }
    }

    return result; 
}

WhenConditional::WhenConditional(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> WhenConditional::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    variant<int, string> condition = children[0]->evaluate(symbolTable);

    if (holds_alternative<string>(condition)) {
        throw invalid_argument("Semantic: when condition must be a boolean");
    }

    // Variable to store the result of the conditional block
    variant<int, string> result = 0;

    // if condition execute if block, else is executed when condition isn´t met and 
    // else block exists
    if (get<int>(condition)) {
        result = children[1]->evaluate(symbolTable);

        // If the conditional block is a return block, 
        // then the when block becomes a return block as well
        if (children[1]->isReturnNode) {
            this->isReturnNode = true;
        }
    } else if (children.size() > 2) {
        result = children[2]->evaluate(symbolTable);

        // If the conditional block is a return block, 
        // then the otherwise block becomes a return block as well
        if (children[2]->isReturnNode) {
            this->isReturnNode = true;
        }
    }

    return result; 
}

VarDeclaration::VarDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
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
    this->isReturnNode = false;
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
    this->isReturnNode = false;
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
    this->isReturnNode = false;
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
    this->isReturnNode = false;
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
    this->isReturnNode = false;
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
    this->isReturnNode = false;
}

variant<int, string> Number::evaluate(SymbolTable& symbolTable) {
    // Returns the numeric value
    return this->value;
}

String::String(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

variant<int, string> String::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return this->value;
}

Identifier::Identifier(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
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
    this->isReturnNode = false;
}

variant<int, string> NoOp::evaluate(SymbolTable& symbolTable) {
    // Returns 0
    return this->value;
}