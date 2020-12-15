/*
Advent of Code 2020 Day 5
v1, Last Modified: 2020-12-13
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void fileLogistics(vector<string>&);

struct Range {
    int start;
    int end;
};

struct Passes {
    int row;
    int column;
    int seatID = row * column;
};

int main(){
    vector <string> input;
    fileLogistics(input);
    /*
     FBFBBFFRLR
     Start by considering the whole range, rows 0 through 127.
     
     F means to take the lower half, keeping rows 0 through 63.
     B means to take the upper half, keeping rows 32 through 63.
     F means to take the lower half, keeping rows 32 through 47.
     B means to take the upper half, keeping rows 40 through 47.
     B keeps rows 44 through 47.
     F keeps rows 44 through 45.
     The final F keeps the lower of the two, row 44.
     */
    

    
    string test = "FBFBBFF";
    
    Range crr;
    
    crr.start = 0;
    crr.end = 127;
    
    for (int i = 0 ; i < test.size(); i++){
        
        if (test[i] == 'F'){
            // end = 63
            // start = 32
            crr.end = (crr.end + crr.start) / 2;
            cout << "F @ index " << i << " crr.start=" << crr.start << " crr.end=" << crr.end << endl;
        }
        else if (test[i] == 'B'){
            // start = 32
            // end = 47
            
            // need: start = 40. end = 47
            crr.start = ((crr.end + crr.start) / 2) + 1;
            cout << "B @ index " << i << " crr.start=" << crr.start << " crr.end=" << crr.end << endl;
        }
    }
    
    cout << endl;
    /*
    RLR:
    Start by considering the whole range, columns 0 through 7.
     
    R means to take the upper half, keeping columns 4 through 7.
    L means to take the lower half, keeping columns 4 through 5.
    The final R keeps the upper of the two, column 5.
     */
    string test2 = "RLR";
    Range ccr;
    ccr.start = 0;
    ccr.end = 7;
    for (int i = 0 ; i < test2.size(); i++){
        
        if (test2[i] == 'L'){
            // end = 63
            // start = 32
            ccr.end = (ccr.end + ccr.start) / 2;
            cout << "L @ index " << i << " ccr.start=" << ccr.start << " ccr.end=" << ccr.end << endl;
        }
        else if (test2[i] == 'R'){
            ccr.start = ((ccr.end + ccr.start) / 2) + 1;
            cout << "R @ index " << i << " ccr.start=" << ccr.start << " ccr.end=" << ccr.end << endl;
        }
    }
    
    return 0;
}

void fileLogistics(vector<string>& input){
    ifstream fin;
    string line;

    fin.open("input.txt");
    
    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        //cout << line << endl;
        input.push_back(line);
        
    }
    fin.close();
}
