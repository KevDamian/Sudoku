#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;

class Board {
public:
    // visuals / creating grid
    void Display();
    void emptyspaces();
    void VerticleLines();
    void HorizontialLines();

    // Board creating / game and destructor
    Board();
    void Game();
    void endGame();

    // Checking nums to ensure it follows sudoku rules
    bool numbercheck();// used to call row, col, gird -check
    bool usedNums(int num, int seenNums[9]); // recieve values from row, col, grid checks
    bool rowCheck();
    bool colCheck();
    bool gridCheck();

    // Array navigation & edit (Gameplay)
    void displayPoint(int x, int y);
    void moveAround();
    void editValues(int x, int y);

private:
    int rows;
    int columns;
    int** game;
    void generateRow(int rowIndex);
    bool gameOver = false;
};

Board::Board() {
    srand(time(0));
    rows = 9;
    columns = 9;

    game = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        game[i] = new int[columns];
    }

    for (int i = 0; i < rows; ++i) {
        generateRow(i);
    }
}

void Board::generateRow(int rowIndex) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            game[i][j] = rand() % 9 + 1;
        }
    }
}

void Board::emptyspaces(){
    int emptyCells = 40;
    while (emptyCells > 0) {
        int x = rand() % 9;
        int y = rand() % 9;

        if (game[x][y] != 0) {
            game[x][y] = 0;
            emptyCells--;
        }
    }
}

// following two functions print the board lines
void Board::VerticleLines(){
    cout << "+---------+---------+---------+" << endl;
}

void Board::HorizontialLines() {
    cout << "|";
}

// display board
void Board::Display() {
    //emptyspaces(); // set empty spaces
    for (int i = 0; i < rows; i++) {
        if (i % 3 == 0) {
            VerticleLines();
        }

        for (int j = 0; j < columns; j++) {
            if (j % 3 == 0) {
                HorizontialLines();
            }
            if(game[i][j] == 0){
                cout << "   ";
            }else{
                cout << " " << game[i][j] << " ";
            }
        }
        HorizontialLines();
        cout << endl;
    }
    VerticleLines();

}

// this function is supposed to take the nine numbers in the numbercheck function and sees if theres a repeat
bool Board::usedNums(int num, int seenNums[9]) {
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

bool Board::rowCheck(){
    for(int i = 0; i < rows; i++){
        int seenNums[9] = {0};
        for(int j = 0; j < columns; j++){
            if(usedNums(game[i][j], seenNums)){
                return true;
            }
        }
    }
    return false;
}

bool Board::colCheck(){
    for(int k = 0; k < columns; k++){
        int seenNums[9] = {0};
        for(int l = 0; l < rows; l++){
            if(usedNums(game[l][k], seenNums)){
                return true;
            }
        }
    }   
    return false;
}

bool Board:: gridCheck(){
    for(int a = 0; a <= 2; a++){
        for(int b = 0; b <= 2; b ++ ){
            int seenNums[9] = {0};
            //row loop
            for(int i = 0 + a * 3; i < 3 + a * 3; i++){
                // column loop
                for(int j = 0 + b * 3; j < 3 + b * 3; j++){
                    if(usedNums(game[i][j], seenNums)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Board::numbercheck(){
    if(rowCheck()){
        return true;
    }
    if(colCheck()){
        return true;
    }
    if(gridCheck()){
        return true;
    }
    return false;
}

void Board::editValues(int x, int y){
    int n;
    cout << "Enter new value: ";
    if(cin >> n){
        if(n < 10 || n > 0){
            game[x][y] = n;
            cout << "New value for " << "(" << x << "," << y << ") is " << game[x][y] << endl;
            Display();
        }else{
            cout << "Enter number from 1 - 9";
        }
    }else{
        cout << "Enter numbers: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/*
void Board::displayPoint(int x, int y){
    bool blank = false;
    if(game[x][y] == 0){
        blank = true;
    }
    if(blank == false){
        cout << "Showing point: " << "\033[33m(" << x << "," << y << ") " << game[x][y] << "\033[0m\n";
    }else{
        cout << "Showing point: " << "\033[33m(" << x << "," << y << ") " << "?" << "\033[0m\n";
    }
}
*/

/*
void Board::moveAround(){
    int x, y, n;
    bool game = true; // test bool 

    while(game){
        cout << "Enter point to edit? (Enter x and y): ";
        if(cin >> x >> y){
            if(x >= 0 || y >= 0 || x <= 8 || y <= 8){
                displayPoint(x, y);
                editValues(x, y);
            }else{
                cout << "Enter number from 0 - 8: ";
            }
        }else{
            cout << "Enter numbers: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; // tempoary for debugging
        }
    }
}
*/

void Board::Game() {
    Display();
    //set to 0,0 default
    //displayPoint(0,0);
    //moveAround();
}

void Board::endGame() {
    for (int i = 0; i < rows; ++i) {
        delete[] game[i];
    }
    delete[] game;
    game = nullptr;
}

int main() {
    Board b;
    b.Game();
    b.endGame();
    b.rowCheck();
    return 0;
}
