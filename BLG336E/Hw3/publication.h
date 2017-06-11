//
//  publication.h
//  Academicians
//
//  Created by Emre Özdil on 10/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Publication
{
    string name;
    int type;
    int need;
    
public:
    Publication(string name)
    {
        if (name[0]=='J' || name[0]=='j')
        {
            this->name = name;
            this->type = 1;
            this->need = 2;
        }
        else if (name[0]=='C' || name[0]=='c')
        {
            this->name = name;
            this->type = 2;
            this->need = 3;
        }
        else
        {
            this->name = name;
            this->type = 3;
            this->need = 2;
        }
    }
    int getNeed() { return this->need; }
    int getType() { return this->type; }
    string getName() { return this->name; }
    vector<Reviewer*> reviewerList;
    
};
