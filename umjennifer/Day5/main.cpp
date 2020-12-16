/*
Advent of Code 2020 Day 5
v1, Last Modified: 2020-12-15
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

struct BoardingPass {
    int row;
    int column;
    //int seatID = (row * 8) + column;
    int seatID;
};

int main(){
    vector <string> input;
    fileLogistics(input);
    vector<BoardingPass> passes;
    
/******************************** Part 1; ******************************/
    for (int i = 0; i < input.size(); i++){
        BoardingPass curr_pass;
        string this_pass = input.at(i);
        
        // current row range
        Range crr;
        crr.start = 0;
        crr.end = 127;
        for (int j = 0; j < 7; j++){ // check row
            if (this_pass[j] == 'F'){
                crr.end = (crr.end + crr.start) / 2;
                //cout << "F @ index " << j << " crr.start=" << crr.start << " crr.end=" << crr.end << endl;
            }
            else if (this_pass[j] == 'B'){
                crr.start = ((crr.end + crr.start) / 2) + 1;
                //cout << "B @ index " << j << " crr.start=" << crr.start << " crr.end=" << crr.end << endl;
            }
        }
        
        // current column range
        Range ccr;
        ccr.start = 0;
        ccr.end = 7;
        for (int k = 7; k < this_pass.size(); k++){
            
            if (this_pass[k] == 'L'){
                ccr.end = (ccr.end + ccr.start) / 2;
                //cout << "L @ index " << k << " ccr.start=" << ccr.start << " ccr.end=" << ccr.end << endl;
            }
            else if (this_pass[k] == 'R'){
                ccr.start = ((ccr.end + ccr.start) / 2) + 1;
                //cout << "R @ index " << k << " ccr.start=" << ccr.start << " ccr.end=" << ccr.end << endl;
            }
        }
        //cout << endl << endl;
        curr_pass.row = crr.start;
        curr_pass.column = ccr.start;
        curr_pass.seatID = (curr_pass.row * 8) + curr_pass.column;
        passes.push_back(curr_pass);
    }
    
    int max_seatid = passes.at(0).seatID;
    for (int i = 0; i < passes.size(); i++){
        //cout << "pass" << i << " row=" << passes.at(i).row << " col=" << passes.at(i).column << " seatid=" << passes.at(i).seatID << endl;
        if (passes.at(i).seatID > max_seatid){
            max_seatid = passes.at(i).seatID;
        }
    }
    
    //cout << "max seat id = " << max_seatid << endl;
    

/******************************** Part 2; ******************************/
    //cout << passes.size() << endl;
    
    vector<int> seatIDs;
    
    for (int i = 0; i < passes.size(); i++){
        seatIDs.push_back(passes.at(i).seatID);
        }
    
    sort(seatIDs.begin(), seatIDs.end());
    
    vector<int> seats_template;
    vector<int> missing_seats;
    
    for (int i = seatIDs.at(0); i < seatIDs.at(seatIDs.size()-1); i++){
        seats_template.push_back(i);
    }
    
    /*
    for (int i = 0; i < seats_template.size(); i++){
        cout << seats_template.at(i) << endl;
    }
    cout << "size: " << seats_template.size() << endl;
    */
     
    for (int i = 0; i < seats_template.size(); i++){
        // if seatId at that index is not in seats_template
        if (find(seatIDs.begin(), seatIDs.end(), seats_template.at(i)) == seatIDs.end()){
            cout << "missing: " << seats_template.at(i) << endl;
            missing_seats.push_back(seats_template.at(i));
        }
        //cout << seatIDs.at(i) << endl;
    }
    
    for (int i = 0; i < missing_seats.size(); i++){
        cout << "missing: " << missing_seats.at(i) << endl;
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
