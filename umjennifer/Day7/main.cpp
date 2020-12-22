/*
 Advent of Code Day 7
 v1.2 2020-12-20
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
    vector<Bag> canContain;
};

void findAllAncestors(Bag, vector<Bag>&);

int main() {
    // TODO: convert to set
    vector<Bag> allBags;
// Take care of input
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
    
    Bag bagA;
    for (int i = 0; i < input.size(); i++){
        string line = input.at(i);
        
        bagA.color = line.substr(0, line.find(" bags contain "));
        allBags.push_back(bagA);
        cout << bagA.color << endl;
        
        line = line.erase(0,line.find("contain ")); // turns line into :"contain 4 mirrored fuchsia bags, 4 dotted indigo bags, 3 faded orange bags, 5 plaid crimson bags"
        line = line.erase(0,8); // turns line into :"4 mirrored fuchsia bags, 4 dotted indigo bags, 3 faded orange bags, 5 plaid
        
        cout << "modified line:" << line << endl;
        
        if (line == "no other bags"){
            
        }
        else {
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
                this_bag.fitsInto.push_back(bagA); // this_bag can fit into BagA
                bagA.canContain.push_back(this_bag); // BagA can contain this bag
                allBags.push_back(this_bag);
            }
            cout << endl;
        }
    }
    cout << endl;
    //cout << all << endl;

    
    
    for (int i = 0; i < allBags.size(); i++){
        cout << allBags.at(i).color << " fits into ";
        for (int j = 0; j < allBags.at(i).fitsInto.size(); j++){
            cout << allBags.at(i).fitsInto.at(j).color << ",";
        }
        cout << endl;
    }
    cout << endl;
     
     
    
    // keep unique values in allBags
/*
    cout << "all bags: " << endl;
    for (int i = 0; i < allBags.size(); i++){
        cout << allBags.at(i).color << endl;
        
        cout << allBags.at(i).color << " fits in: ";
        for (int j = 0; j < allBags.at(i).fitsInto.size(); j++){
            cout << allBags.at(i).fitsInto.at(j).color << ",";
        }
        cout << endl;
        cout << allBags.at(i).color << " can contain: ";
        for (int j = 0; j < allBags.at(i).canContain.size(); j++){
            cout << allBags.at(i).canContain.at(j).color << ",";
        }
        cout << endl << endl;
    }
    */
    
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
