//
//  main.cpp
//  Day10
//
//  Created by Jennifer Um on 1/2/21.
//  Copyright © 2021 Jennifer Um. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

void saveInputInVectorSort(string filename, vector<int>& inputVector){
    ifstream fin;
    string line;

    fin.open(filename);

    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        //cout << line << endl;
        inputVector.push_back(stoi(line));
    }
    fin.close();
    sort(inputVector.begin(), inputVector.end()); //1 4 5 6 7 10 11 12 15 16 19
}

void populateAdaptersUsed(vector<int>& adaptersDeviceUsed, vector<int> inputVector, int deviceJoltage, int bound){
    adaptersDeviceUsed = {0};
    
//    for (int num : adaptersDeviceUsed){
//        cout << num << endl;
//    }
    int tracker = inputVector.at(0);
    int i = 0;
    while (tracker != deviceJoltage - bound){
        for (int j = 0; j <= bound; j++){
            // if element in vector
            if (find(inputVector.begin(), inputVector.end(), inputVector.at(i+j)) != inputVector.end()){
                adaptersDeviceUsed.push_back(inputVector.at(i+j));
                tracker = inputVector.at(i+j);
                cout << "pushed=" << inputVector.at(i+j) << " tracker=" << tracker << endl;
                break;
            }
        }
        i++;
    }
    adaptersDeviceUsed.push_back(deviceJoltage);
    for (int num : adaptersDeviceUsed){
        cout << num << " ";
    }
    cout << endl;
    
    int diff_one = 0;
    int diff_three = 0;
    for (int k=0; k < adaptersDeviceUsed.size()-1; k++){
        cout << "i=" << k << " val=" << adaptersDeviceUsed.at(k) << " nextval=" << adaptersDeviceUsed.at(k+1) << " difference=" << adaptersDeviceUsed.at(k+1)-adaptersDeviceUsed.at(k) << endl;
        if (adaptersDeviceUsed.at(k+1)-adaptersDeviceUsed.at(k) == 1){
            diff_one++;
        }
        if (adaptersDeviceUsed.at(k+1)-adaptersDeviceUsed.at(k) == 3){
            diff_three++;
        }
    }
    cout << "diff_one=" << diff_one << " diff_three=" << diff_three << endl;
    cout << "product=" << diff_three * diff_one << endl;
    
}


int main() {
    string filename = "input.txt";
    vector<int> inputVector;
    vector<int> adaptersDeviceUsed;
    int deviceJoltage;
    int bound = 3;
    
    saveInputInVectorSort(filename, inputVector);
    deviceJoltage = inputVector.at(inputVector.size()-1) + bound;
    
    for (int num : inputVector){
        cout << num << " ";
    }
    cout << endl;
    cout << "deviceJoltage=" << deviceJoltage << endl;
    
    populateAdaptersUsed(adaptersDeviceUsed, inputVector, deviceJoltage, bound);
    
    
}



