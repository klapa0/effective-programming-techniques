#pragma once 

#include <string>
#include <iostream>

class CNode{
    public:
        CNode** children;
        CNode* parent;
        CNode();
        CNode(const CNode& pcOther);
        CNode(const std::string name, const int size);
        ~CNode();
        bool canHaveMoreChildren();
        bool haveChildren();
        int getSize() const{return _size;}
        std::string getName() const{
            return _name;}
        CNode* add(CNode* node);
        CNode* canAdd();
    private:
        std::string _name;
        int _size;
        int _children_num;
};