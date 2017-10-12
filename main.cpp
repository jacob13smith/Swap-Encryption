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

int nextRand(){
    int x = rand() % length;
    return x;
}

void decrypt(const char * argv[]){
    
    ofstream decrypt;
    ifstream inKey;
    ifstream inLock;

    // data.txt
    decrypt.open(argv[1]);
    if(!decrypt.is_open()) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }
    // key.txt
    inKey.open(argv[2]);
    if(!inKey.is_open()) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    
    // lock.txt
    inLock.open(argv[3]);
    if( !inLock.is_open() ) {
        cerr << "Unable to open " << argv[3] << endl;
        exit(4);
    }
    
    string line;
    string cipher;
    while(getline(inLock, line)) {
        cout << line;
        cipher += line;
    }
    
    int n;
    vector<int> swaps;
    while (inKey >> n){
        swaps.push_back(n);
    }
    
    long size = swaps.size();
    for (int i = 0; i < size; i++){
        swap(cipher[swaps.back()],cipher[swaps.back() + 1]);
        swaps.pop_back();
    }
    decrypt << cipher;
}

int main(int argc, const char * argv[]) {
    if(argc != 5) {
        cerr << "Usage: " << argv[0] << "data.txt key.txt lock.txt" << endl;
        exit(1);
    }
    
    ifstream data;
    ofstream outKey;
    ofstream outLock;

    if (atoi(argv[4]) == 1){
        decrypt(argv);
        exit(0);
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
        cout << line;
        swapper += line;
        length += line.length();
    }
    srand(static_cast<unsigned int>(time(NULL)));
    
    
    for (int i = 0; i < length * 7; i++){
        int n = nextRand();
        outKey << n << " ";
        swap(swapper[n], swapper[n+1]);
    }
    
    outLock << swapper;
    
}
