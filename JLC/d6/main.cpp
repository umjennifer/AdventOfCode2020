#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;


vector<string>* get_lines_from_file(string filename) {
    ifstream myfile(filename);
    string line;
    vector<string>* v = new vector<string>;
    while (getline(myfile, line)) {
        v->push_back(line);
    }
    return v;
}


void parse_lines_p1(vector<string>* lines) {
    int count = 0;
    unordered_set<char> set = unordered_set<char>();
    for (string line : *lines) {
        if (line == ""){
            cout << set.size() << endl;
            count += set.size();
            set.clear();
            continue;
        }
        for (char c : line) {
            set.insert(c);
        }
    }
    cout << count << endl;
}


int main() {
    vector<string>* lines = get_lines_from_file("foo.txt");
    lines->push_back("");
    parse_lines_p1(lines);
}
