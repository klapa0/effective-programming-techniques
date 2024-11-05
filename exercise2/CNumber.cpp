
#include <iostream>
#include <climits>
#include "include/CNumber.hpp"

#define STANDARD_VALUE 0
    // Standard constructor
    CNumber::CNumber() : CNumber(STANDARD_VALUE) {}

    // Copying constructor
    CNumber::CNumber(const CNumber &other){
        _table_size = other._table_size;
        _is_negative = other._is_negative;
        _table = new int[_table_size];
        for (int i = 0; i < _table_size; i++){
            _table[i] = other._table[i];
        }
    }

    CNumber::CNumber(const int iValue){
        // Checking sign
        if(iValue<0) _is_negative=true;
        else _is_negative=false;
        // Counting new size of the table
        int new_size=0;
        for(int i=abs(iValue);i>0;i/=10){new_size++;}
        if(iValue==0) new_size=1;
        _table_size=new_size;
        _table = new int[_table_size];
        // Assigning values to new array
        int helper = abs(iValue);
        for(int i=_table_size;i>0;i--){
            _table[i-1] = helper%10; 
            helper/=10;
        }
    }

    CNumber::CNumber(int* iTable, const int tableSize){
        _table = iTable;
        _table_size = tableSize;
        _is_negative = false;
    }

    // Assigning int value to CNumber table
    void CNumber::operator=(const int iValue){
        // Checking sign
        if(iValue<0) _is_negative=true;
        else _is_negative=false;
        // Counting new size of the table
        int new_size=0;
        for(int i=abs(iValue);i>0;i/=10){new_size++;}
        if(iValue==0) new_size=1;
        _table_size=new_size;
        delete[] _table;
        _table = new int[_table_size];
        // Assigning values to new array
        int helper = abs(iValue);
        for(int i=_table_size;i>0;i--){
            _table[i-1] = helper%10;
            helper/=10;
        }
        
    }

    // Coping other CNumber object
    void CNumber::operator=(const CNumber& pcOther){
        delete[] _table;
        _table = new int[pcOther.getTableSize()];
        _table_size = pcOther.getTableSize();
        for(int i=0;i<_table_size;i++){
            _table[i]=pcOther.getTable()[i];
        }
    }

    CNumber CNumber::operator/(const CNumber& pcOther) {
    if (pcOther.getTableSize() == 1 && pcOther.getTable()[0] == 0) {
        std::cout<<"No division by 0";
        return CNumber(INT_MAX);
    }
    CNumber quotient(0);
    CNumber divisor(pcOther);
    CNumber dividend(*this);
    divisor.setIsNegative(false);
    dividend.setIsNegative(false);
    if (compareCNumberTable(dividend, divisor) < 0) {
        return CNumber(0);
    } else if (compareCNumberTable(dividend, divisor) == 0) {
        return CNumber(1);
    }

    // Aligning the divisor with the leftmost digits of the dividend
    int shift = dividend.getTableSize() - divisor.getTableSize();
    divisor.shiftLeft(shift);
    for (int i = shift; i >= 0; --i) {
        while (compareCNumberTable(dividend, divisor) >= 0) {
            dividend=(dividend-divisor);
            quotient.incrementAt(i); 
        }
        divisor.shiftRight(1);
    }
    if(_is_negative==pcOther.isNegative()){
        quotient.setIsNegative(false);
    }else{quotient.setIsNegative(true);}
    return quotient;
}


    CNumber CNumber::operator*(const CNumber& pcOther){
        CNumber result(0);
        CNumber copy(*this);
        copy.setIsNegative(false);
        // Multiplication of those two numbers
        for(int i=0;i<pcOther.getTableSize();i++){
            for(int j=0;j<pcOther.getTable()[pcOther.getTableSize()-i-1];j++){
                result=(result+copy);       
            }
            copy.shiftLeft(1);
        }
        // Sign works like "--""=="+"" "-+"" == "-" "++" ="+" 
        result.setIsNegative(!(pcOther.isNegative()==_is_negative));
        return result;
    }

    CNumber CNumber::operator+(const CNumber& pcOther){
        // Addition with the same signs works normally with the same sign
        if(_is_negative == pcOther.isNegative()){
            CNumber returning = addCNumberTable(_table,_table_size, pcOther.getTable(), pcOther.getTableSize());
            returning.setIsNegative(_is_negative);
             return returning;
             }
        // Addition with diff signs works like substraction of the bigger and smaller number with the sign of the bigger
        int compareValue=compareCNumberTable(*this, pcOther);
        if(compareValue>0){
            CNumber returning = substractCNumberTable(_table, _table_size, pcOther.getTable(),pcOther.getTableSize());
            returning.setIsNegative(_is_negative);
            return returning;
        }
        if(compareValue==0){
            return CNumber(0);
        }
        else{
            CNumber returning = substractCNumberTable(pcOther.getTable(),pcOther.getTableSize(),_table,_table_size);
            returning.setIsNegative(pcOther.isNegative());
            return returning;
        }
        
    }

    // Function that returns substraction of this CNumber and other
    CNumber CNumber::operator-(const CNumber& pcOther){
        // Substraction for different signs work like addition with the same sign of the first
        if(_is_negative != pcOther.isNegative()){
            CNumber returning = addCNumberTable(_table,_table_size, pcOther.getTable(), pcOther.getTableSize());
            returning.setIsNegative(_is_negative);
             return returning;
             }
        // Substraction works like substraction bigger and smaller number with the sing of bigger
        int compareValue=compareCNumberTable(*this, pcOther);
        if(compareValue>0){
            CNumber returning = substractCNumberTable(_table, _table_size, pcOther.getTable(),pcOther.getTableSize());
            returning.setIsNegative(_is_negative);
            return returning;
        }
        if(compareValue==0){
            return CNumber(0);
        }
        else{
            CNumber returning = substractCNumberTable(pcOther.getTable(),pcOther.getTableSize(),_table,_table_size);
            returning.setIsNegative(!pcOther.isNegative());
            return returning;
        }
    }

    // Returns as a string number that is represented by CNumber
    std::string CNumber::toString(){
        std::string object_info = "";
        if (_is_negative) {object_info.append("-");}
        for (int i = 0; i < _table_size; i++) {object_info.append(std::to_string(_table[i]));}
        return object_info;
    }

    // Destructor
    CNumber::~CNumber(){
        delete[] _table;
    }
    int CNumber::compareCNumberTable(const CNumber& a, const CNumber& b){
        return compareTables(a.getTable(), a.getTableSize(), b.getTable(), b.getTableSize());
    }
    // Function which compare CNumbers
    int CNumber::compareCNumberTableWithSign(const CNumber& a, const CNumber& b){
        if(a.isNegative() != b.isNegative()){
            if(a.isNegative()){return -1;}
            else{return 1;}
        }
        return compareTables(a.getTable(), a.getTableSize(), b.getTable(), b.getTableSize());
    }

    //Function which compare tables
    int CNumber::compareTables(const int* firstTable, const int firstSize, const int* secondTable, const int secondSize){
        if(firstSize != secondSize) return firstSize-secondSize;
        for(int i=0;i<firstSize;i++){
            if(firstTable[i]!=secondTable[i]) return firstTable[i]-secondTable[i];
        }
        return 0;
    }

    // Function that substracts two arrays and returns CNumber 
    CNumber CNumber::substractCNumberTable(const int* first, const int firstSize, const int* second, const int secondSize){
    int* result_table = new int[firstSize]();
    // Initialize result_table with the first array values
    for (int i = 0; i < firstSize; i++) {
        result_table[i] = first[i];
    }
    // Subtracting second array from result_table
    for (int i = 0; i < secondSize; i++) {
        result_table[firstSize - secondSize + i] -= second[i];
    }
    // Handling borrow
    for (int i = firstSize - 1; i > 0; i--) {
        if (result_table[i] < 0) {
            result_table[i] += 10;
            result_table[i - 1]--;
        }
    }
    int leading_zeros = 0;
    while (leading_zeros < firstSize && result_table[leading_zeros] == 0) {
        leading_zeros++;
    }
    // Creating the final result without leading zeros
    int newSize = firstSize - leading_zeros;
    int* finalresult_table = new int[newSize];

    for (int i = 0; i < newSize; i++) {
        finalresult_table[i] = result_table[leading_zeros + i];
    }
    return CNumber(finalresult_table, newSize);
    }

    // Funcito that adds two arrays and returns CNumber
    CNumber CNumber::addCNumberTable(const int* first, const int firstSize, const int* second, const int secondSize){
        int bigger_size=std::max(firstSize,secondSize);
        int smaller_size=std::min(firstSize,secondSize);
        int* result = new int[bigger_size];
        const int* smaller_table;
        // Making copy of the bigger array
        if(firstSize>=secondSize){
            for(int i=0;i<firstSize;i++){result[i] = first[i];}
            smaller_table=second;
        }else{
            for(int i=0;i<secondSize;i++){result[i]=second[i];}
            smaller_table=first;
        }
        // Adding smaller array to the bigger
        int carry = 0;
        for(int i=0;i<smaller_size;i++){
            int sum = result[bigger_size-1-i]+smaller_table[smaller_size-1-i]+carry;
            if(sum>=10){
                carry=1;
                result[bigger_size-1-i]=sum-10;
            }else{
                carry=0;
                result[bigger_size-1-i]=sum;
            }
        }
        // If carry left after adding add it to the result
        int i = smaller_size;
        while(carry>0 && i<bigger_size){
            int sum = result[bigger_size-1-i]+carry;
            if(sum>=10){
                carry=1;
                result[bigger_size-1-i]=sum-10;
            }
            else{
                carry=0;
                result[bigger_size-1-i]=sum;
            }
            i++;
        }
        // If carry left after addition make bigger array
        if(carry==1){
            bigger_size++;
            int* helper = new int[bigger_size+1];
            helper[0]=1;
            for(int j=0;j<bigger_size;j++){
                helper[j+1] = result[j];
            }
            delete[] result;
            result = helper;
        }

        return CNumber(result, bigger_size);
    }

    // Function that shift CNumber to the left *10^(shift)
    void CNumber::shiftLeft(const int shift){
        if(shift<=0) return;
        int new_size = _table_size+shift;
        int* helper = new int[new_size];
        for(int i=0;i<_table_size;i++){
            helper[i] = _table[i];
        }
        for(int i=_table_size;i<new_size;i++){
            helper[i] = 0;
        }
        delete[] _table;
        _table = helper;
        _table_size =new_size;
    }

    // Function that shifts CNumber to the right *10^(-shift)
    void CNumber::shiftRight(const int shift){
        if(shift<=0) return;
        int new_size = _table_size-shift;
        if(new_size<=0) return;
        int* helper = new int[new_size];
        for(int i=0;i<new_size;i++){
            helper[i] = _table[i];
        }
        delete[] _table;
        _table = helper;
        _table_size = new_size;
    }

    //Incrementing by one CNumber at arrSp 
    void CNumber::incrementAt(const int arrSp){
        if(arrSp<0) return;
        if(arrSp+1>_table_size){
            int* helper = new int[arrSp+1];
            helper[0]=1;
            for(int i=1;i<arrSp-_table_size+1;i++){helper[i]=0;}
            for(int i=0;i<_table_size;i++){helper[arrSp-_table_size+1+i]=_table[i];}
            delete[] _table;
            _table = helper;
            _table_size = arrSp+1;
        }else{
            if(_table[_table_size-arrSp-1]+1==10) return;
            _table[_table_size-arrSp-1]=_table[_table_size-arrSp-1]+1;
        }
    }
    int* CNumber::operator^(int x){
        CNumber helper = CNumber(x);
        CNumber second_helper = CNumber(*this);
        if(compareCNumberTableWithSign(*this, CNumber(x))<0){
            int* result = new int[1];
            result[0] = _table[0];
            return result;
        }
        int i=1;
        while(compareCNumberTableWithSign(*this, helper)>=0){
            helper=helper*CNumber(x);
            i++;
        }
        int* result = new int[i];

        for(int z=0;z<i;z++){result[z]=0;}
        helper=(helper/ CNumber(x));
        for(int j=0;j<i;j++){
        while(compareCNumberTableWithSign(second_helper-helper,CNumber(0))>=0){
            second_helper =second_helper-helper;
            result[j]=result[j]+1; 
           
        }
        
        helper=helper/CNumber(x);
        }
        std::cout<<"\n";
        for(int j=0;j<i;j++){
            std::cout<<result[j];
        }
        return result;
    }
 

int main(){
    CNumber kupa;
    kupa = 379;
    std::cout<<(kupa.toString())<<"\n";
    CNumber kp = CNumber(999);
    std::cout<<(kp.toString())<<"\n";
    std::cout<<((kupa-kp).toString())<<"\n";
    kp.setIsNegative(true);
    std::cout<<((kupa+kp).toString())<<"\n";
    std::cout<<((CNumber(1000)-CNumber(22)).toString())<<"\n";
    std::cout<<((CNumber(999)+CNumber(1)).toString())<<"\n";
    std::cout<<((CNumber(37)*CNumber(-11)).toString())<<CNumber(37).toString()<<CNumber(11).toString()<<"\n";
    std::cout<<((CNumber(-99)*CNumber(-2)).toString())<<"\n";
    std::cout<<((CNumber(121)*CNumber(3012)).toString())<<"\n";
    std::cout<<((CNumber(364452)/CNumber(13)).toString())<<"\n";
    std::cout<<((CNumber(3448182)/CNumber(-123)).toString())<<"\n";
    std::cout<<((CNumber(-229998)/CNumber(6777)).toString())<<"\n";
    int* table = CNumber(65)^4;
    delete[] table;

}
