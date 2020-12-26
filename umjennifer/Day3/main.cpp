/*
    Jennifer Um
    Advent of Code Day 3
    v1.2, 2020-12-25
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Coordinate {
    int x = 0;
    int y = 0;
};

void saveInputInVector(string, vector<string>&);
void outputMatrix(char *arr, unsigned long rows, unsigned long cols);


int main(){
    string filename = "input.txt";
    vector<string> inputVector;
    saveInputInVector(filename, inputVector);
    
    
    // create matrix_template
    unsigned long matrix_rows = inputVector.size();
    unsigned long matrix_cols = inputVector.at(0).size();
    char matrix_template[matrix_rows][matrix_cols];
    // populate matrix_template with vals from inputVector
    for (int i = 0; i < inputVector.size(); i++){
        for (int j = 0; j < inputVector.at(i).size(); j++){
            matrix_template[i][j] = inputVector.at(i).at(j);
        }
    }
    
    //outputMatrix((char *)matrix_template, matrix_rows, matrix_cols);
    
    int col = 0;
    int right_step = 3;
    int down_step = 1;
    int bounds_adjust = right_step - 1;
    
    int total_trees = 0;
    
    for (int i = 0; i < matrix_rows; i++){
        int row = i+down_step;
        int largest_index = matrix_cols - 1;
        cout << "row:" << row << " ";
        
        if ((col + right_step) > largest_index){ // 8+3 > 10
            col = (col - (largest_index)) + bounds_adjust;
            cout << "col:" << col << " ";
        }
        else {
            col += right_step;
            cout << "col:" << col << " ";
        }
        
        // determine symbol given row and col
        char symbol = matrix_template[row][col];
        cout << "symbol:" << symbol << endl;
        if (symbol == '#'){
            total_trees++;
        }
        
    }
    
    cout << "total trees: " << total_trees << endl;
    

    

}

void saveInputInVector(string filename, vector<string>& inputVector){
    ifstream fin;
    string line;

    fin.open(filename);

    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        inputVector.push_back(line);
    }
    fin.close();
}

void outputMatrix(char *arr, unsigned long rows, unsigned long cols){
    //output the matrix
    for (int i = 0; i < rows; i++){
        for (int j = 0; j< cols; j++){
            cout<<*((arr+i*cols) + j);
        }
        cout << endl;
    }
}
