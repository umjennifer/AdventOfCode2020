/*
    Jennifer Um
    Advent of Code Day 3
    v1.3, 2020-12-25
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
int partOne(vector<string>, int, int);


int main(){
    string filename = "input.txt";
    vector<string> inputVector;
    saveInputInVector(filename, inputVector);
    
    int product = 1;
//    cout << partOne(inputVector, 1, 1) << endl;
//    cout << partOne(inputVector, 3, 1) << endl;
//    cout <<  partOne(inputVector, 5, 1) << endl;
//    cout <<  partOne(inputVector, 7, 1) << endl;
//    cout <<  partOne(inputVector, 1, 2) << endl;
    
    // partOne(inputVector, right_step, down_step);
    product *= partOne(inputVector, 1, 1);
    product *= partOne(inputVector, 3, 1);
    product *= partOne(inputVector, 5, 1);
    product *= partOne(inputVector, 7, 1);
    product *= partOne(inputVector, 1, 2);

    cout << "What do you get if you multiply together the number of trees encountered on each of the listed slopes? \nAnswer:" << product << endl;
    
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

int partOne(vector<string> inputVector, int right_step, int down_step){
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
    int row = 0;
    int bounds_adjust = right_step - 1;
    
    int total_trees = 0;
    
    for (int i = 0; i < matrix_rows; i++){
        
        if (row + down_step > matrix_rows){
            break;
        }
        else {
            row += down_step;
        }
        
        int largest_index = matrix_cols - 1;
        //cout << "row:" << row << " ";
        
        if ((col + right_step) > largest_index){ // 8+3 > 10
            col = (col - (largest_index)) + bounds_adjust;
            //cout << "col:" << col << " ";
        }
        else {
            col += right_step;
            //cout << "col:" << col << " ";
        }
        
        // determine symbol given row and col
        char symbol = matrix_template[row][col];
        //cout << "symbol:" << symbol << endl;
        if (symbol == '#'){
            total_trees++;
        }
        
    }
    //cout << "total trees: " << total_trees << endl;
    return total_trees;
}
