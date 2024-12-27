//Test sudoku board generation
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;

class Table{
public:
    Table(); // make table
    void print(); // print
    void end(); // destructor

    void column(int x, int y, int n); // column
    void square(int x, int y, int n); // using
    void rows(int x, int y, int n); // using

    void assign(int x, int y, int seenNums[9]); // assign numbers
    bool usedNums(int num, int seenNums[9]);

private:
    int row;
    int col;
    int** table;
};

Table::Table(){
    srand(time(0));
    row = 9;
    col = 9;

    table = new int*[row];
    for(int i = 0; i < row; i++){
        table[i] = new int[col];
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            table[i][j] = 0;
        }
    }

}

void Table::print(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}


void Table::rows(int x, int y, int n){
    for(int i = 0; i < col; i++){
        int seenNums[9];
        //table[x][i]
        assign(x , i , seenNums);
        
    }
}

void Table::column(int x, int y, int n){
    for(int i = 0; i < row; i++){
        int seenNums[9];
        assign(i, y , seenNums);
        
    }
}

void Table::square(int x, int y, int n){
    for(int r = 0; r < 3; r++){
        int girdrow = (x / 3) * 3;

        for(int c = 0; c < 3; c++){
            int girdcol = (y / 3) * 3;
            int seenNums[9] = {0};

            for(int i = girdrow; i < girdrow + 3; i++){

                for(int k = girdcol; k < girdcol + 3; k++){
                    assign(i,k, seenNums);
                }   
            }            
        }
    }
}


void Table::assign(int x, int y, int seenNums[9]) {
    bool repeat = true;
    if(table[x][y] == 0){
        table[x][y] = rand() % 9 + 1;
    }

    while(repeat == true){
        for (int i = 0; i < 9; i++) {
            if (seenNums[i] == table[x][y]) {
                table[x][y] = rand() % 9 + 1;
                break;
            }
        }
        repeat = false;
    }
    
}

bool Table::usedNums(int num, int seenNums[9]) {
    for (int i = 0; i < 9; i++) {
        if (seenNums[i] == num) {
            return true;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (seenNums[i] == 0) {
            seenNums[i] = num;
            break;
        }
    }
    return false;
}

void Table::end(){
    for (int i = 0; i < row; ++i) {
        delete[] table[i];
    }
    delete[] table;
    table = nullptr;
}

int main(){
    Table e;
    int x = 0;
    int y = 0;
    int n = 1;
    e.rows(x,y,n);
    e.column(x,y,n);
    e.square(x,y,n);
    e.print();
    e.end();
}