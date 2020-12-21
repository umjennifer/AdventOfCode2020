#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

struct PasswordAndPolicy {
    int min;
    int max;
    char c;
    string password;
};


PasswordAndPolicy get_password_and_policy_from_line(regex policy, string line){
    struct PasswordAndPolicy pp;
    smatch match;
    regex_search(line, match, policy);
    if (match.size() != 5) {
        throw "Regex found an incorrect number";
    }
    pp.min = stoi(match.str(1));
    pp.max = stoi(match.str(2));
    pp.c = match.str(3)[0];
    pp.password = match.str(4);
    return pp;
}

bool valid_password_1(PasswordAndPolicy pp){
    int count = 0;
    for (int i = 0; i < pp.password.size(); i++){
        if (pp.password[i] == pp.c){
            count++;
        }
    }
    return (count <= pp.max && count >= pp.min);
}


bool valid_password_2(PasswordAndPolicy pp){
    return (pp.password[pp.min - 1] == pp.c ^ pp.password[pp.max - 1] == pp.c);
}


void count_valid_passwords_from_file() {
    string line;
    int p1 = 0;
    int p2 = 0;
    regex policy("(\\d{1,3})-(\\d{1,3}) (\\D): (\\S*)");
    ifstream myfile("foo.txt");
    while (getline(myfile, line)) {
        PasswordAndPolicy pp = get_password_and_policy_from_line(policy, line);
        if (valid_password_1(pp)) p1++;
        if (valid_password_2(pp)) p2++;
    }
    cout << p1 << " " << p2;
}


int main() {
    count_valid_passwords_from_file();
}
