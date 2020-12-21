/*
Advent of Code 2020 Day 6
v2, Last Modified: 2020-12-17
*/

#include <iostream>
#include <fstream>
#include <vector>
#include<set>
using namespace std;

struct linesRange {
    int start;
    int end;
};

int main(){
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
    
//Part2
    vector<vector<string>> groupanswers;
     for (int i = 0; i < ranges.size(); i++){
         vector<string> individualanswers;
         for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
             individualanswers.push_back(input.at(j));
         }
         groupanswers.push_back(individualanswers);
     }
    
    
    int yes_quorum = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < groupanswers.size(); i++){
        int answers_per_group = groupanswers.at(i).size();
        for (int k = 0; k < alphabet.size(); k++){
            char letter = alphabet[k];
            int letter_occurance_in_group = 0;
            //cout << "letter: " << letter << endl;
            for (int j = 0; j < groupanswers.at(i).size();j++){
                cout << groupanswers.at(i).at(j) << endl;
                size_t found = groupanswers.at(i).at(j).find(letter);
                if (found != string::npos){
                    //cout << "found letter " << letter << endl;
                    letter_occurance_in_group++;
                }
            }
            cout << letter << " count in group: " << letter_occurance_in_group << endl;
            if (answers_per_group == letter_occurance_in_group){
                yes_quorum++;
            }
        }
        //cout << "answers_per_group: " << answers_per_group << endl;
        cout << endl;
    }
    
    cout << "yes_quorum: " << yes_quorum << endl;
    
//Part1
//    vector<string> answer_strings;
//    for (int i = 0; i < ranges.size(); i++){
//        //cout << "index i = " << i << endl;
//        string answer_string;
//        for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
//            answer_string = answer_string + input.at(j);
//        }
//        answer_strings.push_back(answer_string);
//    }
//    int total_yes = 0;
//    for (int i = 0; i < answer_strings.size(); i++){
//        //cout << answer_strings.at(i) << endl;
//        string group_answers = answer_strings.at(i);
//        set<char> uniquecharsinline;
//        for (int j = 0; j < group_answers.length(); j++){
//            uniquecharsinline.insert(group_answers[j]);
//        }
//        total_yes += uniquecharsinline.size();
//
//        // print the characters in the set
//        /*
//        set<char, greater<char> >::iterator itr;
//        for (itr = uniquecharsinline.begin(); itr != uniquecharsinline.end(); ++itr){
//               cout << *itr;
//           }
//           cout << endl;
//        */
//
//    }
//    /*
//    for (int i = 0; i < uniqueAnswersPerLine.size(); i++){
//        cout << uniqueAnswersPerLine.at(i) << endl;
//    }*/
//    cout << "total yes: " << total_yes << endl;
    
    return 0;
}
