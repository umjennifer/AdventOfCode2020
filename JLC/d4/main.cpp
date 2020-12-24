#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;
regex hcl_re("(#[0-9a-f]{6})");
regex pid_re("([0-9]{9})");

class Passport {
    public:
        int byr = 0;
        int iyr = 0;
        int eyr = 0;
        string hgt = "";
        string hcl = "";
        string ecl = "";
        string pid = "";
        string cid = "";
        void set_byr(string input);
        void set_iyr(string input);
        void set_eyr(string input);
        void set_hgt(string input);
        void set_hcl(string input);
        void set_ecl(string input);
        void set_pid(string input);
        void set_cid(string input);
        void print();
};


void Passport::print() {
    cout << "PID: " << this->pid
         << "  BYR: " << this->byr
         << "  IYR: " << this->iyr
         << "  EYR: " << this->eyr
         << "  HCL: " << this->hcl
         << "  ECL: " << this->ecl
         << "  HGT: " << this->hgt
         << "  CID: " << this->cid
         << endl;
}
void Passport::set_byr(string input){
    int yr = 0;
    try { yr = stoi(input); }
    catch (invalid_argument ia) { return; }
    if (yr >= 1920 && yr <= 2002){
        this->byr = yr;
    }
}


void Passport::set_iyr(string input) {
    int yr = 0;
    try { yr = stoi(input); }
    catch (invalid_argument ia) { return; }
    if (yr >= 2010 && yr <= 2020){
        this->iyr = yr;
    }
}


void Passport::set_eyr(string input) {
    int yr = 0;
    try { yr = stoi(input); }
    catch (invalid_argument ia) { return; }
    if (yr >= 2020 && yr <= 2030){
        this->eyr = yr;
    }
}


void Passport::set_hgt(string input) {
    int i = input.size() - 2;
    string unit = input.substr(i);
    int height = 0;
    try { height = stoi(input.substr(0, i));}
    catch (invalid_argument ia) { return; }
    if (unit == "in") {
        if (height >= 59 && height <= 76) this->hgt = input;

    }
    else if (unit == "cm") {
        if (height >= 150 && height <= 193) this->hgt = input;
    }
}


void Passport::set_hcl(string input) {
    smatch match;
    regex_search(input, match, hcl_re);
    this->hcl = match.str(0);
}


void Passport::set_ecl(string input) {
    const string colors[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for (string c: colors){
        if (input == c){
            this->ecl = input;
        }
    }
}


void Passport::set_pid(string input) {
    smatch match;
    regex_search(input, match, pid_re);
    this->pid = match.str(0);
}


bool is_passport_valid(Passport* p) {
    return (
        (p->byr != 0)
        && (p->iyr != 0)
        && (p->eyr != 0)
        && (p->hgt != "")
        && (p->hcl != "")
        && (p->ecl != "")
        && (p->pid != "")
        // && (p->cid != "") optional
    );
}


regex passport_re("(\\w{3}):(\\S*)");


void add_to_passport(Passport* p, string line) {
    smatch match;
    while(regex_search(line, match, passport_re)){
        string key = match.str(1);
        string value = match.str(2);
        if (key =="byr") p->set_byr(value);
        if (key =="iyr") p->set_iyr(value);
        if (key =="eyr") p->set_eyr(value);
        if (key =="hgt") p->set_hgt(value);
        if (key =="hcl") p->set_hcl(value);
        if (key =="ecl") p->set_ecl(value);
        if (key =="pid") p->set_pid(value);
        if (key =="cid") p->cid = value;
        line = match.suffix().str();
    }
}


vector<Passport> generate_passports_from_file() {
    vector<Passport> pv;
    string line;
    ifstream myfile("foo.txt");
    Passport* p = new Passport;;
    while (getline(myfile, line)) {
        if (line == ""){
            pv.push_back(*p);
            p = new Passport;
        }
        else{
            add_to_passport(p, line);
        }
    }
    pv.push_back(*p);
    return pv;
}


int main() {
    vector<Passport> vp = generate_passports_from_file();
    int count = 0;
    for (Passport passport:vp){
        if (is_passport_valid(&passport)){
            count++; 
            passport.print();
        }
    }
    cout << count << "/" << vp.size() << endl;
}
