//
//  main.cpp
//  Swap-Encryption
//
//  Created by Jacob Smith on 2017-10-11.
//  Copyright © 2017 JacuzziProductions. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <sstream>
#include <string>
using namespace std;


int length = 0;
ifstream data;
ofstream outKey;
ofstream outLock;

int nextRand(){
    int x = rand() % length;
    return x;
}

int main(int argc, const char * argv[]) {
    if(argc != 4) {
        cerr << "Usage: " << argv[0] << "data.txt key.txt lock.txt" << endl;
        exit(1);
    }
    
    stringstream strStream;
    
    // data.txt
    data.open(argv[1]);
    if(!data.is_open()) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }
    // key.txt
    outKey.open(argv[2]);
    if(!outKey.is_open()) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    
    // lock.txt
    outLock.open(argv[3]);
    if( !outLock.is_open() ) {
        cerr << "Unable to open " << argv[3] << endl;
        exit(4);
    }
    
    string line;
    string swapper;
    while(getline(data, line)) {
        cout << line << endl;
        swapper += line;
        length += line.length();
    }
    srand(static_cast<unsigned int>(time(NULL)));
    
    
    for (int i = 0; i < length * 11; i++){
        int n = nextRand();
        outKey << n << " ";
        swap(swapper[n], swapper[n+1]);
    }
    
    outLock << swapper;
    
}
