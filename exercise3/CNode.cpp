#include <iostream>
#include "include/CNode.hpp"

CNode::CNode(){
    _name = "1";
    _size = 0;
    _children_num = 0;
    children = NULL;
}

CNode::CNode(const CNode& pcOther){
    _name = pcOther.getName();
    _size = pcOther.getSize();
    _children_num=0;
    children = new CNode*[_size];
    for(int i=0;i<_size;i++){
        children[i] = new CNode(*pcOther.children[i]);
        children[i]->parent = this;
    }
}

CNode::CNode(const std::string name, const int size){
    _name = name;
    _size = size;
    _children_num =0;
    children = new CNode*[_size];
}

CNode::~CNode(){
    delete[] children;
}

bool CNode::canHaveMoreChildren(){
    return _size-_children_num>0;
}

bool CNode::haveChildren(){
    return _size>0;
}

CNode* CNode::add(CNode* node){
    if(_size == _children_num){
        if(parent==NULL){
            return NULL;
        }
        return parent->add(node);
    }
    else{
        children[_children_num] = node;
        _children_num++;
        node->parent=this;
        if(node->getSize()>0){
            return node;
        }else{
            return this;
        }
    }
}
CNode* CNode::canAdd(){
    if(_size == _children_num){
        if(parent==NULL){
            return NULL;
        }
        return parent->canAdd();
    }
     else{
        return this;
     }
}