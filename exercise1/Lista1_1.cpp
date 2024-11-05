#include <iostream>

void v_alloc_table_fill_34(int iSize) {
    const int table_content=34;
    // Checking if size correct
    if (iSize <= 0) {
        std::cout << "Błąd: Nieprawidłowy rozmiar tablicy. Musi być większy niż 0." << std::endl;
        return;
    }

    // Allocating array
    int* pi_table = new int[iSize];

    // Filing table
    for (int i = 0; i < iSize; ++i) {
        pi_table[i] = table_content;
    }

    // Printing content of table
    std::cout << "Zawartość tablicy: ";
    for (int i = 0; i < iSize; ++i) {
        std::cout << pi_table[i] << " ";
    }
    std::cout << std::endl;

    // Dealocation of memory
    delete[] pi_table;
}

int main() {
    // Example of function
    v_alloc_table_fill_34(5); 
    v_alloc_table_fill_34(-1); 

    return 0;
}
