#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <algorithm>

using namespace std;

vector<int> findTwoValues(vector<int> nums){
  // for value at start of vector
  for (int i = 0; i < nums.size(); i++){
    // for value at end of vector
    for (int j = (nums.size()-1); j >= 0 ; j--){
      if (nums[j] == 2020 - nums[i]){
        //cout << "i: " << i<< ", nums[i]: " << nums[i] << endl;
        //cout << "j: " << j<< ", nums[j]: " << nums[j] << endl;
        vector<int> result;
        result.push_back(nums[i]);
        result.push_back(nums[j]);
        return result;
      }
    }
  }
}

vector<int> findThreeValues(vector<int> nums){
  // for value at start of vector
  for (int i = 0; i < nums.size(); i++){
    // for value at end of vector
    for (int j = 0; j < nums.size(); j++){ 

      for (int k = (nums.size()-1); k >= 0 ; k--){
        if (nums[k] == 2020 - nums[i] - nums[j]){
          //cout << "i: " << i<< ", nums[i]: " << nums[i] << endl;
          //cout << "j: " << j<< ", nums[j]: " << nums[j] << endl;
          //cout << "k: " << j<< ", nums[k]: " << nums[k] << endl;
          vector<int> result;
          result.push_back(nums[i]);
          result.push_back(nums[j]);
          result.push_back(nums[k]);
          return result;
        }
      }
    }
  }
}

int main() {
  ifstream fin;
  string line;
  vector<int> nums;

  fin.open("input.txt");

  while(!fin.eof()) {

    // read lines from file
    getline(fin,line);

    stringstream linestream(line);

    int num = stoi(line);
    nums.push_back(num);
  }
  fin.close();

  sort(nums.begin(), nums.end());
  // Part 1
  vector<int> part1 = findTwoValues(nums); 
  cout << "Advent of Code 2020 Day 1 Part 1 Answer: " << part1[0] * part1[1] << endl;

  // Part 2
  vector<int> part2 = findThreeValues(nums);
  cout << "Advent of Code 2020 Day 1 Part 2 Answer: " << part2[0] * part2[1] * part2[2] << endl;

  return 0;
}
