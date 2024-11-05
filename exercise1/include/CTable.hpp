#ifndef CTABLE
#define CTABLE

#include<string>
#include<iostream>

class CTable {
private:
    std::string s_name_;
    int* pi_table_;
    int i_table_len_;
    const std::string DEFAULT_NAME="default";
    const int  DEFAULT_TABLE_LENGTH=10;

public:
    // Default constructor
    CTable();

    // Constructor with parameters
    CTable(std::string sName, int iTableLen);

    // Coping constructor
    CTable(const CTable &pcOther);

    // Destruktor
    ~CTable();

    // Method which changes name
    void vSetName(std::string sName);

    // Method with changes size of the table
    bool bSetNewSize(int iTableLen);

    // Method witch returns copy of the object
    CTable* pcClone();
    // Getter
    int getITableLen();

    bool bDoubleLen();
};

#endif