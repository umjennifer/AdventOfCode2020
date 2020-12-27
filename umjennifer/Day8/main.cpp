//
//  main.cpp
//  Day8
//
//  Created by Jennifer Um on 12/25/20.
//  Copyright © 2020 Jennifer Um. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

struct Instruction {
    string operation;
    int argument;
    bool hasRanAtLeastOnce = false;
};

void saveInputInVector(string, vector<string>&);
void populateAllInstructions(unordered_map<int, Instruction>&, vector<string>);
void printAllInstructions(unordered_map<int, Instruction>);
void partOneCalculateAccumulator(unordered_map<int, Instruction>&, int&);
void partTwoCalculateAccumulator(unordered_map<int, Instruction>&, int&);

int main() {
    string filename = "input.txt";
    vector<string> inputVector;
    saveInputInVector(filename, inputVector);
    int accumulator = 0;
    
    unordered_map<int, Instruction> allInstructions; // key=int index. value=instruction
    populateAllInstructions(allInstructions, inputVector);
    //printAllInstructions(allInstructions);
    //partOneCalculateAccumulator(allInstructions, accumulator);
    partTwoCalculateAccumulator(allInstructions, accumulator);
    cout << "accumulator: " << accumulator << endl;
    
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


void populateAllInstructions(unordered_map<int, Instruction>& allInstructions, vector<string> inputVector){
    for (int i = 0; i < inputVector.size(); i++){
        string line = inputVector.at(i);
        Instruction instruction;
        
        // get operation
        instruction.operation = line.substr(0,line.find(" "));
        //cout << "operation:" << instruction.operation << endl;
        
        // get argument
        string arg_string = line.substr(line.find(" ")+1);
        instruction.argument = stoi(arg_string);
        //cout << "argument string:" << arg << endl;
        //cout << "int:" << instruction.argument << endl;
        
        allInstructions[i] = instruction;
        
    }
}

void printAllInstructions(unordered_map<int, Instruction> allInstructions){
    for (auto instruction : allInstructions){
        Instruction* instruct_ptr = &instruction.second;
        cout << instruction.first << " " << instruct_ptr->operation << " " << instruct_ptr->argument << " " << instruct_ptr->hasRanAtLeastOnce << endl;
    }
}

void partOneCalculateAccumulator(unordered_map<int, Instruction>& allInstructions, int& accumulator){
    //cout << "accumulator: " << accumulator << endl;
    
    vector<int> instructionsExecuted;
    int i = 0;
    //Instruction curr_instruction = allInstructions[i];
    
    while (allInstructions[i].hasRanAtLeastOnce == false){
        instructionsExecuted.push_back(i);
        
        if (allInstructions[i].operation == "nop"){// if nop,
            allInstructions[i].hasRanAtLeastOnce = true;
            i++;
        }
        else if (allInstructions[i].operation == "jmp"){// else if jmp
            allInstructions[i].hasRanAtLeastOnce = true;
            i += allInstructions[i].argument;
        }
        else {  // if acc
            allInstructions[i].hasRanAtLeastOnce = true;
            accumulator += allInstructions[i].argument;
            i++;
        }
    }

    cout << "instructions executed: " << endl;
    for (int j = 0; j < instructionsExecuted.size(); j++){
        int allInstrutionsInd = instructionsExecuted.at(j);
        cout << "index: " << allInstrutionsInd << " | " << allInstructions[allInstrutionsInd].operation << " " << allInstructions[allInstrutionsInd].argument << endl;
    }
}

void partTwoCalculateAccumulator(unordered_map<int, Instruction>& allInstructions, int& accumulator){
    //cout << "accumulator: " << accumulator << endl;
    
    vector<int> instructionsExecuted;
    bool run = true;
    int i = 0;
    //Instruction curr_instruction = allInstructions[i];
    
    while (allInstructions[i].hasRanAtLeastOnce == false){
        if (allInstructions[i].operation == "nop"){// if nop,
            if (((i+1) + allInstructions[i + 1].argument) > allInstructions.size()){
                allInstructions[i].operation = "jmp";
                instructionsExecuted.push_back(i);
                i += allInstructions[i].argument;
                run = false;
            }
            else {
                i++;
            }
        }
        else if (allInstructions[i].operation == "jmp"){// else if jmp
            i += allInstructions[i].argument;
        }
        else {  // if acc
            accumulator += allInstructions[i].argument;
            i++;
        }
    }

    cout << "instructions executed: " << endl;
    for (int j = 0; j < instructionsExecuted.size(); j++){
        int allInstrutionsInd = instructionsExecuted.at(j);
        cout << "index: " << allInstrutionsInd << " | " << allInstructions[allInstrutionsInd].operation << " " << allInstructions[allInstrutionsInd].argument << endl;
    }

}
