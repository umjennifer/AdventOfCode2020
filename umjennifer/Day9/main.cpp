//
//  main.cpp
//  Day 9
//
//  Created by Jennifer Um on 1/2/21.
//  Copyright © 2021 Jennifer Um. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Value {
    unsigned long long int val;
    int index_in_inputVector; // this will be the key in unordered map
    int preamble_start = 0;
    int preamble_end = 0;
    bool foundTwoPreambleValThatSumToThisVal = true;
};

void saveInputInVector(string, vector<unsigned long long int>&);
void populateDataInallValues(int, unordered_map<int, Value>&, vector<unsigned long long int>);
void printallValues(unordered_map<int, Value>);
void updateBool(unordered_map<int, Value>&, vector<unsigned long long int>);
void findFirstNumberWithoutProperty(unordered_map<int, Value>);

int main() {
    string filename = "input.txt";
    vector<unsigned long long int> inputVector;
    saveInputInVector(filename, inputVector);
    
//    for (int i = 0; i < inputVector.size(); i++){
//        cout << inputVector.at(i) << endl;
//    }
    
    int preamble_len = 25;
    unordered_map <int, Value> allValues;
    populateDataInallValues(preamble_len, allValues, inputVector);
    updateBool(allValues, inputVector);
    //printallValues(allValues);
    findFirstNumberWithoutProperty(allValues);
    
}

void saveInputInVector(string filename, vector<unsigned long long int>& inputVector){
    ifstream fin;
    string line;

    fin.open(filename);

    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        cout << line << endl;
        inputVector.push_back(stoull(line));
    }
    fin.close();
}

void populateDataInallValues(int preamble_len, unordered_map<int, Value>& allValues, vector<unsigned long long int> inputVector){
    for (int i = preamble_len; i < inputVector.size(); i++){
        Value this_val;
        this_val.val = inputVector.at(i);
        this_val.index_in_inputVector = i;
        this_val.preamble_start = i - preamble_len;
        this_val.preamble_end = i - 1;
        allValues[i] = this_val;
    }
}

void printallValues(unordered_map<int, Value> allValues){
    for (auto value : allValues){
        Value* ptr = &value.second;
        cout << "i in allValues=" << value.first << " value=" << ptr->val << " preambleStart=" << ptr->preamble_start << " preambleEnd=" << ptr->preamble_end << " foundTwoPreambleValThatSumToThisVal=" << ptr->foundTwoPreambleValThatSumToThisVal << endl;
    }
}

void updateBool(unordered_map<int, Value>& allValues, vector<unsigned long long int> inputVector){
    for (auto value : allValues){
//        Value* ptr = &value.second;
//        for (int i = ptr->preamble_start; i < ptr->preamble_end; i++){
//        }
        
        int count_foundTwoPreambleValThatSumToThisVal = 0;
        
        Value* ptr = &value.second;
        cout << "val= " << ptr-> val << endl;
        for (int i = ptr->preamble_start; i < ptr->preamble_end; i++){
            for (int j = ptr->preamble_end; j > ptr->preamble_start; j--){
                //cout << "i=" << i << ",val@i=" << inputVector.at(i) << " j=" << j << ",val@j=" << inputVector.at(j) << " sum=:" << inputVector.at(i) + inputVector.at(j) << endl;
                
                if (inputVector.at(i) + inputVector.at(j) == ptr->val){
                    count_foundTwoPreambleValThatSumToThisVal++;
                }
            }
        }
        if (count_foundTwoPreambleValThatSumToThisVal == 0){
            allValues[value.first].foundTwoPreambleValThatSumToThisVal = false;
        }
        //cout << endl;
    }
}

void findFirstNumberWithoutProperty(unordered_map<int, Value> allValues){
    for (auto value : allValues){
        Value* ptr = &value.second;
        if (ptr->foundTwoPreambleValThatSumToThisVal == false){
            cout << "Number w/o this property=" << ptr->val << endl;
        }
    }
}
