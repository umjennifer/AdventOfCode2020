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
void findFirstNumberWithoutProperty(unordered_map<int, Value>, unsigned long long int&);
void partTwofindContiguousVals(unsigned long long int, vector<unsigned long long int>, unordered_map<int, Value>);
void findIndexOfDesiredValue(unsigned long long int, int&, unordered_map<int, Value>);
void sumMinMax(vector<unsigned long long int>, vector<int>);

int main() {
    string filename = "input.txt";
    vector<unsigned long long int> inputVector;
    saveInputInVector(filename, inputVector);
    unsigned long long int first_num_wo_prop;
    
//    for (int i = 0; i < inputVector.size(); i++){
//        cout << inputVector.at(i) << endl;
//    }
    
    int preamble_len = 25;
    unordered_map <int, Value> allValues;
    populateDataInallValues(preamble_len, allValues, inputVector);
    updateBool(allValues, inputVector);
    //printallValues(allValues);
    findFirstNumberWithoutProperty(allValues, first_num_wo_prop);
    //cout << "Number w/o this property=" << first_num_wo_prop << endl;
    partTwofindContiguousVals(first_num_wo_prop, inputVector, allValues);
    
    
}

void saveInputInVector(string filename, vector<unsigned long long int>& inputVector){
    ifstream fin;
    string line;

    fin.open(filename);

    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        //cout << line << endl;
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
        //cout << "val= " << ptr-> val << endl;
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

void findFirstNumberWithoutProperty(unordered_map<int, Value> allValues, unsigned long long int& first_num_wo_prop){
    for (auto value : allValues){
        Value* ptr = &value.second;
        if (ptr->foundTwoPreambleValThatSumToThisVal == false){
            first_num_wo_prop = ptr->val;
        }
        
    }
}

void partTwofindContiguousVals(unsigned long long int desired_sum, vector<unsigned long long int> inputVector, unordered_map<int, Value> allValues){
    int index_of_desired_val;
    cout << "desired sum=" << desired_sum << endl;
    
    findIndexOfDesiredValue(desired_sum,index_of_desired_val, allValues);
    cout << "index_of_desired_val=" << index_of_desired_val << endl;

    for (int i = 0; i < index_of_desired_val; i++){ // start @ index 13, val = 182
        vector<int> range;
        for (int j = i; j < index_of_desired_val; j++){
            range.push_back(j);
            
            unsigned long long int total = 0;
            for (int elem : range){
                //cout << elem << " | total=";
                total += inputVector.at(elem);
                //cout << total << endl;
            }
//            cout << endl;
//            cout << " | total=" << total;
//            if (total == desired_sum){
//                cout << " DESIRED SUM IS HERE!" << endl;
//
//            }
//            else {
//                //cout << endl;
//            }
            
            if (total == desired_sum){
                cout << "Desired sum found=" << desired_sum << endl;
                sumMinMax(inputVector, range);

            }
        }
        //cout << endl;
    }
}

void findIndexOfDesiredValue(unsigned long long int desired_sum, int& index_of_desired_val,unordered_map<int, Value> allValues){
    // TODO: find key by value of struct, instead of iterating through unordered map
    for (auto value : allValues){
        Value* ptr = &value.second;
        if (ptr->val == desired_sum){
            index_of_desired_val = value.first;
        }
    }
}

void sumMinMax(vector<unsigned long long int> inputVector, vector<int> range){
    unsigned long long int min = inputVector.at(range.at(0));
    unsigned long long int max = inputVector.at(range.at(0));
    
    for (int i = 0; i < range.size(); i++){
        cout << "Values:" << inputVector.at(range.at(i)) << " " << endl;
        
        if (inputVector.at(range.at(i)) > max){
            max = inputVector.at(range.at(i));
        }
        if (inputVector.at(range.at(i)) < min){
            min = inputVector.at(range.at(i));
        }
    }
    cout << "Sum of largest and smallest values:" << min + max << endl;
}
