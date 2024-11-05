#pragma once

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "CNode.hpp"
#include "Operations.hpp"

class CTree{
    public:
        CTree();
        CTree(const CTree& pcOther);
        CTree(const std::string equation);
        ~CTree();
        CTree operator+(const CTree& pcOther);
        void operator=(const CTree& pcOther);
        void printTree();
        void printVariables();
        double calculate(std::string values);
    private:
        // Variables
        CNode* _root;
        std::map<std::string,Operation> _operations;
        std::map<std::string,int> _operationArg;
        std::map<std::string,int> _values;
        std::map<std::string,int> _variables;
        // Private functions;
        void destroyTree(CNode* current);
        int isOperation(std::string expression);
        int isNumber(std::string expression);
        std::string normalizeValue(std::string expression);
        std::string printTreeHelper(CNode* node);
        bool assignValues(std::string values);
        std::vector<std::string> splitValues(const std::string& values);
        double calculateHelper(CNode* node);
        void initialize();
};