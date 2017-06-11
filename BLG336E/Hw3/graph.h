//
//  graph.hpp
//  Academicians
//
//  Created by Emre Özdil on 10/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include "reviewer.h"
#include "publication.h"

#define pb push_back

using namespace std;

class Graph {
    int **matrix;
    int reviewersSize;
    int publicationsSize;
    int totalNode;
public:
    vector<Publication*> publications;
    vector<Reviewer*> reviewers;
    void createGraph();
    bool bfs(int *, int, int);
    int fordFulkerson();
    void output();
};
