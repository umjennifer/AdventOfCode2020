/*
 Advent of Code Day 7
 v1.7 2020-12-25
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct Bag {
    string color;
    set<string> fitsInto;
    vector<Bag> canContain;
    // TODO: specify
    int quantity;
};

void saveInputInVector(string, vector<string>&);
void standardizeStrings(vector<string>&);
void eraseSubstring(string& , string);
void replaceSubstring(string& , string, string);
void getDatafromString(vector<string>, unordered_map<string, Bag>&);
string getParentColor(string);
int getChildQuantity(string);
string getChildColor(string);
void updateFitsInto(unordered_map<string, Bag>&);
void updateBagsAncestorColors(string,unordered_map<string, Bag>, set<string>&);
int countBagAncestorColorsTotal(set<string>);
void partOne(unordered_map<string, Bag>);
void partTwo(unordered_map<string, Bag>);
void updateBagsDescendents(string,unordered_map<string, Bag>,vector<Bag>&);

int main(){
    unordered_map<string, Bag> allBags;
    string filename = "input.txt";
    vector<string> inputVector;
    
    saveInputInVector(filename, inputVector);
    standardizeStrings(inputVector);
    getDatafromString(inputVector, allBags);
    updateFitsInto(allBags);
    
    //partOne(allBags);
    partTwo(allBags);
    
    return 0;
}

void saveInputInVector(string filename, vector<string>& inputVector){
    ifstream fin;
    string line;

    fin.open(filename);

    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, line);
        inputVector.push_back(line);
    }
    fin.close();
}

void standardizeStrings(vector<string>& inputVector){

    for (int i = 0; i < inputVector.size(); i++){
        string* line = &inputVector.at(i);
        line->pop_back();
        
        replaceSubstring(*line, " bags contain no other bags", ":");
        eraseSubstring(*line, " bags");
        eraseSubstring(*line, " bag");
        replaceSubstring(*line, " contain ", ":");
        replaceSubstring(*line, ", ", ",");
        
    }
}

void eraseSubstring(string& line, string substring){
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop until nothing is found
    while ((pos = line.find(substring) )!= std::string::npos){
        // If found then erase it from string
        line.erase(pos, substring.length());
    }
}

void replaceSubstring(string& line, string to_replace, string replace_with){
    size_t index = 0;
    while (true) {
         /* Locate the substring to replace. */
         index = line.find(to_replace, index);
         if (index == std::string::npos) break;

         /* Make the replacement. */
        line.replace(index, to_replace.length(), replace_with);

         /* Advance index forward so the next iteration doesn't pick it up as well. */
         index += to_replace.length();
    }
}

void getDatafromString(vector<string> inputVector, unordered_map<string, Bag>& allBags){

    
    
    for(string line : inputVector){ // for each string line --> stringstream sstream
        Bag parent;
        parent.color = getParentColor(line);
        //cout << "parent color: " << parent_color << endl;

        string children_string = line.substr(line.find(":")+1);
        //cout << children_string << endl;
        
        stringstream children_string_stream(children_string);
        while (!children_string_stream.eof()){
            string child_string;
                        
            getline(children_string_stream, child_string,',');
            //cout << "child string:" << child_string << endl;
            
            // if child_string not empty
            if (!child_string.empty()){
                Bag child;
                child.quantity = getChildQuantity(child_string);
                child.color = getChildColor(child_string);
                //cout << "color:" << child.color << ",quant:" << child.quantity << endl << endl;
                parent.canContain.push_back(child);
            }
        }
        //cout << endl << endl;
        
        allBags[parent.color] = parent;
    }
    //cout << endl;
}

string getParentColor(string line){
    return line.substr(0,line.find(":"));
}

int getChildQuantity(string child_string){
    return stoi(child_string.substr(0,child_string.find(" ")));
}

string getChildColor(string child_string){
    return child_string.substr(child_string.find(" ")+1);
}

void updateFitsInto(unordered_map<string, Bag>& allBags){
        for(auto bag : allBags){
            // bag.first is the parent color
            // bag.second is the parent Bag structure
    //        cout << bag.first << " can contain: ";
            for (int i =0; i < bag.second.canContain.size(); i++){ // for each Bag in vector bag.second.canContain
    //            cout << bag.second.canContain.at(i).quantity << " " << bag.second.canContain.at(i).color << ",";
                
                // find bag.second.canContain.at(i).color in allBags
                allBags[bag.second.canContain.at(i).color].fitsInto.insert(bag.first);
                // add bag.first into bag.second.canContain.at(i).color's string
            }
    //        cout << endl;
        }
        
    // DEBUG
//        for(auto bag : allBags){
//            // bag.first is the parent color
//            // bag.second is the parent Bag structure
//            cout << bag.first << " fits into: ";
//            set<string>::iterator it = bag.second.fitsInto.begin();
//            while (it != bag.second.fitsInto.end()){
//                cout << *it << ",";
//                it++;
//            }
//            cout << endl;
//        }
}

void updateBagsAncestorColors(string desired_color,unordered_map<string, Bag> allBags, set<string>& BagsAncestorColors){
    Bag desiredBag = allBags[desired_color]; // find Bag using desired_color string
    //cout << desiredBag.color << endl;
    
    // find the "fits into" set<sting>, iterate through it
    set<string>::iterator it = desiredBag.fitsInto.begin();
    while (it != desiredBag.fitsInto.end()){
        string ancestor_color = *it;
        //cout << ancestor_color << ",";
        
        // insert ancestor_color into set<string> BagsAncestorColors
        BagsAncestorColors.insert(ancestor_color);
        updateBagsAncestorColors(ancestor_color, allBags, BagsAncestorColors);
        it++;
    }
    //cout << endl;
}

int countBagAncestorColorsTotal(set<string> BagsAncestorColors){
    int total = 0;
    set<string>::iterator it = BagsAncestorColors.begin();
    while (it != BagsAncestorColors.end()){
        //cout << *it << endl;
        it++;
        total++;
    }
    return total;
}

void partOne(unordered_map<string, Bag> allBags){
    string desired_color = "shiny gold";
    set<string> BagsAncestorColors;
    updateBagsAncestorColors(desired_color, allBags, BagsAncestorColors);
    int total = countBagAncestorColorsTotal(BagsAncestorColors);
    cout << "Total ancestors: " << total << endl;
}

void partTwo(unordered_map<string, Bag> allBags){
    string desired_color = "shiny gold";
    vector<Bag> BagDescendents;
    updateBagsDescendents(desired_color,allBags,BagDescendents);
    cout << "Total descendents: " << BagDescendents.size() << endl;
}

void updateBagsDescendents(string desired_color, unordered_map<string, Bag> allBags,vector<Bag>& BagDescendents){
    Bag desiredBag = allBags[desired_color]; // find desired bag in all bags
    for (int i = 0; i < desiredBag.canContain.size(); i++){
        Bag descendent = desiredBag.canContain.at(i);
        for (int j = 0; j < descendent.quantity; j++){
            BagDescendents.push_back(descendent);
            cout << "pushing back:" << descendent.color << endl;
            updateBagsDescendents(descendent.color, allBags, BagDescendents);
        }
    }
    
}
