//
//  word.h
//  Algo4
//
//  Created by Emre Özdil on 11/12/16.
//  Copyright © 2016 Emre Özdil. All rights reserved.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Word
{
private:
    string content;
    
public:
    Word(){};
    
    // Getter
    string getContent(){ return this->content; };
    
    // Setter
    void setContent(string content) { this->content = content; };
};

