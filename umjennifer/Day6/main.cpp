/*
Advent of Code 2020 Day 6
v1, Last Modified: 2020-12-15
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
    
    vector<string> answer_strings;

    //Part2
    
    vector<vector<string>> groupanswers;
    for (int i = 0; i < ranges.size(); i++){
        
        vector<string> individualanswers;
        for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
            individualanswers.push_back(input.at(j));
        }
        groupanswers.push_back(individualanswers);
        //allanswers.push_back(groupanswers);
    }
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    int yes_question_quorum = 0;
    for (int i = 0; i < groupanswers.size(); i++){ // to iterate through a group
        if (groupanswers.at(i).size() == 1){
            yes_question_quorum++;
        }
        else {
            //for all letters in the alphabet
            for (int j = 0 ; j < alphabet.length() ; j++){
                // itr: letter a
                // int: letter occur
                char letter = alphabet[j];
                int letter_occur = 0;
                // for all answers in a group
                for (int k = 0; k < groupanswers.at(i).size(); k++){
                    if (groupanswers.at(i).at(k).find(letter)){
                        // if a is in the answer string, +1 letter occur
                        letter_occur++;
                    }
                    if (letter_occur == groupanswers.at(i).size()){
                        //if letter occur = num answers in group, yes_question_quorum++
                        yes_question_quorum++;
                    }
                    
                }

            }


        }
    }
    cout << "yes_question_quorum" << yes_question_quorum << endl;

  /*
    for (int i = 0; i < ranges.size(); i++){
        //cout << "index i = " << i << endl;
        string answer_string;
        for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
            answer_string = answer_string + input.at(j) + ",";
        }
        answer_string.pop_back();
        answer_strings.push_back(answer_string);
    }*/
    
    /*
    for (auto& i : answer_strings){
        cout << i << endl;
    }*/
    

    
    
    
//Part1
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
