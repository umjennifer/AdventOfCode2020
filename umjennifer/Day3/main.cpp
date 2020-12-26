
//
//  main.cpp
//  Day3
//
//  Created by Jennifer Um on 12/3/20.
//  Copyright © 2020 Jennifer Um. All rights reserved.
//

struct Coordinate {
    int x;
    int y;
};

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(){
    // can be class members
    int width;
    int length;
    
    ifstream fin;
    string line;
    vector<string> linesOfForest;

    fin.open("input.txt");

    while(!fin.eof()) {
        //cout << "reading line" << endl;
        getline(fin,line);
        //cout << line << endl;
        linesOfForest.push_back(line);
    }
    fin.close();
    
    width = linesOfForest[0].size();
    length = linesOfForest.size();

    /*
    for (int i = 0; i < linesOfForest.size(); i++){
        cout << linesOfForest.at(i) << endl;
    }
    */
    //cout << linesOfForest[1][1] << endl;

    
    // Create 2D array from the vector
    char forest[length][width];
    cout << "length: " << length << endl;
    cout << "width: " << width << endl;
    
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            //forest[i][j] = '*';
            //cout << linesOfForest[i][j];
            forest[i][j] = linesOfForest[i][j];
            //cout << linesOfForest[i][j];
        }
        //cout << endl;
    }
    
    /*
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            cout << forest[i][j];
        }
        cout << endl;
    }*/
    
    int right_step = 3;
    int down_step = 1;
    
    int curr_i = 0;
    int curr_j = 0;
    
    vector<Coordinate> coordinates;
    // TODO: create constructor if I create class
    Coordinate coord1;
    coord1.x = 0;
    coord1.y = 0;
    coordinates.push_back(coord1);
    
    
    // create all the coordinates
    for (int i = 0; i < length; i++){
            curr_j += down_step;
            //curr_coord.y = curr_j;
        cout << curr_j << endl;
    }

    for (int i = 0; i < width; i++){
            curr_j += down_step;
            //curr_coord.y = curr_j;
        cout << curr_j << endl;
    }
    
    /*
    // print out all the coordinates
    for (int i = 0; i < coordinates.size(); i++){
        cout << "coord x: " << coordinates[i].x << ", coord y: " << coordinates[i].y;
        cout << endl;
    }*/
    
    
}
