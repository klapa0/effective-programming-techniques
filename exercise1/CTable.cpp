#include <iostream>
#include <string>
#include <climits>
#include "include/CTable.hpp"



    // Default constructor
    CTable::CTable() {
        s_name_ = DEFAULT_NAME;
        i_table_len_ = DEFAULT_TABLE_LENGTH;
        pi_table_ = new int[i_table_len_];
        std::cout << "bezp: '" << s_name_ << "'" << std::endl;
    }

    // Constructor with parameters
    CTable::CTable(std::string sName, int iTableLen) {
        s_name_ = sName;
        if(iTableLen<=0){
            i_table_len_=DEFAULT_TABLE_LENGTH;
        }
        else{
        i_table_len_ = iTableLen;
        }
        pi_table_ = new int[i_table_len_];
        std::cout << "parametr: '" << s_name_ << "'" << std::endl;
    }

    // Coping constructor
    CTable::CTable(const CTable &pcOther) {
        s_name_ = pcOther.s_name_ + "_copy";
        i_table_len_ = pcOther.i_table_len_;
        pi_table_ = new int[i_table_len_];
        for (int i = 0; i < i_table_len_; i++) {
            pi_table_[i] = pcOther.pi_table_[i];
        }
        std::cout << "kopiuj: '" << s_name_ << "'" << std::endl;
    }

    // Destruktor
    CTable::~CTable() {
        std::cout << "usuwam: '" << s_name_ << "'" << std::endl;
        delete[] pi_table_;
    }

    // Method which changes name
    void CTable::vSetName(std::string sName) {
        s_name_ = sName;
    }

    // Method with changes size of the table
    bool CTable::bSetNewSize(int iTableLen) {
        if (iTableLen <= 0) {
            return false;
        }
        delete[] pi_table_;
        pi_table_ = new int[iTableLen];

        i_table_len_ = iTableLen;
        return true;
    }

    // Method witch returns copy of the object
    CTable* CTable::pcClone() {
        return new CTable(*this);
    }
    // Getter
    int CTable::getITableLen(){
        return i_table_len_;
    }

    bool CTable::bDoubleLen(){
        if(i_table_len_*2>=INT_MAX || i_table_len_*2<=0){
            return false;
        }
        delete[] pi_table_;
        pi_table_ = new int[i_table_len_*2];
        i_table_len_ =i_table_len_*2;
        return true;
    }


// Function with modifies table size of the object
void v_mod_tab(CTable* pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}

// Function with modifies copy of the object
void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}

int main() {
    // Test of construcotrs
    CTable c1;
    CTable c2("Tablica1", 2);
    CTable c3(c2);

    // Testing changing of the name
    c1.vSetName("NewName");

    // Testing of the size change
    c2.bSetNewSize(7);
    c2.vSetName("Tablica2");
    // Cloning c2 object
    CTable* c2_clone = c2.pcClone();
    c2.vSetName("Tablica3");
    // Testing of the function  
    v_mod_tab(&c2, 10);
    std::cout<<c2.getITableLen()<<'\n';
    c2.vSetName("Tablica4");
    v_mod_tab(c2, 12); 
    std::cout<<c2.getITableLen()<<'\n';
    c2.bDoubleLen();
    std::cout<<c2.getITableLen()<<'\n';
    // Dealocating memory
    delete c2_clone;

    return 0;
}
