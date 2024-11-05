#include <iostream>

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    // Checking if size is correct
    if (iSizeX <= 0 || iSizeY <= 0) {
        return false; 
    }
    // Alocation of the table
    *piTable = new int*[iSizeX];
    for (int i = 0; i < iSizeX; ++i) {
        (*piTable)[i] = new int[iSizeY];
    }

    return true;
}

bool b_dealloc_table_2_dim(int** piTable, int iSizeX) {
    if(iSizeX<=0 || piTable==NULL || *piTable==NULL){
        return false;
    }
    // Dealocating memory
    for (int i = 0; i < iSizeX; ++i) {
        if(piTable[i]==NULL) continue;
        delete[] piTable[i]; 
    }
    delete[] piTable;
    return true; 
}

int main() {
    int** pi_table;
    int sizeX = 5;
    int sizeY = 3;
    
    if (b_alloc_table_2_dim(&pi_table, sizeX, sizeY)) {
        std::cout << "Alokacja powiodła się!" << std::endl;
    }
    else {
        std::cerr << "Błąd alokacji pamięci!" << std::endl;
    }
    // Filling and showing the table
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            pi_table[i][j] = i * sizeY + j; 
        }
    }
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            std::cout << pi_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Dealocation of memory
    if (b_dealloc_table_2_dim(pi_table, sizeX)) {
        std::cout << "Dealokacja powiodła się!" << std::endl;
    } else {
        std::cerr << "Błąd przy dealokacji!" << std::endl;
    }
    b_dealloc_table_2_dim(pi_table, sizeX);
    
    return 0;
}
