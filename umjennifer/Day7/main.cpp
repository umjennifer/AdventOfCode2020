/*
 Advent of Code Day 7
 v1.4 2020-12-22
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
    vector<Bag> fitsInto;
    vector<Bag> canContain;
    // TODO: specify
    int quantity;
};

void findAllAncestors(Bag, vector<Bag>&);
void eraseSubstrings(string&, string);
void parseInput(unordered_map<string, Bag>&);
string formatLineAndGetParentBagColor(string&);
void parseChildBagsDataRelateToParentBag(string&, Bag&);
void standardizeCommaDelimter(string&);


int main() {
    unordered_map<string, Bag> allBags;
    parseInput(allBags);
    return 0;
}

void findAllAncestors(Bag color, vector<Bag>& bagAncestors){
    //cout << endl << "orig color: " << color.color << endl;
    for (int i = 0; i < color.fitsInto.size(); i++){
        Bag curr_bag = color.fitsInto.at(i); // parents of original colored bag
        //cout << "parent: " << curr_bag.color << endl;
        bagAncestors.push_back(curr_bag);
        findAllAncestors(curr_bag, bagAncestors);
    }
}

void eraseSubstrings(string& line, string substring){
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop until nothing is found
    while ((pos = line.find(substring) )!= std::string::npos){
        // If found then erase it from string
        line.erase(pos, substring.length());
    }
}

void parseInput(unordered_map<string,Bag>& allBags){
    // Take care of input
    vector <string> input;
    ifstream fin;
    string line;

    fin.open("input.txt");
    
    // save all lines of input into vector "input"
    while(!fin.eof()) {
        
        getline(fin, line);
        string bag_parent_color = formatLineAndGetParentBagColor(line);
        
        // DEBUGGING
        //cout << line << endl; // "faded yellow contain 4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
        cout << "bag_parent_color: " << bag_parent_color;
        cout << endl;
        //
        
        Bag bag_parent;
        bag_parent.color = bag_parent_color;
        parseChildBagsDataRelateToParentBag(line, bag_parent);
        
        // if bag_parent not in allBags unordered_map
        if (allBags.find(bag_parent.color) == allBags.end()){
            allBags[bag_parent.color] = bag_parent;
        }
        
        
        cout << endl << endl;
    }
    fin.close();
}

string formatLineAndGetParentBagColor(string& line){
    
    line.pop_back();
    
    string bags_string = " bags";
    eraseSubstrings(line, bags_string);
    
    string bag_string = " bag";
    eraseSubstrings(line, bag_string);
    string color = line.substr(0,line.find(" contain"));
    
    line.erase(0,line.find(" contain")); //" contain 4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
    line.erase(0,9); // "4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
    
    return color;
}


void parseChildBagsDataRelateToParentBag(string& line, Bag& bag_parent){
    
    // bags that have string "no other" have no child bags, thus will not need to complete these steps
    
    if (line.find("no other") == std::string::npos){ // for bags that do not have string "no other" and thus do contain other bags
        standardizeCommaDelimter(line); //cout << line << endl; // "4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
        
        
        stringstream linestream(line);
        while (!linestream.eof()){
            string bag_child_string;
            getline(linestream, bag_child_string, ','); // split line by comma delimiter. Each substring will be a child string
            
            // get quantity of child bag that can fit into parent bag
            string bag_child_quantity_string =
                bag_child_string.substr(0,bag_child_string.find(" ")); //quantity will be substring from start to first instance of " "
            cout << bag_child_quantity_string << "," ;
            int bag_child_quanity = stoi(bag_child_quantity_string);
            
            // get color of child bag that can fit into parent bag
            string bag_child_color =
            bag_child_string.erase(0,bag_child_string.find(bag_child_quantity_string)+2);
            cout << bag_child_color << endl;
            
            Bag bag_child;
            bag_child.color = bag_child_string;
            bag_child.quantity = bag_child_quanity;
            
            // check hashmap, update parent bag's can contain vector
            
            // check hashmap, if child bag not in hashmap
                // update child bag's fits into w/ parent
                // add to hashmap
            // if child bag in hashmap
                // find child bag in hashmap
                // update child bag's fits into with parent
            
            
        }

    }
}

void standardizeCommaDelimter(string& line){
    // replace ", " with ","
    string to_replace = ", ";
    string replace_with = ",";
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
