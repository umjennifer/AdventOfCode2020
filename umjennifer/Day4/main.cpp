/*
 Advent of Code 2020 Day 4
 v1, Last Modified: 2020-12-09
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct linesRange {
    int start;
    int end;
};

int main() {
    vector <string> input;
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
    
    // create vector of empty lines
    vector<int> emptyLines;
    for (int i = 0; i < input.size(); i++){
        if (input.at(i).empty()){
            //cout << "Empty line at: " << i << endl;
            emptyLines.push_back(i);
        }
    }
    
    /*
    for (int i = 0; i < emptyLines.size(); i++){
        cout << "index = " << i << " Empty line in vector input @ " << emptyLines.at(i) << endl;
    }
     */
    
    // Populate vector of ranges
    vector<linesRange> ranges;
    // Populate vector of ranges with first range
    linesRange first_range;
    first_range.start = 0;
    first_range.end = emptyLines.at(0) - 1;
    ranges.push_back(first_range);
    //cout << "ranges[0].start = " << ranges[0].start << endl;
    //cout << "ranges[0].end = " << ranges[0].end << endl;
    
    // populate vector of ranges with all but the last range
    for (int i = 0; i < emptyLines.size() - 1; i++){
        linesRange curr_range;
        curr_range.start = emptyLines.at(i) + 1;
        curr_range.end = emptyLines.at(i+1) - 1;
        ranges.push_back(curr_range);
    }
    // populate vector of ranges with the last range
    linesRange last_range;
    last_range.start = emptyLines.at(emptyLines.size() - 1) + 1;
    last_range.end = input.size() - 1;
    ranges.push_back(last_range);
    
    
    vector<string> passport_strings;
    for (int i = 0; i < ranges.size(); i++){
        //cout << "curr range: start=" << ranges.at(i).start << " end=" << ranges.at(i).end << endl;
    }
    
    for (int i = 0; i < ranges.size(); i++){
        //cout << "index i = " << i << endl;
        string passport_string;
        for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
            passport_string = passport_string + input.at(j) + " ";
        }
        passport_string.pop_back(); // erase space at end of the string
        passport_strings.push_back(passport_string);
    }
    
    /*
    for (int i = 0; i < passport_strings.size(); i++){
        cout << passport_strings.at(i) << endl;
    }
     */
    

    vector<string> fieldsToCheck = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
    
    vector<string> fieldsPerPassport;
    vector<vector<string>> vOfFieldsPerPassport;
        
    for (int i = 0; i < passport_strings.size(); i++){ // for each line
        stringstream linestream(passport_strings.at(i)); // save each line as string stream
        

        while (!linestream.eof()){ // for each string stream
            string s;
            getline(linestream,s,' '); // get portion of string stream and save as string s
            string key = s.substr(0,3);
            fieldsPerPassport.push_back(key);
        }
        vOfFieldsPerPassport.push_back(fieldsPerPassport);
        fieldsPerPassport.clear();
        //cout << endl;
    }
    int numInvalidPassports = 0;
    for (int i = 0; i < vOfFieldsPerPassport.size(); i++){
        //cout << vOfFieldsPerPassport[i].size() << endl;
        
        if (vOfFieldsPerPassport[i].size() < fieldsToCheck.size()){ // if passport contains less than 8 fields
            //cout << vOfFieldsPerPassport[i].size() << endl;
            
            if  (vOfFieldsPerPassport[i].size() == 7){ // if passport contains exactly 7 fields
                if (find(vOfFieldsPerPassport[i].begin(), vOfFieldsPerPassport[i].end(), "cid") == vOfFieldsPerPassport[i].end()){ // if cid is not in vOfFieldsPerPassport[i]
                    // do nothing
                    //cout << "i =" << i << "7 Fields, missing cid: " << passport_strings.at(i) << endl;
                } else { // else, if passport contains exactly 7 fields and is missing something else,
                    numInvalidPassports++;
                    cout << "i =" << i << "7 Fields, missing something else: " << passport_strings.at(i) << endl;
                }
            } else { // if passport size is any other size (less than 7)
                numInvalidPassports++;
                cout << "i =" << i << "Less than 7 fields: " << passport_strings.at(i) << endl;
            }
            
        }
        
    }
    int numValidPassports = passport_strings.size() - numInvalidPassports;
    cout << "numInvalidPassports: " << numInvalidPassports << endl;
    cout << "numValidPassports: " << numValidPassports << endl;
  
}
