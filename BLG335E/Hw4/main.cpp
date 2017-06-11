//
//  main.cpp
//  Algo4
//
//  Created by Emre Özdil on 11/12/16.
//  Copyright © 2016 Emre Özdil. All rights reserved.
//

#include "myHash.h"

void readFile(char*, int);
void writeFile();

myHash* table;

int main(int argc, char ** argv)
{
    char* fileName = argv[1];
    int N = atoi(argv[2]);
    readFile(fileName, N);
    writeFile();
    return 0;
}

void readFile(char* fileName, int N)
{
    char* inputFileName;
    inputFileName = (char*)fileName;
    table = new myHash(N);
    table->words = new Word[N];
    ifstream inputStream;
    string line;
    string type;
    string value;
    string delimiter = ":";
    size_t pos;
    inputStream.open(inputFileName, ios::in);
    while (inputStream >> line)
    {
        pos = line.find(delimiter);
        type = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        value = line;
        if (type=="insert")
        {
            table->insert(value);
        }
        else if (type=="retrieve")
        {
            table->retrieve(value);
        }
        else if (type=="delete")
        {
            table->remove(value);
        }
        else
        {
            ;
        }
    }
}

void writeFile()
{
    cout<<"-------------------------------------"<<endl;
    cout<<"TOTAL COLLISIONS: "<<table->collision<<endl;
    cout<<"Final form of hash table is saved as 150120138_output.txt"<<endl;
    char* outputFileName;
    outputFileName = (char*)"150120138_output.txt";
    ofstream outputStream;
    outputStream.open(outputFileName, ios::out | ios::trunc);
    for (int i=0; i<table->getTableSize(); i++) {
        if(table->words[i].getContent() != "")
            outputStream<<i<< ": " << table->words[i].getContent()<<endl;
    }
}

