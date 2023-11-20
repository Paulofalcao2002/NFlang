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

string getSymbolTypeName(SymbolType symbolType) {
    switch(symbolType) {
        case SymbolType::ATHLETE:
            return "athlete";
        case SymbolType::PLAY:
            return "play";
        case SymbolType::NUMBER:
            return "number";
        case SymbolType::DOWN:
            return "down";
        default:
            return "empty";
    }
}

string incrementDown(const string& down) {
    if (down == "firstdown") {
        return "seconddown";
    }
    if (down == "seconddown") {
        return "thirddown";
    }
    if (down == "thirddown") {
        return "fourthdown";
    }
    if (down == "fourthdown") {
        return "toondowns";
    }
    if (down == "toondowns") {
        runtime_error("No downs left to increment");
    }

    throw runtime_error("Invalid down value " + down);
}

int getDownOrder(const string& down) {
    if (down == "firstdown") {
        return 1;
    }
    if (down == "seconddown") {
        return 2;
    }
    if (down == "thirddown") {
        return 3;
    }
    if (down == "fourthdown") {
        return 4;
    }
    if (down == "toondowns") {
        return 5;
    }

    throw runtime_error("Invalid down value");
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

pair<SymbolType, variant<int, string>> SymbolTable::get(const string& symbol) {
    auto it = table.find(symbol);
    if (it == table.end()) {
        throw runtime_error("Symbol not in table");
    }

    return it->second;
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
            strValue != "thirddown" && strValue != "fourthdown" && 
            strValue != "toondowns") {
            throw runtime_error("Type mismatch for DOWN type variable");
        }
    } else if (symbolType == SymbolType::DOWN) {
        throw runtime_error("Type mismatch for DOWN type variable");
    }

    it->second.second = value;
}

pair<SymbolType, variant<int, string>> Node::evaluate(SymbolTable& symbolTable) {
    return make_pair(SymbolType::EMPTY, 0);
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

pair<SymbolType, variant<int, string>> Result::evaluate(SymbolTable& symbolTable) {
    return children[0]->evaluate(symbolTable); 
}

FunctionDeclaration::FunctionDeclaration(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> FunctionDeclaration::evaluate(SymbolTable& symbolTable) {
    variant<int, string> functionName = children[0]->children[0]->value;

    if (holds_alternative<int>(functionName)) {
        throw invalid_argument("Semantic: function identifier in declaration must be a string");
    }

    variant<int, string> functionType = children[0]->value;

    if (holds_alternative<int>(functionType)) {
        throw invalid_argument("Semantic: function type in declaration must be a string");
    }

    FunctionTable::create(get<string>(functionName), getSymbolTypeFromString(get<string>(functionType)), this);

    return make_pair(SymbolType::EMPTY, 0); 
}

FunctionCall::FunctionCall(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> FunctionCall::evaluate(SymbolTable& symbolTable) {
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
        pair<SymbolType, variant<int, string>> argument = child->evaluate(symbolTable);

        if (holds_alternative<int>(functionDeclarationNode->children[i + 1]->children[0]->value)) {
            throw invalid_argument("Semantic: argument name must be an identifier string");
        }

        functionSymbolTable->set(
            get<string>(functionDeclarationNode->children[i + 1]->children[0]->value),
            argument.second
        );

        i++;
    }

    pair<SymbolType, variant<int, string>> result = functionDeclarationNode->children[i + 1]->evaluate(*functionSymbolTable);

    if (result.first != get<SymbolType>(functionDeclaration)) {
        throw invalid_argument("Semantic: function result is not of type " + getSymbolTypeName(get<SymbolType>(functionDeclaration)));
    }

    return result; 
}

Block::Block(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Block::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate each of the childs
    for (const auto& child : children) {
        pair<SymbolType, variant<int, string>> result = child->evaluate(symbolTable);
        if (child->isReturnNode) {
            this->isReturnNode = true;
            return result;
        }
    }

    return make_pair(SymbolType::EMPTY, 0); 
}

Drive::Drive(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Drive::evaluate(SymbolTable& symbolTable) {
    auto checkCondition = [&](const pair<SymbolType, variant<int, string>>& driveVar,
                             const pair<SymbolType, variant<int, string>>& limitValue) {

        if (driveVar.first != limitValue.first) {
            throw invalid_argument("Semantic: first and second values of drive loop must have the same type");
        }

        if (driveVar.first == SymbolType::DOWN) {
            return getDownOrder(get<string>(driveVar.second)) <= getDownOrder(get<string>(limitValue.second));
        }
        return get<int>(driveVar.second) <= get<int>(limitValue.second);
    };

    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluates the variable declaration and assignment
    children[0]->evaluate(symbolTable);


    variant<int, string> identifier = children[0]->children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: drive identifier must be a string");
    }

    // Gets loop variable value
    pair<SymbolType, variant<int, string>> driveVar = symbolTable.get(get<string>(identifier));

    if (holds_alternative<string>(driveVar.second) && driveVar.first != SymbolType::DOWN) {
        throw invalid_argument("Semantic: drive loop value must be a number or a down");
    }

    // Gets limit value
    pair<SymbolType, variant<int, string>> limitValue = children[1]->evaluate(symbolTable);

    if (holds_alternative<string>(limitValue.second) && limitValue.first != SymbolType::DOWN) {
        throw invalid_argument("Semantic: drive loop value must be a number or a down");
    }

    if (driveVar.first != limitValue.first) {
        throw invalid_argument("Semantic: first and second values of drive loop must have same type");
    }

    pair<SymbolType, variant<int, string>> result = make_pair(SymbolType::EMPTY, 0);

    while (checkCondition(driveVar, limitValue)) {
        // Evaluates loop block
        result = children[2]->evaluate(symbolTable);

        if (children[2]->isReturnNode) {
            this->isReturnNode = true; 
            return result;
        }

        // Increments loops variable
        if (driveVar.first == SymbolType::DOWN) {
            symbolTable.set(get<string>(identifier), incrementDown(get<string>(driveVar.second)));
        } else {
            symbolTable.set(get<string>(identifier), get<int>(driveVar.second) + 1);
        }

        // Gets loop variable value
        driveVar = symbolTable.get(get<string>(identifier));
    }

    return result; 
}

PlayUntil::PlayUntil(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> PlayUntil::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    pair<SymbolType, variant<int, string>> condition = children[0]->evaluate(symbolTable);
    
    if (holds_alternative<string>(condition.second) || condition.first != SymbolType::NUMBER) {
        throw invalid_argument("Semantic: playuntil condition must be a boolean");
    }

    pair<SymbolType, variant<int, string>> result = make_pair(SymbolType::EMPTY, 0);

    // While stop condition isn't met
    while (!get<int>(condition.second)) {
        // Execute block
        result = children[1]->evaluate(symbolTable);

        if (children[1]->isReturnNode) {
            this->isReturnNode = true;
            return result;
        }

        // Reevaluate condition
        condition = children[0]->evaluate(symbolTable);

        if (holds_alternative<string>(condition.second)) {
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

pair<SymbolType, variant<int, string>> WhenConditional::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    pair<SymbolType, variant<int, string>> condition = children[0]->evaluate(symbolTable);

    if (holds_alternative<string>(condition.second) || condition.first != SymbolType::NUMBER) {
        throw invalid_argument("Semantic: when condition must be a boolean");
    }

    // Variable to store the result of the conditional block
    pair<SymbolType, variant<int, string>> result = make_pair(SymbolType::EMPTY, 0);

    // if condition execute if block, else is executed when condition isn´t met and 
    // else block exists
    if (get<int>(condition.second)) {
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

pair<SymbolType, variant<int, string>> VarDeclaration::evaluate(SymbolTable& symbolTable) {
    // Variable declaration, defines the type of the variable and can assign a value
    variant<int, string> identifier = children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    symbolTable.create(get<string>(identifier), getSymbolTypeFromString(get<string>(this->value)));

    if (children.size() == 1) {
        return make_pair(SymbolType::EMPTY, 0);
    }

    pair<SymbolType, variant<int, string>> value = children[1]->evaluate(symbolTable);

    symbolTable.set(get<string>(identifier), value.second);

    return make_pair(SymbolType::EMPTY, 0);
}

Assignment::Assignment(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Assignment::evaluate(SymbolTable& symbolTable) {
    // Assign the value of the expression to a variable in the symbol table
    variant<int, string> identifier = children[0]->value;

    if (holds_alternative<int>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    pair<SymbolType, variant<int, string>> value = children[1]->evaluate(symbolTable);

    symbolTable.set(get<string>(identifier), value.second);

    return make_pair(SymbolType::EMPTY, 0);
}

Call::Call(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Call::evaluate(SymbolTable& symbolTable) {
    // Prints in the std out the value of the expression
    pair<SymbolType, variant<int, string>> child = children[0]->evaluate(symbolTable);

    if (holds_alternative<string>(child.second)) {
        cout << get<string>(child.second) << endl;
    } else if (child.first == SymbolType::NUMBER) {
        cout << get<int>(child.second) << endl;
    } else if (child.first == SymbolType::EMPTY) {
        cout << "empty" << endl;
    }

    return make_pair(SymbolType::EMPTY, 0);
}


BinOp::BinOp(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> BinOp::evaluate(SymbolTable& symbolTable) {
    variant<int, string> result = 0;
    SymbolType resultType = SymbolType::NUMBER;

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    pair<SymbolType, variant<int, string>> left_child = children[0]->evaluate(symbolTable);
    pair<SymbolType, variant<int, string>> right_child = children[1]->evaluate(symbolTable);

    switch (get<int>(this->value)) {
        case (int) BinOperation::PLUS:
            if (
                holds_alternative<string>(left_child.second) && left_child.first == SymbolType::ATHLETE
                && holds_alternative<string>(right_child.second) && right_child.first == SymbolType::ATHLETE
            ) {
                result = get<string>(left_child.second) + get<string>(right_child.second);
                resultType = SymbolType::ATHLETE;
                break;
            }

            if (
                holds_alternative<string>(left_child.second) && left_child.first == SymbolType::ATHLETE
                && holds_alternative<int>(right_child.second) && right_child.first == SymbolType::NUMBER
            ) {
                result = get<string>(left_child.second) + to_string(get<int>(right_child.second));
                resultType = SymbolType::ATHLETE;
                break;
            }

            if (
                holds_alternative<int>(left_child.second) && left_child.first == SymbolType::NUMBER
                && holds_alternative<string>(right_child.second) && right_child.first == SymbolType::ATHLETE
            ) {
                result = to_string(get<int>(left_child.second)) + get<string>(right_child.second);
                resultType = SymbolType::ATHLETE;
                break;
            }

            if (
                holds_alternative<int>(left_child.second) && left_child.first == SymbolType::NUMBER
                && holds_alternative<int>(right_child.second) && right_child.first == SymbolType::NUMBER
            ) {
                result = get<int>(left_child.second) + get<int>(right_child.second);
                break;
            }

            throw invalid_argument(
                "Semantic: Invalid + operation between: " + getSymbolTypeName(left_child.first)
                + " and " + getSymbolTypeName(right_child.first)
            );
        
        case (int) BinOperation::MINUS:
            if (holds_alternative<string>(left_child.second)) {
                throw invalid_argument("Semantic: Cannot perform - operation in string: " + get<string>(left_child.second));
            }
            if (holds_alternative<string>(right_child.second)) {
                throw invalid_argument("Semantic: Cannot perform - operation in string: " + get<string>(right_child.second));
            }

            result = get<int>(left_child.second) - get<int>(right_child.second);
            break;

        case (int) BinOperation::TIMES:
            if (holds_alternative<string>(left_child.second)) {
                throw invalid_argument("Semantic: Cannot perform * operation in string: " + get<string>(left_child.second));
            }
            if (holds_alternative<string>(right_child.second)) {
                throw invalid_argument("Semantic: Cannot perform * operation in string: " + get<string>(right_child.second));
            }

            result = get<int>(left_child.second) * get<int>(right_child.second);
            break;

        case (int) BinOperation::DIVIDE:
            if (holds_alternative<string>(left_child.second)) {
                throw invalid_argument("Semantic: Cannot perform / operation in string: " + get<string>(left_child.second));
            }
            if (holds_alternative<string>(right_child.second)) {
                throw invalid_argument("Semantic: Cannot perform / operation in string: " + get<string>(right_child.second));
            }

            result = get<int>(left_child.second) / get<int>(right_child.second);
            break;

        case (int) BinOperation::EQUALS:
            if (holds_alternative<string>(left_child.second) && holds_alternative<string>(right_child.second)) {
                result = get<string>(left_child.second).compare(get<string>(right_child.second)) == 0 ? 1 : 0;
                break;
            }
            if (holds_alternative<int>(left_child.second) && holds_alternative<int>(right_child.second)) {
                result = get<int>(left_child.second) == get<int>(right_child.second) ? 1 : 0;
                break;
            }

            throw invalid_argument(
                "Semantic: Invalid equals operation between: " + getSymbolTypeName(left_child.first)
                + " and " + getSymbolTypeName(right_child.first)
            );

        case (int) BinOperation::GREATER_THAN:
            if (holds_alternative<string>(left_child.second) && holds_alternative<string>(right_child.second)) {
                result = get<string>(left_child.second).length() > get<string>(right_child.second).length() ? 1 : 0;
                break;
            }
            if (holds_alternative<int>(left_child.second) && holds_alternative<int>(right_child.second)) {
                result = get<int>(left_child.second) > get<int>(right_child.second) ? 1 : 0;
                break;
            }
            
            throw invalid_argument(
                "Semantic: Invalid > operation between: " + getSymbolTypeName(left_child.first)
                + " and " + getSymbolTypeName(right_child.first)
            );

        case (int) BinOperation::LESSER_THAN:
            if (holds_alternative<string>(left_child.second) && holds_alternative<string>(right_child.second)) {
                result = get<string>(left_child.second).length() < get<string>(right_child.second).length() ? 1 : 0;
                break;
            }
            if (holds_alternative<int>(left_child.second) && holds_alternative<int>(right_child.second)) {
                result = get<int>(left_child.second) < get<int>(right_child.second) ? 1 : 0;
                break;
            }
            
            throw invalid_argument(
                "Semantic: Invalid > operation between: " + getSymbolTypeName(left_child.first)
                + " and " + getSymbolTypeName(right_child.first)
            );

        case (int) BinOperation::AND:
            if (holds_alternative<string>(left_child.second)) {
                throw invalid_argument("Semantic: Cannot perform and operation in string: " + get<string>(left_child.second));
            }
            if (holds_alternative<string>(right_child.second)) {
                throw invalid_argument("Semantic: Cannot perform and operation in string: " + get<string>(right_child.second));
            }

            result = get<int>(left_child.second) && get<int>(right_child.second) ? 1 : 0;
            break;

        case (int) BinOperation::OR:
            if (holds_alternative<string>(left_child.second)) {
                throw invalid_argument("Semantic: Cannot perform or operation in string: " + get<string>(left_child.second));
            }
            if (holds_alternative<string>(right_child.second)) {
                throw invalid_argument("Semantic: Cannot perform or operation in string: " + get<string>(right_child.second));
            }

            result = get<int>(left_child.second) || get<int>(right_child.second) ? 1 : 0;
            break;

        default:
            break;
    }

    return make_pair(resultType, result);
}

UnOp::UnOp(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> UnOp::evaluate(SymbolTable& symbolTable) {
    variant<int, string> result = 0;
    SymbolType resultType = SymbolType::NUMBER;

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    pair<SymbolType, variant<int, string>> child = children[0]->evaluate(symbolTable);

    switch (get<int>(this->value)) {
        case (int) UnOperation::PLUS:
            if (holds_alternative<string>(child.second)) {
                throw invalid_argument("Semantic: Cannot perform + unary operation in string: " + get<string>(child.second));
            }
            result = get<int>(child.second);
            break;
        
        case (int) UnOperation::MINUS:
            if (holds_alternative<string>(child.second)) {
                throw invalid_argument("Semantic: Cannot perform - unary operation in string: " + get<string>(child.second));
            }
            result = -get<int>(child.second);
            break;

        case (int) UnOperation::NOT:
            if (holds_alternative<string>(child.second)) {
                throw invalid_argument("Semantic: Cannot perform not unary operation in string: " + get<string>(child.second));
            }
            result = !get<int>(child.second);
            break;

        case (int) UnOperation::INCREMENT:
            if (holds_alternative<string>(child.second) && child.first != SymbolType::DOWN) {
                throw invalid_argument("Semantic: Cannot perform >> unary operation in string: " + get<string>(child.second));
            }

            if (child.first == SymbolType::DOWN) {
                result = incrementDown(get<string>(child.second));
                resultType = SymbolType::DOWN;
            } else {
                result = get<int>(child.second) + 1;
            }
            break;

        default:
            break;
    }

    return make_pair(resultType, result);
}

Signal::Signal(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Signal::evaluate(SymbolTable& symbolTable) {
    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Returns the numeric value
    int input;
    cin >> input;
    return make_pair(SymbolType::NUMBER, input);
}

Number::Number(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Number::evaluate(SymbolTable& symbolTable) {
    // Returns the numeric value
    return make_pair(SymbolType::NUMBER, this->value);
}

String::String(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> String::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return make_pair(SymbolType::ATHLETE, this->value);
}

Down::Down(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Down::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return make_pair(SymbolType::DOWN, this->value);
}

Identifier::Identifier(variant<int, string> value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, variant<int, string>> Identifier::evaluate(SymbolTable& symbolTable) {
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

pair<SymbolType, variant<int, string>> NoOp::evaluate(SymbolTable& symbolTable) {
    // Returns empty
    return make_pair(SymbolType::EMPTY, this->value);
}