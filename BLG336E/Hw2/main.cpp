//
//  main.cpp
//  Parser
//
//  Created by Emre Özdil on 20/04/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

#define pb push_back
using namespace std;

void operationFile(string);
void convert(string);
void extractParseTree(int);

string match(string, string);

vector<string> structure;
vector<string> sentence;
vector<string> result;

int main(int argc, const char * argv[]) {
    string input;
    input = argv[1];
    //input = "input.txt";
    operationFile(input);
    return 0;
}

void operationFile(string in)
{
    // input File
    ifstream inputStream;
    const char* input = in.c_str();
    inputStream.open(input, ios::in);
    // output File
    ofstream outputStream;
    outputStream.open("output.txt", ios::out);
    string word;
    // read line by line
    while (getline(inputStream,word))
    {
        structure.clear();
        sentence.clear();
        result.clear();
        string tempWord;
        for (int i = 0; i < word.size(); i++) {
            if(word[i] != ' ' && word[i] != '\n' && word[i] != '\r'){
                tempWord += word[i];
            }
            else {
                transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower);
                sentence.pb(tempWord);
                convert(tempWord);
                tempWord = "";
            }
        }
        // end of text ( last line)
        if(tempWord != "") {
            transform(tempWord.begin(), tempWord.end(), tempWord.begin(), ::tolower);
            sentence.pb(tempWord);
            convert(tempWord);
            tempWord = "";
        }
        for (int i = 0; i < sentence.size(); i++) {
            result.pb(structure[i] + '(' + sentence[i] +')');
        }
        int initialSize = structure.size();
        
        while(true) {
            initialSize = structure.size();
            extractParseTree(structure.size());
            if(initialSize == structure.size()){
                outputStream<<"SYNTAX ERROR"<<endl;
                break;
            }
            else if ( structure.size() == 1){
                outputStream<<result[0]<<endl;
                break;
            }
        }
        
    }
}

void convert(string word){
    /*
     POS Tags of Words:
     
     DT → that | this | a | the
     NN → book | flight | cat | mat | I | you | they
     VR → booked | included | preferred | sat
     PR → from | to | on | near | through
     AD → big | heavy | beautiful | cheap
     
     */
    
    if (word == "that" || word == "this" || word == "a" || word == "the") {
        structure.pb("DT");
    }
    else if (word == "book" || word == "flight" || word == "cat" || word == "mat" || word == "i" || word == "you" || word == "they") {
        structure.pb("NN");
    }
    else if (word == "booked" || word == "included" || word == "preferred" || word == "sat") {
        structure.pb("VR");
    }
    else if (word == "from" || word == "to" || word == "on" || word == "near" || word == "through") {
        structure.pb("PR");
    }
    else if (word == "big" || word == "heavy" || word == "beautiful" || word == "cheap") {
        structure.pb("AD");
    }
}
void extractParseTree(int index)
{
    string temp;
    string concat;
    if(index-2 >= 0){
        temp = match(structure[index-2], structure[index-1]);
        if(temp != "noMatch") {
            structure.erase(structure.begin() + (index-1));
            structure[index-2] =temp;
            concat = temp + "[" + result[index-2] + result[index-1] + "]";
            result.erase(result.begin() + (index-1));
            result[index-2] = concat;
            
            extractParseTree(index-1);
        }
        else {
            extractParseTree(index-1);
        }
    }
}

string match(string left, string right){
    /*
     Grammar and Binary/Positional Transformation Rules:
     NP → NN NN     NP → AD NN      NP → AD NP      NP → DT NP      NP → DT NN
     PP → PR NN     PP → PR NP
     VP → VR PP     VP → NN VR      VP → NP VR      VP → VR NP
     S → NP VP      S → NN VP
     */
    if(left == "NN"){
        if(right == "NN")
            return "NP";
        else if(right == "VR")
            return "VP";
        else if(right == "VP" && structure.size()==2)
            return "S";
    }
    else if(left == "PR"){
        if(right == "NN")
            return "PP";
        else if(right == "NP")
            return "PP";
    }
    else if(left == "VR"){
        if(right == "PP")
            return "VP";
        else if(right == "NP")
            return "VP";
    }
    else if(left == "NP"){
        if(right == "VP" && structure.size()==2)
            return "S";
        else if(right == "VR")
            return "VP";
    }
    else if(left == "AD"){
        if(right == "NN")
            return "NP";
        else if(right == "NP")
            return "NP";
    }
    else if(left == "DT"){
        if(right == "NP")
            return "NP";
        else if(right == "NN")
            return "NP";
    }
    return "noMatch";
}
