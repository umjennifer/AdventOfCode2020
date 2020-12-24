#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;


class BoardingPass {
    private:
        int row;
        int aisle;
    public:
        BoardingPass(int row, int aisle);
        int score();
};


BoardingPass::BoardingPass(int row, int aisle) {
    this->row = row;
    this->aisle = aisle;
}


int BoardingPass::score() {
    return ((8 * this->row) + this->aisle);
}


vector<string>* get_input_lines() {
    vector<string>* v = new vector<string>;
    string line;
    ifstream myfile("foo.txt");
    while (getline(myfile, line)) {
        v->push_back(line);
    }
    return v;
}


int row_from_back_front(string back_front) {
    int row = 0;
    int bitshift = 6;
    for (char ch:back_front) {
        if (ch == 'B') {
            row ^= (1 << bitshift);
        }
        bitshift--;
    }
    return row;
}


int aisle_from_left_right(string left_right) {
    int aisle = 0;
    int bitshift = 2;
    for (char ch:left_right) {
        if (ch == 'R') {
            aisle ^= (1 << bitshift);
        }
        bitshift--;
    }
    return aisle;
}


BoardingPass* bp_from_line(string line) {
    string row_specifier = line.substr(0,7);    
    string aisle_specifier = line.substr(7);    
    int row = row_from_back_front(row_specifier);
    int aisle = aisle_from_left_right(aisle_specifier);
    return new BoardingPass(row, aisle);
}


vector<BoardingPass*>* convert_lines_to_boarding_passes(vector<string>* input_lines) {
    vector<BoardingPass*>* bps = new vector<BoardingPass*>;
    for (auto line : *input_lines) {
        bps->push_back(bp_from_line(line));
    }
    return bps;
}


void find_highest_boarding_pass() {
    vector<string>* input_lines = get_input_lines();
    vector<BoardingPass*>* bps = convert_lines_to_boarding_passes(input_lines);
    int high_score = -1;
    int current_score = -1;
    for (auto bp : *bps) {
        current_score = bp->score();
        if (current_score > high_score) {
            high_score = current_score;
        }
    }
    cout << "High score: " << high_score << endl;
}


void find_muh_seat() {
    vector<string>* input_lines = get_input_lines();
    vector<BoardingPass*>* bps = convert_lines_to_boarding_passes(input_lines);
    unordered_set<int> s;
    // add all possible IDs to the set
    for (int id = 0; id < (128*8) ; id++) {
        s.insert(id);
    }
    // delete the IDs that I have
    for (BoardingPass* bp: *bps) {
        s.erase(bp->score());
    }
    // delete the leading IDs starting from 0
    for (int id = 0; id < (128*8) ; id++) {
        if (s.count(id) == 0) break;
        s.erase(id);
    }
    // delete the trailing IDs starting from 0
    for (int id = (128*8) -1; id > 0; id--) {
        if (s.count(id) == 0) break;
        s.erase(id);
    }
    // print what's left
    for (auto i : s) {
        cout << i << endl;
    }
}

int main() {
    // find_highest_boarding_pass();
    find_muh_seat();
}
