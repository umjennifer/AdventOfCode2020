/*
 Advent of Code Day 7
 v1.5 2020-12-23
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct Bag {
    string color;
    vector<Bag> fitsInto;
    vector<Bag> canContain;
    // TODO: specify
    int quantity;
};

void saveInputInVector(string, vector<string>&);
void standardizeStrings(vector<string>&);
void eraseSubstring(string& , string);
void replaceSubstring(string& , string, string);
    
int main(){
    string filename = "input.txt";
    vector<string> inputVector;
    
    saveInputInVector(filename, inputVector);
    standardizeStrings(inputVector);
    for (int i = 0; i < inputVector.size(); i++){
        cout << inputVector.at(i) << endl;
    }
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

void standardizeStrings(vector<string>& inputVector){

    for (int i = 0; i < inputVector.size(); i++){
        string* line = &inputVector.at(i);
        line->pop_back();
        
        replaceSubstring(*line, " bags contain no other bags", ":");
        eraseSubstring(*line, " bags");
        eraseSubstring(*line, " bag");
        replaceSubstring(*line, " contain ", ":");
        replaceSubstring(*line, ", ", ",");
        
    }
}

void eraseSubstring(string& line, string substring){
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop until nothing is found
    while ((pos = line.find(substring) )!= std::string::npos){
        // If found then erase it from string
        line.erase(pos, substring.length());
    }
}

void replaceSubstring(string& line, string to_replace, string replace_with){
    size_t index = 0;
    while (true) {
         /* Locate the substring to replace. */
         index = line.find(to_replace, index);
         if (index == std::string::npos) break;

         /* Make the replacement. */
        line.replace(index, to_replace.length(), replace_with);

         /* Advance index forward so the next iteration doesn't pick it up as well. */
         index += to_replace.length();
    }
}
