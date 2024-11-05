#include <iostream>
#include "include/CTree.hpp"
#include "CNode.cpp"

// Basic constructor
CTree::CTree(){
    _root = NULL;
    initialize();
}

// Copy constructor
CTree::CTree(const CTree& pcOther){
    if (pcOther._root != NULL) {
        _root = new CNode(*pcOther._root); 
    } else {
        _root = NULL;
    }
    _values=pcOther._values;
    _variables=pcOther._variables;
}

// Constructor with equation
CTree::CTree(std::string  equation){
    initialize();
    long unsigned int i=0;
    std::vector<std::string> expressions = splitValues(equation);
    int result = isOperation(expressions[i]);
    if(result>0){
        _root= new CNode(expressions[i], result);
        }else{
        result = isNumber(expressions[i]);
        _root =new CNode(expressions[i], 0);
        if(result>=0){
           _values[expressions[i]] = result; 
        }else{
            std::string resultNormalized = normalizeValue(expressions[i]);
            if(resultNormalized!=""){_variables[expressions[i]] = 1;}}
        }
    i++;
    CNode* current = _root->canAdd();
    while(current!=NULL && i<expressions.size()){
        result = isOperation(expressions[i]);
        if(result>0){
            current= current->add(new CNode(expressions[i], result))->canAdd();
        }
        else{
            result = isNumber(expressions[i]);
            if(result>=0){
                current= current->add(new CNode(expressions[i], 0))->canAdd();
               _values[expressions[i]] = result;
            }
            else{
                std::string resultNormalized = normalizeValue(expressions[i]);
                if(resultNormalized!=""){
                    current= current->add(new CNode(resultNormalized, 0))->canAdd();
                    _variables[resultNormalized] = 1;
                }
            }
        }
    i++;
    };
    bool changed =false;
    if(current != NULL){  
        changed = true;
        while(current!=NULL){
            current= current->add(new CNode("1", 0))->canAdd();
        }
    }
    if(changed){
    std::cout<<"Zmodyfikowano poczatkowa formułe na : ";
    printTree();}
    
}

// Adding operations to map 
void CTree::initialize(){
    _operationArg["+"]=2;
    _operations["+"] =add;
    _operationArg["-"]=2;
    _operations["-"] =subtract;
    _operationArg["/"]=2;
    _operations["/"] =divide;
    _operationArg["*"]=2;
    _operations["*"] =multiply;
    _operationArg["sin"]=1;
    _operations["sin"] =sinus;
    _operationArg["cos"]=1;
    _operations["cos"] =cosinus;
}

// Destructor
CTree::~CTree(){
    
    if(_root!=NULL){
    destroyTree(_root);
    }
}

// destroys all nodes from current
void CTree::destroyTree(CNode* current){
    if (current == NULL){return;}
    for(int i=0;i<current->getSize();i++){
        if(current->children[i] != NULL){
            destroyTree(current->children[i]);
        }
    }
    delete current;

}
// Adds second tree on the place of the leaf of the first
CTree CTree::operator+(const CTree& pcOther){
    CTree result;
    if(this->_root==NULL){
        result=pcOther;
        return result;
    }else if(pcOther._root==NULL){
        result=*this;
        return result;
    }
    result=*this;
    CNode* current;
    current = result._root;
    while(current->getSize()>0){
        current = current->children[0];
    }
    current=current->parent;
    delete current->children[0];
    current->children[0] = new CNode(*pcOther._root);
    for (std::map<std::string, int>::const_iterator it = pcOther._values.begin(); it != pcOther._values.end(); ++it) {
        result._values[it->first] = it->second;
    }
    for (std::map<std::string, int>::const_iterator it = pcOther._variables.begin(); it != pcOther._variables.end(); ++it) {
        result._variables[it->first] = it->second; 
    }
    return result;
}

// Copy other CTree object data
void CTree::operator=(const CTree& pcOther){
    if (this == &pcOther) {
        return; 
    }
    if(_root!=NULL){destroyTree(_root);}
    if(pcOther._root==NULL){return;}
    _root= new CNode(*pcOther._root);
    _values=pcOther._values;
    _variables=pcOther._variables;
}

// Prints Ctree's CNodes
void CTree::printTree(){
    
    std::cout<<printTreeHelper(_root)<<std::endl;
}

std::string CTree::printTreeHelper(CNode* node){
    std::string result = node->getName();
    for(int i=0;i<node->getSize();i++){
        result+= " "+printTreeHelper(node->children[i]);
    }
    return result;
}

// Prints all variables
void CTree::printVariables(){
    std::cout << "Variables: ";
    for (std::map<std::string, int >::iterator it = _variables.begin(); it != _variables.end(); ++it) {
        const std::string& varName = it->first;
        std::cout<< varName<<" ";
    }
    std::cout <<"\n";
}

// Assing and checks if there are sufficient values for variables
bool CTree::assignValues(std::string values){
    std::vector<std::string> tokens = splitValues(values);
    long unsigned int expectedCount = _variables.size();
    
    // Check if the number of values matches the number of variables
    if (tokens.size() != expectedCount) {
        std::cout << "Error: Expected " << expectedCount << " values, but got " << tokens.size() << "." << std::endl;
        return false;
    }

    // Check if all tokens are numeric and assign valuesint
    long unsigned int i = 0;
    for (std::map<std::string, int >::iterator it = _variables.begin(); it != _variables.end(); ++it, ++i) {
        int value = isNumber(tokens[i]);
        if (value < 0) { // `-1` indicates an invalid number
            std::cout << "Error: Invalid number found for variable " << it->first << "." << std::endl;
            return false;
        }
        _values[it->first] = value;
    }

    return true;
}

// Calculates the value of all operations in tree
double CTree::calculate(std::string values){
    if(!assignValues(values)){return 0;}
    return calculateHelper(_root);
}

double CTree::calculateHelper(CNode* node){
    if(node->getSize()>0){
        std::vector<double> values;
        for(int i=0;i<node->getSize();i++){
            values.push_back(calculateHelper(node->children[i]));
        }
        return _operations.find(node->getName())->second(values);
    }
    return _values.find(node->getName())->second;
}

// Checks if it is operation and returns how many variables it has
int CTree::isOperation(std::string expression){
    std::map<std::string, int>::iterator it = _operationArg.find(expression);
    if (it != _operationArg.end()) {
        return it->second;
    } else {
        return 0;
    }
}

// Checks if the variable is number and return value
int CTree::isNumber(std::string expression) {
    if (expression.empty()) {
        return -1;
    }
    int result = 0; // Variable to store the resulting integer
    for (size_t i = 0; i < expression.length(); ++i) {
        if (!std::isdigit(expression[i])) { // Check if each character is a digit
            return -1; // Return -1 if any character is not a digit
        }
        // Convert char digit to int and accumulate
        result = result * 10 + (expression[i] - '0');
    }
    return result; 
}

std::string CTree::normalizeValue(std::string expression) {
    std::string normalized; // To store the normalized variable name
    bool hasLetter = false; // Flag to check if there is at least one letter

    for (char ch : expression) {
        if (std::isalpha(ch)) {
            hasLetter = true; // Found a letter
            normalized += ch; // Add letter to the normalized string
        } else if (std::isdigit(ch)) {
            normalized += ch; // Add digit to the normalized string
        } else {
            // If character is not a valid letter or digit, we can ignore it
            std::cout << "Ignoring invalid character: " << ch << std::endl;
        }
    }

    // Check if the normalized string contains at least one letter
    if (!hasLetter) {
        std::cout << "Invalid variable name. It must contain at least one letter." << std::endl;
        return ""; // Return an empty string if there are no letters
    }

    return normalized; // Return the normalized variable name
}

// Split string by " "
std::vector<std::string> CTree::splitValues(const std::string& values) {
    std::vector<std::string> tokens;
    std::string token;
    long unsigned int i=0;
    while(i<values.length()){
        token="";
        while(i<values.length() && values.at(i)!= ' '){
            token.push_back(values.at(i));
            i++;
        }
        i++;
        if(token!=""){
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main(){
    CTree* test = new CTree("- 1 - sin a c");
    test->printTree();
    test->printVariables();
    std::cout<<test->calculate("0 1");
    CTree wow;
    wow=*test;
    wow.printTree();
    (wow+*test).printTree();
    (wow+*test).printVariables();
    return 0;
}