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
        unordered_map<string, variant<int, string>> emptyPlay;
        table[symbol] = make_pair(type, emptyPlay);
    } else if (type == SymbolType::NUMBER) {
        table[symbol] = make_pair(type, 0);
    } else if (type == SymbolType::DOWN) {
        table[symbol] = make_pair(type, "firstdown");
    } else {
        table[symbol] = make_pair(type, 0);
    }
}

pair<SymbolType, NodeValue> SymbolTable::get(const string& symbol) {
    auto it = table.find(symbol);
    if (it == table.end()) {
        throw runtime_error("Symbol not in table");
    }

    return it->second;
}

void SymbolTable::set(const string& symbol, const NodeValue value) {
    auto it = table.find(symbol);
    if (it == table.end()) {
        throw runtime_error("Symbol not in the table");
    }

    SymbolType symbolType = it->second.first;

    if (symbolType == SymbolType::ATHLETE && !holds_alternative<string>(value)) {
        throw runtime_error("Type mismatch for athlete type variable");
    }

    if (symbolType == SymbolType::PLAY && 
        !holds_alternative<unordered_map<string, variant<int, string>>>(value)) {
        throw runtime_error("Type mismatch for play type variable");
    }

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

pair<SymbolType, NodeValue> Node::evaluate(SymbolTable& symbolTable) {
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
        throw runtime_error("Function " + name + " not in table");
    }

    return it->second;
}

unordered_map<string, FunctionValue> FunctionTable::table;

Play::Play(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Play::evaluate(SymbolTable& symbolTable) {
    unordered_map<string, variant<int, string>> playMap;

    for (auto& playKeyValuePair: children) {
        NodeValue key = playKeyValuePair->children[0]->value;

        if (!holds_alternative<string>(key)) {
            throw invalid_argument("Semantic: play key must be a position");
        }

        string keyValue = get<string>(key);

        pair<SymbolType, NodeValue> value = playKeyValuePair->children[1]->evaluate(symbolTable);

        if (holds_alternative<int>(value.second)) {
            int intValue = get<int>(value.second);
            playMap[keyValue] = intValue;
        } else if (holds_alternative<string>(value.second)) {
            string strValue = get<string>(value.second);
            playMap[keyValue] = strValue;
        } else {
            throw invalid_argument("Semantic: play value must be a string or number");
        }
    }

    return make_pair(SymbolType::PLAY, playMap); 
}

Result::Result(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = true;
}

pair<SymbolType, NodeValue> Result::evaluate(SymbolTable& symbolTable) {
    return children[0]->evaluate(symbolTable); 
}

FunctionDeclaration::FunctionDeclaration(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> FunctionDeclaration::evaluate(SymbolTable& symbolTable) {
    NodeValue functionName = children[0]->children[0]->value;

    if (!holds_alternative<string>(functionName)) {
        throw invalid_argument("Semantic: function identifier in declaration must be a string");
    }

    NodeValue functionType = children[0]->value;

    if (!holds_alternative<string>(functionType)) {
        throw invalid_argument("Semantic: function type in declaration must be a string");
    }

    FunctionTable::create(get<string>(functionName), getSymbolTypeFromString(get<string>(functionType)), this);

    return make_pair(SymbolType::EMPTY, 0); 
}

FunctionCall::FunctionCall(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> FunctionCall::evaluate(SymbolTable& symbolTable) {
    if (!holds_alternative<string>(this->value)) {
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
        pair<SymbolType, NodeValue> argument = child->evaluate(symbolTable);

        if (!holds_alternative<string>(functionDeclarationNode->children[i + 1]->children[0]->value)) {
            throw invalid_argument("Semantic: argument name must be an identifier string");
        }

        functionSymbolTable->set(
            get<string>(functionDeclarationNode->children[i + 1]->children[0]->value),
            argument.second
        );

        i++;
    }

    pair<SymbolType, NodeValue> result = functionDeclarationNode->children[i + 1]->evaluate(*functionSymbolTable);

    if (result.first != get<SymbolType>(functionDeclaration)) {
        throw invalid_argument("Semantic: function result is not of type " + getSymbolTypeName(get<SymbolType>(functionDeclaration)));
    }

    return result; 
}

Block::Block(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Block::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate each of the childs
    for (const auto& child : children) {
        pair<SymbolType, NodeValue> result = child->evaluate(symbolTable);
        if (child->isReturnNode) {
            this->isReturnNode = true;
            return result;
        }
    }

    return make_pair(SymbolType::EMPTY, 0); 
}

Drive::Drive(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Drive::evaluate(SymbolTable& symbolTable) {
    auto checkCondition = [&](const pair<SymbolType, NodeValue>& driveVar,
                             const pair<SymbolType, NodeValue>& limitValue) {

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


    NodeValue identifier = children[0]->children[0]->value;

    if (!holds_alternative<string>(identifier)) {
        throw invalid_argument("Semantic: drive identifier must be a string");
    }

    // Gets loop variable value
    pair<SymbolType, NodeValue> driveVar = symbolTable.get(get<string>(identifier));

    if (holds_alternative<unordered_map<string, variant<int, string>>>(driveVar.second) && 
        holds_alternative<string>(driveVar.second) && 
        driveVar.first != SymbolType::DOWN) {
        throw invalid_argument("Semantic: drive loop value must be a number or a down");
    }

    // Gets limit value
    pair<SymbolType, NodeValue> limitValue = children[1]->evaluate(symbolTable);

    if (holds_alternative<unordered_map<string, variant<int, string>>>(driveVar.second) && 
        holds_alternative<string>(limitValue.second) 
        && limitValue.first != SymbolType::DOWN) {
        throw invalid_argument("Semantic: drive loop value must be a number or a down");
    }

    if (driveVar.first != limitValue.first) {
        throw invalid_argument("Semantic: first and second values of drive loop must have same type");
    }

    pair<SymbolType, NodeValue> result = make_pair(SymbolType::EMPTY, 0);

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

PlayUntil::PlayUntil(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> PlayUntil::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    pair<SymbolType, NodeValue> condition = children[0]->evaluate(symbolTable);
    
    if (!holds_alternative<int>(condition.second) || condition.first != SymbolType::NUMBER) {
        throw invalid_argument("Semantic: playuntil condition must be a boolean");
    }

    pair<SymbolType, NodeValue> result = make_pair(SymbolType::EMPTY, 0);

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

        if (!holds_alternative<int>(condition.second)) {
            throw invalid_argument("Semantic: playuntil condition must be a boolean");
        }
    }

    return result; 
}

WhenConditional::WhenConditional(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> WhenConditional::evaluate(SymbolTable& symbolTable) {
    // If this block has already been executed, resets the isReturnNode atribute
    this->isReturnNode = false;

    // Evaluate condition
    pair<SymbolType, NodeValue> condition = children[0]->evaluate(symbolTable);

    if (!holds_alternative<int>(condition.second) || condition.first != SymbolType::NUMBER) {
        throw invalid_argument("Semantic: when condition must be a boolean");
    }

    // Variable to store the result of the conditional block
    pair<SymbolType, NodeValue> result = make_pair(SymbolType::EMPTY, 0);

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

VarDeclaration::VarDeclaration(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> VarDeclaration::evaluate(SymbolTable& symbolTable) {
    // Variable declaration, defines the type of the variable and can assign a value
    NodeValue identifier = children[0]->value;

    if (!holds_alternative<string>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    symbolTable.create(get<string>(identifier), getSymbolTypeFromString(get<string>(this->value)));

    if (children.size() == 1) {
        return make_pair(SymbolType::EMPTY, 0);
    }

    pair<SymbolType, NodeValue> value = children[1]->evaluate(symbolTable);

    symbolTable.set(get<string>(identifier), value.second);

    return make_pair(SymbolType::EMPTY, 0);
}

Assignment::Assignment(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Assignment::evaluate(SymbolTable& symbolTable) {
    // Assign the value of the expression to a variable in the symbol table
    NodeValue identifier = children[0]->value;

    if (!holds_alternative<string>(identifier)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    pair<SymbolType, NodeValue> value = children[children.size() - 1]->evaluate(symbolTable);

    if (children.size() > 2) {
        NodeValue position = children[1]->value;

        if (!holds_alternative<string>(position)) {
            throw invalid_argument("Semantic: Play position value must be of type string");
        }

        pair<SymbolType, NodeValue> play = symbolTable.get(get<string>(identifier));

        if (play.first != SymbolType::PLAY ||
            !holds_alternative<unordered_map<string, variant<int, string>>>(play.second)) {
            throw invalid_argument("Semantic: Can only access dynamic values of plays");
        }

        unordered_map<string, variant<int, string>> playMap = get<unordered_map<string, variant<int, string>>>(play.second);

        if (holds_alternative<unordered_map<string, variant<int, string>>>(value.second) ||
            value.first == SymbolType::DOWN || value.first == SymbolType::PLAY || 
            value.first == SymbolType::EMPTY) {
            throw invalid_argument("Semantic: play value must be a string or number");
        }

        if (holds_alternative<int>(value.second)) {
            playMap[get<string>(position)] = get<int>(value.second);
        } else {
            playMap[get<string>(position)] = get<string>(value.second);
        }

        symbolTable.set(get<string>(identifier), playMap);

        return make_pair(SymbolType::EMPTY, 0);
    }

    symbolTable.set(get<string>(identifier), value.second);

    return make_pair(SymbolType::EMPTY, 0);
}

Call::Call(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Call::evaluate(SymbolTable& symbolTable) {
    auto printPlay = [](const unordered_map<string, variant<int, string>>& playMap) {
        cout << "{";
        bool first = true;
        for (const auto& pair : playMap) {
            if (!first) {
                cout << ", ";
            }
            cout << pair.first << ": ";
            const variant<int, string>& value = pair.second;
            if (holds_alternative<int>(value)) {
                cout << get<int>(value);
            } else if (holds_alternative<string>(value)) {
                cout << "\"" << get<string>(value) << "\"";
            }
            first = false;
        }
        cout << "}" << endl;
    };

    // Prints in the std out the value of the expression
    pair<SymbolType, NodeValue> child = children[0]->evaluate(symbolTable);

    if (holds_alternative<unordered_map<string, variant<int, string>>>(child.second)) {
        printPlay(get<unordered_map<string, variant<int, string>>>(child.second));
    } else if (holds_alternative<string>(child.second)) {
        cout << get<string>(child.second) << endl;
    } else if (child.first == SymbolType::NUMBER) {
        cout << get<int>(child.second) << endl;
    } else if (child.first == SymbolType::EMPTY) {
        cout << "empty" << endl;
    }

    return make_pair(SymbolType::EMPTY, 0);
}


BinOp::BinOp(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> BinOp::evaluate(SymbolTable& symbolTable) {
    NodeValue result = 0;
    SymbolType resultType = SymbolType::NUMBER;

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    pair<SymbolType, NodeValue> left_child = children[0]->evaluate(symbolTable);
    pair<SymbolType, NodeValue> right_child = children[1]->evaluate(symbolTable);

    if (holds_alternative<unordered_map<string, variant<int, string>>>(left_child.second)) {
        throw invalid_argument("Semantic: Cannot perform binary operations on play");
    }
    if (holds_alternative<unordered_map<string, variant<int, string>>>(right_child.second)) {
        throw invalid_argument("Semantic: Cannot perform binary operations on play");
    }

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

UnOp::UnOp(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> UnOp::evaluate(SymbolTable& symbolTable) {
    NodeValue result = 0;
    SymbolType resultType = SymbolType::NUMBER;

    if (holds_alternative<string>(this->value)) {
        throw invalid_argument("Unexpected variant type");
    }

    pair<SymbolType, NodeValue> child = children[0]->evaluate(symbolTable);

    if (holds_alternative<unordered_map<string, variant<int, string>>>(child.second)) {
        throw invalid_argument("Semantic: Cannot perform unary operations on play");
    }

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

Signal::Signal(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Signal::evaluate(SymbolTable& symbolTable) {
    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Returns the numeric value
    int input;
    cin >> input;
    return make_pair(SymbolType::NUMBER, input);
}

Number::Number(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Number::evaluate(SymbolTable& symbolTable) {
    // Returns the numeric value
    return make_pair(SymbolType::NUMBER, this->value);
}

String::String(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> String::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return make_pair(SymbolType::ATHLETE, this->value);
}

Down::Down(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Down::evaluate(SymbolTable& symbolTable) {
    // Returns the string value
    return make_pair(SymbolType::DOWN, this->value);
}

Identifier::Identifier(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> Identifier::evaluate(SymbolTable& symbolTable) {
    // Returns the identifier value in the symbolTable
    if (!holds_alternative<string>(this->value)) {
        throw invalid_argument("Semantic: Identifier value must be of type string");
    }

    pair<SymbolType, NodeValue> savedIdentifier = symbolTable.get(get<string>(this->value));

    if (savedIdentifier.first == SymbolType::PLAY && children.size() > 0) {
        NodeValue playPosition = children[0]->value;

        if (!holds_alternative<string>(playPosition)) {
            throw invalid_argument("Semantic: Identifier value must be of type string");
        }

        string playPositionKey = get<string>(playPosition);
        unordered_map<string, variant<int, string>> savedPlay = get<unordered_map<string, variant<int, string>>>(savedIdentifier.second);

        auto it = savedPlay.find(playPositionKey);
        if (it == savedPlay.end()) {
            throw runtime_error("Semantic: Accessing position " + playPositionKey + " not defined in play " + get<string>(this->value));
        }

        variant<int, string> playPositionValue = it->second;

        if (holds_alternative<int>(playPositionValue)) {
            return make_pair(SymbolType::NUMBER, get<int>(playPositionValue));
        } else {
            return make_pair(SymbolType::ATHLETE, get<string>(playPositionValue));
        }
    }

    return savedIdentifier;
}

NoOp::NoOp(NodeValue value, vector<unique_ptr<Node>> children) {
    this->value = value;
    this->children = move(children);
    this->isReturnNode = false;
}

pair<SymbolType, NodeValue> NoOp::evaluate(SymbolTable& symbolTable) {
    // Returns empty
    return make_pair(SymbolType::EMPTY, this->value);
}