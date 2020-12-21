#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

void fill_slope_from_file(bool slope[][31]) {
    string line;
    ifstream myfile("foo.txt");
    int line_num = 0;
    while (getline(myfile, line)) {
        for (int i=0; i<line.size(); i++){
            if (line[i] == '#'){
                slope[line_num][i] = true;
            }
        }
        line_num++;
    }
}
int how_many_trees_will_i_hit(bool slope[][31], int right_shift, int down_shift){
    int count = 0;
    int line_num = 0;
    int units_right = 0;
    while (line_num < 323){
        if (slope[line_num][units_right % 31]) count++;
        line_num += down_shift; units_right += right_shift;
    }

    return count;
}


int main() {
    bool slope[323][31] = { 0 };
    fill_slope_from_file(slope);
    cout << how_many_trees_will_i_hit(slope, 1, 1) << endl;
    cout << how_many_trees_will_i_hit(slope, 3, 1) << endl;
    cout << how_many_trees_will_i_hit(slope, 5, 1) << endl;
    cout << how_many_trees_will_i_hit(slope, 7, 1) << endl;
    cout << how_many_trees_will_i_hit(slope, 1, 2) << endl;
}
