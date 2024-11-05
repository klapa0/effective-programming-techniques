#pragma once

#include <string>

class CNumber{
    public:
        CNumber();
        CNumber(const CNumber& pcOther);
        CNumber(const int iValue);
        CNumber(int* iTable, const int tableSize);
        void operator=(const int iValue);
        void operator=(const CNumber& pcOther);
        CNumber operator/(const CNumber &pcOther);
        CNumber operator*(const CNumber& pcOther);
        CNumber operator+(const CNumber& pcOther);
        CNumber operator-(const CNumber& pcOther);
        void shiftLeft(const int shift);
        void shiftRight(const int shift);
        void incrementAt(const int arrSp);
        std::string toString();
        ~CNumber();
        int* getTable() const{
            return _table;
        }
        int getTableSize() const{
            return _table_size;
        }
        bool isNegative() const{
            return _is_negative;
        }
        void setIsNegative(bool isNegative){
            _is_negative=isNegative;
        }
        int* operator^(int x);
        
    private:
        int* _table;
        int _table_size;
        bool _is_negative;
        int compareCNumberTable(const CNumber& a, const CNumber& b);
        int compareCNumberTableWithSign(const CNumber& a, const CNumber& b);
        CNumber addCNumberTable(const int* first, const int firstSize, const int* second, const int secondSize);
        CNumber substractCNumberTable(const int* first, const int firstSize, const int* second, const int secondSize);
        int compareTables(const int* first, const int firstSize, const int* second, const int secondSize);
}; 
