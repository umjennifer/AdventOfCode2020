// https://adventofcode.com/2020/day/2#part1
// https://adventofcode.com/2020/day/2#part2

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <string>

using namespace std;

struct Password {
  // TODO: UPDATE THESE TWO INTS NAMES
  int lowest_appearance;
  int highest_appearance;
  char letter;
  string pw_string;
};

void populatePasswords(ifstream&, vector<Password>&);
void part1(vector<Password>);
void part2(vector<Password>);

int main() {
  int valid;
  vector<Password> passwords;
  
  ifstream fin;
  string file = "input.txt";
  fin.open(file);

  populatePasswords(fin, passwords);
  //part1(passwords);
  part2(passwords);



  return 0;
}

void populatePasswords(ifstream& fin, vector<Password>& passwords){
  string line;

  //2-5 h: lcwghhkpkxvzkvrmxrv
  Password curr_password;
  string str_lowest;
  string str_highest;
  string str_letter;
  string pw;

  while (!fin.eof()) {
    getline(fin, line);
    stringstream lineStream(line);

    getline(lineStream, str_lowest, '-');
    getline(lineStream, str_highest, ' ');
    getline(lineStream, str_letter, ':');
    getline(lineStream,pw);
    pw.erase(0,1); // erase " " at the start of the string

    curr_password.lowest_appearance = stoi(str_lowest);
    curr_password.highest_appearance = stoi(str_highest);
    curr_password.letter = str_letter[0];
    curr_password.pw_string = pw;

    passwords.push_back(curr_password);
  }
}

void part1(vector<Password> passwords){
  int valid = 0;
  for (int i = 0; i < passwords.size(); i++){
    int letter_count = 0;
    cout << "letter: " << passwords[i].letter << " ";
    for (int j = 0; j < passwords[i].pw_string.length(); j++){
      cout << passwords[i].pw_string[j];
      if (passwords[i].pw_string[j] == passwords[i].letter){
        letter_count++;
      }
      
    }
    cout << " Count: " << letter_count;

    if (letter_count >= passwords[i].lowest_appearance && letter_count <= passwords[i].highest_appearance){
      cout << " VALID" << endl;
      valid++;
    } else {
      cout << endl;
    }
  }
  cout << "Total valid: " << valid << endl;
}
/*
1-3 a: [a]b[c]de is valid: position 1 contains a and position 3 does not.
1-3 b: [c]d[e]fg is invalid: neither position 1 nor position 3 contains b.
2-9 c: c[c]cccccc[c] is invalid: both position 2 and position 9 contain c.
*/
void part2(vector<Password> passwords){
  int valid = 0;
  
  for (int i = 0; i < passwords.size(); i++){
    int letter_count = 0;

    cout << "Letter: " << passwords[i].letter <<", ";
    cout << "first: " << passwords[i].lowest_appearance << ", second: " << passwords[i].highest_appearance << endl;

    int ind1 = passwords[i].lowest_appearance- 1;
    int ind2 = passwords[i].highest_appearance- 1;

    // TODO: check that first num is in bounds
    //if (passwords[i].pw_string[ind1] <= passwords[i].pw_string.length()){
      if (passwords[i].pw_string[ind1] == passwords[i].letter){
        letter_count++;
        cout << "Letter found in first place!" << endl << endl;
      }
    //}

    // TODO: check that second num is in bounds
    //if (passwords[i].pw_string[ind2] <= passwords[i].pw_string.length()){
      if (passwords[i].pw_string[ind2] == passwords[i].letter){
        letter_count++;
        cout << "Letter found in second place!" << endl << endl;
      } 
    //}
    
    if (letter_count == 1){
      valid++;
    }
  }
  cout << "Total valid: " << valid << endl;
}
