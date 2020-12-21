/*
 Advent of Code Day 7
 v1 2020-12-20
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
#include <vector>
#include <set>
using namespace std;

struct Bag {
    string color;
    vector<Bag> canContain;
    vector<Bag> fitsInto;
};

void findAllAncestors(Bag, vector<Bag>&);

int main() {
    // instantiate bag types
    Bag lightRed;
    lightRed.color = "lightRed";
    
    Bag darkOrange;
    darkOrange.color = "darkOrange";
    
    Bag brightWhite;
    brightWhite.color = "brightWhite";
    
    Bag mutedYellow;
    mutedYellow.color = "mutedYellow";
    
    Bag shinyGold;
    shinyGold.color = "shinyGold";
    
    Bag darkOlive;
    darkOlive.color = "darkOlive";
    
    Bag vibrantPlum;
    vibrantPlum.color = "vibrantPlum";
    
    Bag fadedBlue;
    fadedBlue.color = "fadedBlue";
    
    Bag dottedBlack;
    dottedBlack.color = "dottedBlack";

    lightRed.canContain = {
        brightWhite,
        mutedYellow,
        mutedYellow
    };
    
    darkOrange.canContain = {
        brightWhite,
        brightWhite,
        brightWhite,
        mutedYellow,
        mutedYellow,
        mutedYellow,
        mutedYellow
    };
    
    brightWhite.canContain = {
        shinyGold
    };
    
    mutedYellow.canContain = {
        shinyGold,
        shinyGold,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue
    };
    
    shinyGold.canContain = {
        darkOlive,
        vibrantPlum,
        vibrantPlum
    };
    
    darkOlive.canContain = {
        fadedBlue,
        fadedBlue,
        fadedBlue,
        dottedBlack,
        dottedBlack,
        dottedBlack,
        dottedBlack
        
    };
    
    vibrantPlum.canContain = {
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        fadedBlue,
        dottedBlack,
        dottedBlack,
        dottedBlack,
        dottedBlack,
        dottedBlack,
        dottedBlack
    };
    
    fadedBlue.canContain = {};
    dottedBlack.canContain = {};
    
    lightRed.fitsInto = {};
    darkOrange.fitsInto = {};
    brightWhite.fitsInto = {lightRed, darkOrange};
    mutedYellow.fitsInto = {lightRed, darkOrange};
    shinyGold.fitsInto = {brightWhite, mutedYellow};
    darkOlive.fitsInto = {shinyGold};
    vibrantPlum.fitsInto = {shinyGold};
    fadedBlue.fitsInto = {mutedYellow, darkOlive, vibrantPlum};
    dottedBlack.fitsInto = {darkOlive, vibrantPlum};
    
    vector<Bag> bagAncestors;
    
    
        // generation++
        // add that bag that shiny gold bag fits into into
        // find the parents of the bag that generation 1 bag fits into
    
    findAllAncestors(shinyGold, bagAncestors);
    
    
//    for (int i = 0; i < shinyGold.fitsInto.size(); i++){ // for bag that shiny gold bag fits into
//        Bag curr_bag;
//        curr_bag = shinyGold.fitsInto.at(i);
//        bagColorsWithDescendentShinyGold.push_back(curr_bag);
//        generation++;
//        cout << "curr_bag color: " << curr_bag.color << endl;
//        for (int j = 0; j < curr_bag.fitsInto.size(); j++){
//            cout << "fits into: " << curr_bag.fitsInto.at(i).color << endl;
//        }
//    }
    
    set<string> uniqueBagAncestors;
    for (int i = 0; i < bagAncestors.size(); i++){
        uniqueBagAncestors.insert(bagAncestors.at(i).color);
    }

    cout << endl << "unique bag ancestors: ";
    for (string bag : uniqueBagAncestors){
        cout << bag << ", ";
    }
    cout << endl;
    cout << "size: " << uniqueBagAncestors.size() << endl;
    
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
