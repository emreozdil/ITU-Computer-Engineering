//
//  myHash.h
//  Algo4
//
//  Created by Emre Özdil on 11/12/16.
//  Copyright © 2016 Emre Özdil. All rights reserved.
//

#pragma once

#include "word.h"

class myHash
{
private:
    int tableSize;
    static int totalEntries; // Stores the current number of entries in the table.
    static string deleteKey;
    
public:
    Word* words; // Stores words.
    static int collision;
    myHash(int tableSize); // Creates a hash table that can store up to tableSize entries.
    //(Constructor)5 POINTS
    void insert(string); // Inserts w into the hash table. 15 POINTS
    long long int hashFunc(string); // Computes the hash value of w. 5 POINTS
    bool retrieve(string); // Finds index of a given word in the hash table, if it isn't in
    // the table, starts for spell checking and suggests similiar
    // words if any found. 30 POINTS
    bool remove(string s); // Removes given word from the dictionary. 15 POINTS
    // Getter
    int* search(string);
    void spellChecker(string);
    int getTableSize() { return this->tableSize; };
};

int myHash::totalEntries = 0;
int myHash::collision = 0;
string myHash::deleteKey = "####";
myHash::myHash(int tableSize)
{
    this->tableSize = tableSize;
}
void myHash::insert (string value)
{
    int localCollision = 0;
    if (totalEntries==tableSize)
    {
        cout<<"WARNING: There are no empty space in the hash table for the word: "<<value<<endl;
        localCollision = totalEntries;
        collision += localCollision;
    }
    else
    {
        totalEntries++;
        long long int key = hashFunc(value);
        cout<<"h(x) result is "<< key<< " for: "<<value<<endl;
        while (true) {
            if (words[key].getContent() == "" || words[key].getContent() == deleteKey)
            {
                words[key].setContent(value);
                cout<<"INSERT: The word '"<<value<<"' is put in the cell number "<<key<<endl;
                
                break;
            }
            else if(words[key].getContent() == value)
            {
                cout<<"WARNING: The word '"<<value<<"' is already in the dictionary!"<<endl;
                break;
            }
            else
            {
                collision++;
                localCollision++;
                key++;
                if (key==tableSize) {
                    key=0;
                }
            }
        }
    }
    cout<<"COLLISIONS :"<<localCollision<<endl;
    cout<<"-------------------------------------"<<endl;
}
long long int myHash::hashFunc(string value)
{
    long long int key=1;
    for (int i=0; i<value.length(); i++)
    {
        key *= value[i] - 0;
        key %= tableSize;
    }
    return key;
}
bool myHash::retrieve(string value)
{
    int* keyCol = search(value);
    int key = keyCol[0];
    int localCollision = keyCol[1];
    if (key==-1)
    {
        cout<<"WARNING: The word '"<<value<<"' couldn't be found in the dictionary"<<endl;
        spellChecker(value);
        cout<<"COLLISIONS :"<<localCollision<<endl;
        cout<<"-------------------------------------"<<endl;
    }
    else
    {
        cout<<"RETRIEVE: The word '"<<value<<"' found in the dictionary with index: "<<key<<endl;
        cout<<"COLLISIONS :"<<localCollision<<endl;
        cout<<"-------------------------------------"<<endl;
    }
    return true;
}
bool myHash::remove(string value)
{
    int* keyCol = search(value);
    int key = keyCol[0];
    int localCollision = keyCol[1];
    if (key==-1)
    {
        cout<<"WARNING: The word '"<<value<<"' couldn't be found in the dictionary"<<endl;
        cout<<"COLLISIONS :"<<localCollision<<endl;
        cout<<"-------------------------------------"<<endl;
        return false;
    }
    else
    {
        words[key].setContent(deleteKey);
        totalEntries--;
        cout<<"REMOVE: The word '"<<value<<"' is removed from the dictionary."<<endl;
        cout<<"COLLISIONS :"<<localCollision<<endl;
        cout<<"-------------------------------------"<<endl;
    }
    return true;
}

int* myHash::search(string value)
{
    int* keyCol;
    keyCol = new int[2];
    int localCollision=0;
    long long int key = hashFunc(value);
    while (true) {
        if (tableSize == localCollision || words[key].getContent() == "")
        {
            keyCol[0]=-1;
            keyCol[1]=localCollision;
            return keyCol;
        }
        else if (words[key].getContent() == value)
        {
            break;
        }
        else
        {
            collision++;
            localCollision++;
            key++;
            if (key==tableSize)
            {
                key=0;
            }
        }
    }
    keyCol[0]=key;
    keyCol[1]=localCollision;
    return keyCol;
}

void myHash::spellChecker(string value)
{
    bool bInit = false;
    int* keyCol;
    keyCol = new int[2];
    string temp;
    temp = value;
    for (int i=0; i<value.length(); i++)
    {
        for(int j=0;j<26;j++)
        {
            temp[i]='a'+j;
            //cout << temp <<endl;
            keyCol = search(temp);
            if (keyCol[0] != -1 && !bInit) {
                cout<<"Looking for possible suggestions."<<endl;
                cout<<"SUGGESTIONS for "<<value<<": ";
                bInit=true;
            }
            if (keyCol[0] != -1)
            {
                cout<<temp<<", ";
            }
        }
        temp = value;
    }
    if (bInit) {
        cout<<endl;
    }
}
