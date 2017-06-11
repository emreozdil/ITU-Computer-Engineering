//
//  reviewer.h
//  Academicians
//
//  Created by Emre Özdil on 10/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#pragma once

#include <iostream>

using namespace std;

class Reviewer
{
    string name;
    int type;
    int numberOfReview;
    
public:
    Reviewer(string name, int numberOfReview)
    {
        if (name[0]=='P' || name[0]=='p')
        {
            this->name = name;
            this->type = 1;
            this->numberOfReview = numberOfReview;
        }
        else if (name[3]=='P' || name[3]=='p')
        {
            this->name = name;
            this->type = 2;
            this->numberOfReview = numberOfReview;
        }
        else
        {
            this->name = name;
            this->type = 3;
            this->numberOfReview = numberOfReview;
        }
    }
    int getNumberOfReview() { return this->numberOfReview; }
    int getType() { return this->type; }
    string getName() { return this->name; }
};
