//
//  node.h
//  Rush Hour
//
//  Created by Emre Özdil on 10/03/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct Nodes;
struct Car
{
    int id;
    char direction;
    int length;
};

struct Maze
{
    vector< vector<int> > maze;
};

class Node
{
public:
    Node();
    ~Node();
    vector< vector<int> > maze;
    Nodes* below;
    Node* above;
private:
    
};

Node::Node()
{
    this->below = NULL;
}

Node::~Node()
{
}



struct Nodes
{
    vector<Node*> nodes;
    Node *above;
};


