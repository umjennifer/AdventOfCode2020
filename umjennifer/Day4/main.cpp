/*
 Advent of Code 2020 Day 4
 v2, Last Modified: 2020-12-13
 
 TODO: organize into functions
 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>


using namespace std;

struct Passport {
    string byr = "";
    string iyr = "";
    string eyr = "";
    string hgt = "";
    string hcl = "";
    string ecl = "";
    string pid = "";
    string cid = "";
};


struct linesRange {
    int start;
    int end;
};

bool byrCheck(string byr){
    bool byrBool = false;
    if (byr.length() == 4){
        int birth_year = stoi(byr);
        if (birth_year >= 1920 && birth_year <= 2002){
            byrBool = true;
        }
    }
    return byrBool;
}

bool iyrCheck(string iyr){
    bool iyrBool = false;
    if (iyr.length() == 4){
        int issued_year = stoi(iyr);
        if (issued_year >= 2010 && issued_year <= 2020){
            iyrBool = true;
        }
    }
    return iyrBool;
}

bool eyrCheck(string eyr){
    bool eyrBool = false;
    if (eyr.length() == 4){
        int expired_year = stoi(eyr);
        if (expired_year >= 2020 && expired_year <= 2030){
            eyrBool = true;
        }
    }
    return eyrBool;
}

bool hgtCheck(string hgt){
    bool hgtBool = false;
    
    if ((hgt.length() >= 2) && (hgt.substr(hgt.length()-2) == "cm" || hgt.substr(hgt.length()-2) == "in")){
        
        string unit = hgt.substr(hgt.length()-2);
        int height = stoi(hgt.substr(0,hgt.find(unit)));
        
        if (unit == "cm"){
            if (height >= 150 && height <= 193){
                hgtBool = true;
            }
        }
        else if (unit == "in"){
            if (height >= 59 && height <= 76){
                hgtBool = true;
            }
        }
    }
    return hgtBool;
}

bool hclCheck(string hcl){
    bool hclBool = false;
    if (hcl.length() == 7){
        if (hcl[0] == '#'){
            int valid_char = 0;
            for (int i = 1; i < 7; i++){
                if (isalnum(hcl[i])){
                    valid_char++;
                }
            }
            if (valid_char == 6){
                hclBool = true;
            }
        }
    }
    return hclBool;
}

bool eclCheck(string ecl){
    bool eclBool = false;
    
    vector<string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    // if element in vector
    if (find(valid_ecl.begin(), valid_ecl.end(), ecl) != valid_ecl.end()){
        eclBool = true;
    }
    return eclBool;
}

bool pidCheck(string pid){
    bool pidBool = false;
    int valid_chars = 0;
    if (pid.length() == 9){
        for (int i = 0; i < pid.length(); i++){
            if (isdigit(pid[i])){
                valid_chars++;
            }
        }
        if (valid_chars == 9){
            pidBool = true;
        }
    }
    return pidBool;
}



int main() {
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
    
    
    vector<string> passport_strings;
    for (int i = 0; i < ranges.size(); i++){
        //cout << "curr range: start=" << ranges.at(i).start << " end=" << ranges.at(i).end << endl;
    }
    
    for (int i = 0; i < ranges.size(); i++){
        //cout << "index i = " << i << endl;
        string passport_string;
        for (int j = ranges.at(i).start; j <= ranges.at(i).end; j++){
            passport_string = passport_string + input.at(j) + " ";
        }
        passport_string.pop_back(); // erase space at end of the string
        passport_strings.push_back(passport_string);
    }
    
    /*
    for (int i = 0; i < passport_strings.size(); i++){
        cout << passport_strings.at(i) << endl;
    }
     */
     
    
    /*PART 1//////////////////////*/
    /*
    vector<string> fieldsToCheck = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
    
    vector<string> fieldsPerPassport;
    vector<vector<string>> vOfFieldsPerPassport;
        
    for (int i = 0; i < passport_strings.size(); i++){ // for each line
        stringstream linestream(passport_strings.at(i)); // save each line as string stream

        while (!linestream.eof()){ // for each string stream
            string s;
            getline(linestream,s,' '); // get portion of string stream and save as string s
            string key = s.substr(0,3);
            fieldsPerPassport.push_back(key);
        }
        vOfFieldsPerPassport.push_back(fieldsPerPassport);
        fieldsPerPassport.clear();
        //cout << endl;
    }
    

    int numInvalidPassports = 0;
    for (int i = 0; i < vOfFieldsPerPassport.size(); i++){
        //cout << vOfFieldsPerPassport[i].size() << endl;
        
        if (vOfFieldsPerPassport[i].size() < fieldsToCheck.size()){ // if passport contains less than 8 fields
            //cout << vOfFieldsPerPassport[i].size() << endl;
            
            if  (vOfFieldsPerPassport[i].size() == 7){ // if passport contains exactly 7 fields
                if (find(vOfFieldsPerPassport[i].begin(), vOfFieldsPerPassport[i].end(), "cid") == vOfFieldsPerPassport[i].end()){ // if cid is not in vOfFieldsPerPassport[i]
                    // do nothing
                    //cout << "i =" << i << "7 Fields, missing cid: " << passport_strings.at(i) << endl;
                } else { // else, if passport contains exactly 7 fields and is missing something else,
                    numInvalidPassports++;
                    cout << "i =" << i << "7 Fields, missing something else: " << passport_strings.at(i) << endl;
                }
            } else { // if passport size is any other size (less than 7)
                numInvalidPassports++;
                cout << "i =" << i << "Less than 7 fields: " << passport_strings.at(i) << endl;
            }
            
        }
        
    }
    int numValidPassports = passport_strings.size() - numInvalidPassports;
    cout << "numInvalidPassports: " << numInvalidPassports << endl;
    cout << "numValidPassports: " << numValidPassports << endl;
 */
    
    
/*PART 2//////////////////////*/
    //for (int i = 0; i < passport_strings.size(); i++){ // for each line
        //stringstream linestream(passport_strings.at(i)); // save each line as string stream

    vector<Passport> passports;
    
    for (int i = 0; i < passport_strings.size(); i++){
        stringstream linestream(passport_strings.at(i));
        //map<string,string> curr_passport;
        Passport this_passport;
        while (!linestream.eof()){ // for each string stream
            string s;
            getline(linestream,s,' '); // get portion of string stream and save as string s
            string key = s.substr(0,3);
            string value = s.substr(4);
            //cout << "key:" << key << " value:" << value << endl;
            
            if (key == "byr"){
                this_passport.byr = value;
            }
            else if (key == "iyr"){
                this_passport.iyr = value;
            }
            else if (key == "eyr"){
                this_passport.eyr = value;
            }
            else if (key == "hgt"){
                this_passport.hgt = value;
            }
            else if (key == "hcl"){
                this_passport.hcl = value;
            }
            else if (key == "ecl"){
                this_passport.ecl = value;
            }
            else if (key == "pid"){
                this_passport.pid = value;
            }
            else if (key == "cid"){
                this_passport.cid = value;
            }
            // if I were using map: curr_passport.insert(pair<string, string>(key, value));
        }
        passports.push_back(this_passport);
    }
    
    int valid_passports = 0;
    // TODO: debugging, change this value
    //for (int i = passports.size()-1; i < passports.size(); i++){

    for (int i = 0; i < passports.size(); i++){
        cout << i << ": " << "byr=" << passports.at(i).byr << endl;
        cout << i << ": " << "iyr=" << passports.at(i).iyr << endl;
        cout << i << ": " << "eyr=" << passports.at(i).eyr << endl;
        cout << i << ": " << "hgt=" << passports.at(i).hgt << endl;
        cout << i << ": " << "hcl=" << passports.at(i).hcl << endl;
        cout << i << ": " << "ecl=" << passports.at(i).ecl << endl;
        cout << i << ": " << "pid=" << passports.at(i).pid << endl;
        cout << i << ": " << "cid=" << passports.at(i).cid << endl;
        cout << endl;
        
        int valid_fields = 0;
        // See if each field (other than cid) is true or false
        // If returns true, the field is valid and increment valid_fields
        if (byrCheck(passports.at(i).byr)){
            valid_fields++;
            cout << i << ": " << "bry valid" << endl;
        }
        if (iyrCheck(passports.at(i).iyr)){
            valid_fields++;
            cout << i << ": " << "iyr valid" << endl;
        }
        if (eyrCheck(passports.at(i).eyr)){
            valid_fields++;
            cout << i << ": " << "eyr valid" << endl;
        }
        if (hgtCheck(passports.at(i).hgt)){
            valid_fields++;
            cout << i << ": " << "hgt valid" << endl;
        }
        if (hclCheck(passports.at(i).hcl)){
            valid_fields++;
            cout << i << ": " << "hcl valid" << endl;
        }
        if (eclCheck(passports.at(i).ecl)){
            valid_fields++;
            cout << i << ": " << "ecl valid" << endl;
        }
        if (pidCheck(passports.at(i).pid)){
            valid_fields++;
            cout << i << ": " << "pid valid" << endl;
        }
        
        // if valid_fields == 7, the passport is valid. Increment valid_passports
        if (valid_fields == 7){
            valid_passports++;
        }
        
    }
    
    cout << "Valid passports: " << valid_passports << endl;

    /* if I were using map
    map<string, string>::iterator itr;
    cout << "\nThe curr_passport is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = curr_passport.begin(); itr != curr_passport.end(); ++itr) {
        cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }
    cout << endl;
     */
    
}
