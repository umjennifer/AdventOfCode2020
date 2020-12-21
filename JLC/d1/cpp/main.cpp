#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void fill_vector_from_file(vector<int>* vec_p) {
    ifstream myfile("foo.txt");
    string line;
    while ( getline(myfile, line)) {
        vec_p->push_back(stoi(line));
    }
}


void find_three_that_add_to(vector<int>* vec_p, int sum_to){
    unordered_map<int, int> um = unordered_map<int, int>();
    for (int num=0; num < vec_p->size(); num++){
        um[vec_p->at(num)] = num;
    }
    for (int i=0; i < vec_p->size(); i++){
        for (int j=0; j < vec_p->size(); j++){
            if (i != j){
                const int partial_sum = vec_p->at(i) + vec_p->at(j);
                const int look_for = sum_to - partial_sum;
                try{
                    const int index = um.at(look_for);
                    if (index == i || index == j){
                        continue;
                    }
                    cout << vec_p->at(i) << " + " << vec_p->at(j) << " + " << look_for << " = " << sum_to
                    << " -> " << vec_p->at(i) * vec_p->at(j) * look_for << endl;
                }
                catch(const out_of_range){
                    continue;
                }
            }
        }
    }

}


void find_two_that_add_to(vector<int>* vec_p, int sum_to){
    unordered_set<int> us = unordered_set<int>();
    for (int num : *vec_p){
        us.insert(num);
    }
    for (int num : *vec_p){
        int look_for = sum_to - num;
        if (us.count(look_for)){
            cout << look_for << "*" << num << " = " << look_for * num << endl;
        }
    }
}


int main() {
    vector<int> theVec;
    fill_vector_from_file(&theVec);
    find_two_that_add_to(&theVec, 2020);
    cout << "________" << endl;
    find_three_that_add_to(&theVec, 2020);
}
