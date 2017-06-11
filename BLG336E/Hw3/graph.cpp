//
//  graph.cpp
//  Academicians
//
//  Created by Emre Özdil on 10/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#include "graph.h"

void Graph::createGraph()
{
    reviewersSize = reviewers.size();
    publicationsSize = publications.size();
    totalNode = 1 + reviewersSize + publicationsSize + 1;
    matrix = new int*[totalNode];
    for (int i = 0; i < totalNode; i++)
        matrix[i] = new int[totalNode];
    for (int i = 0; i < totalNode; i++)
    {
        for (int j = 0; j < totalNode; j++)
            matrix[i][j] = 0;
    }
    // Source-Reviewer Relations
    for (int i = 0; i < reviewersSize; i++)
        matrix[0][1 + i] = reviewers[i]->getNumberOfReview();

    // Publication-Sink Relations
    for (int i = 0; i < publicationsSize; i++)
        matrix[1 + reviewersSize + i][totalNode - 1] = publications[i]->getNeed();
    
    // Reviewer-Publication Relations
    for (int i = 0; i < reviewersSize; i++)
    {
        for (int j = 0; j < publicationsSize; j++)
        {
            if (publications[j]->getType() >= reviewers[i]->getType())
                matrix[1 + i][1 + reviewersSize + j] = 1;
        }
    }

}

// Breadth-First Search
bool Graph::bfs(int *graph, int first, int last)
{
    queue<int> bfsQueue;
    int index;
    int *nodes = new int[totalNode];
    bool *visited = new bool[totalNode];
    for (int i = 0; i < totalNode; i++)
        visited[i] = false;
    index = first;
    bfsQueue.push(index);
    
    while (!bfsQueue.empty())
    {
        index = bfsQueue.front();
        bfsQueue.pop();
        
        for (int i = 0; i < totalNode; i++)
        {
            if (visited[i] == false && matrix[index][i] > 0)
            {
                visited[i] = true;
                bfsQueue.push(i);
                nodes[i] = index;
            }
        }
    }
    
    // check reach to sink
    if (visited[last])
    {
        for (int i = 0; i < totalNode; i++)
            graph[i] = nodes[i];
        delete[] visited;
        delete[] nodes;
        return true;
    }

    delete[] visited;
    delete[] nodes;
    
    return false;
}

// Ford-Fulkerson Algorithm
int Graph::fordFulkerson()
{
    int* traverse;
    traverse = new int[totalNode];
    
    int index;
    int parentIndex;
    int pathFlow;
    
    while (bfs(traverse, 0, totalNode-1))
    {
        index = totalNode-1;
        pathFlow = INT_MAX;
        int publicationNumber = -1;
        
        while (index != 0)
        {
            if (index > reviewersSize && index < totalNode-1)
                publicationNumber = index - (reviewersSize + 1);
            else if (index > 0 && index <= reviewersSize) // Output file
                publications[publicationNumber]->reviewerList.pb(reviewers[index-1]);
            
            parentIndex = traverse[index];
            if (pathFlow > matrix[parentIndex][index])
                pathFlow = matrix[parentIndex][index];
            
            index = traverse[index];
        }

        index = totalNode-1;
        while (index != 0)
        {
            parentIndex = traverse[index];
            matrix[parentIndex][index] -= pathFlow;
            matrix[index][parentIndex] += pathFlow;
            index = traverse[index];
        }
    }
    
    delete[] traverse;
    
    return 0;
}

void Graph::output()
{
    ofstream outputStream;
    outputStream.open("output.txt", ios::out);
    for (int i = 0 ; i < publicationsSize; i++)
    {
        if (publications[i]->reviewerList.size() == 0)
        {
            outputStream<<publications[i]->getName()<<" is NOT assigned. ";
            outputStream<<endl;
        }
        else
        {
            outputStream<<publications[i]->getName()<<" is assigned to ";
            int j;
            for (j = 0; j < publications[i]->reviewerList.size(); j++)
            {
                outputStream<<publications[i]->reviewerList[j]->getName();
                if(j + 1 == publications[i]->getNeed())
                    outputStream << ".";
                else
                    outputStream<< ", ";
            }
            if(j != publications[i]->getNeed())
                outputStream<< "even if the number of reviewers is not enough for the current publication to be accepted.";
            outputStream<<endl;
        }
    }
    outputStream.close();
}
