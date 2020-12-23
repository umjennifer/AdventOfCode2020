/*
 Advent of Code Day 7
 v1.3 2020-12-22
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
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

int main() {
    // TODO: convert to set
    vector<Bag> allBags;
// Take care of input
    vector <string> input;
    ifstream fin;
    string line;

    fin.open("input.txt");
    
    // save all lines of input into vector "input"
    while(!fin.eof()) {
        Bag bag_parent;
        
        getline(fin, line);
        line.pop_back();
        
        string bags_string = " bags";
        eraseSubstrings(line, bags_string);
        
        string bag_string = " bag";
        eraseSubstrings(line, bag_string);
        
        string bag_parent_color = line.substr(0,line.find(" contain"));
        
        cout << line << endl; // "faded yellow contain 4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
        
        cout << "bag_parent_color: " << bag_parent_color;
        cout << endl;
        bag_parent.color = bag_parent_color;
        
        line.erase(0,line.find(" contain")); //" contain 4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
        line.erase(0,9); // "4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
        
        if (line.find("no other") == std::string::npos){ // for bags that do not have string "no other" and thus do contain other bags
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
            //cout << line << endl; // "4 mirrored fuchsia, 4 dotted indigo, 3 faded orange, 5 plaid crimson"
            
            stringstream linestream(line);
            while (!linestream.eof()){
                string bag_child_string;
                getline(linestream, bag_child_string, ',');
                //cout << "child string:" << bag_child_string << " | "; // ex: "4 mirrored fuchsia"
                
                string bag_child_quantity_string = bag_child_string.substr(0,bag_child_string.find(" ")); //quantity will be substring from start to first instance of " "
                cout << bag_child_quantity_string << "," ;
                
                string bag_child_color = bag_child_string.erase(0,bag_child_string.find(bag_child_quantity_string)+2);
                cout << bag_child_color << endl;
                
                
                Bag bag_child;
                bag_child.color = bag_child_string;
                bag_child.quantity = stoi(bag_child_quantity_string);
                bag_child.fitsInto.push_back(bag_parent);
                
                allBags.push_back(bag_child);
                
                bag_parent.canContain.push_back(bag_child);
                
            }

        }
        allBags.push_back(bag_parent);
        /*
        cout << bag_parent.color << " contains: ";
        for (int i = 0; i < bag_parent.canContain.size(); i++){
            cout << bag_parent.canContain.at(i).color << ",";
        }
        */
        cout << endl << endl;
    }
    fin.close();

    /*
    for (int i = 0; i < allBags.size(); i++){
        cout << allBags.at(i).color << " fits into: ";
        for (int j = 0; j <allBags.at(i).fitsInto.size(); j++){
            cout << allBags.at(i).fitsInto.at(j).color << ", ";
        }
        cout << endl;
    }
     */
    for (int i = 0; i < allBags.size(); i++){
        cout << allBags.at(i).color << " contains: ";
        for (int j = 0; j <allBags.at(i).canContain.size(); j++){
            cout << allBags.at(i).canContain.at(j).color << ", ";
        }
        cout << endl;
    }
    
    
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

//
