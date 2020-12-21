/*
 Advent of Code Day 7
 v1.2 2020-12-20
 Using example provided
 
 light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
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
    //TODO: map <Bag, int> canContain;
    vector<Bag> fitsInto;
};

void findAllAncestors(Bag, vector<Bag>&);

int main() {
    
    vector <string> input;
    ifstream fin;
    string this_line;

    fin.open("input.txt");
    
    // save all lines of input into vector "input"
    while(!fin.eof()) {
        getline(fin, this_line);
        //cout << line << endl;
        this_line.pop_back();
        input.push_back(this_line);
        
    }
    fin.close();
    
    for (int i = 0; i < input.size(); i++){
        string line = input.at(i);
        cout << line << endl;
    }
    cout << endl;
    
    for (int i = 0; i < input.size(); i++){
        string line = input.at(i);
        Bag bagA;
        bagA.color = line.substr(0, line.find(" bags contain "));
        cout << bagA.color << endl;
        
        line = line.erase(0,line.find("contain ")); // turns line into :"contain 4 mirrored fuchsia bags, 4 dotted indigo bags, 3 faded orange bags, 5 plaid crimson bags"
        line = line.erase(0,8); // turns line into :"4 mirrored fuchsia bags, 4 dotted indigo bags, 3 faded orange bags, 5 plaid
        
        cout << "modified line:" << line << endl;
        
        stringstream linestream(line);
        string child;
        while (!linestream.eof()){
            getline(linestream,child,',');
            if (child[0] == ' '){
                child.erase(0,1);
            }
            cout << "child:" << child << " "; //4 mirrored fuchia bags
            //TODO: QUANTITY
            int quantity = stoi(child.substr(0,child.find(" ")));
            child = child.erase(0,child.find(" "));
            child = child.erase(0,1);
            child.pop_back();
            child.pop_back();
            child.pop_back();
            child.pop_back();
            child.pop_back();
            string color = child;
            cout << ", quantity:" << quantity << ", color:" << color << endl;
            Bag this_bag;
            this_bag.color = color;
        }
        cout << endl;
    }
    
    
    
    /*
    Bag bagA;
    string example = "faded yellow bags contain 4 mirrored fuchsia bags, 4 dotted indigo bags, 3 faded orange bags, 5 plaid crimson bags.";
    bagB.color = example.substr(0,example.find(" bags contain "));
    */
    
    
    


    
//    vector<Bag> bagAncestors;
//    findAllAncestors(shinyGold, bagAncestors);
//
//    set<string> uniqueBagAncestors;
//    for (int i = 0; i < bagAncestors.size(); i++){
//        uniqueBagAncestors.insert(bagAncestors.at(i).color);
//    }
//
//    cout << endl << "unique bag ancestors: ";
//    for (string bag : uniqueBagAncestors){
//        cout << bag << ", ";
//    }
//    cout << endl;
//    cout << "size: " << uniqueBagAncestors.size() << endl;
    
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
