//
//  main.cpp
//  Academicians
//
//  Created by Emre Özdil on 10/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#include "reviewer.h"
#include "publication.h"
#include "graph.h"



void readPublication(Graph*, string);
void readReviewer(Graph*, string);

int main(int argc, const char ** argv)
{
    Graph *academic;
    academic = new Graph();
    
    string reviewer;
    reviewer = argv[1];
    // reviewer = "reviewer.txt";
    readReviewer(academic, reviewer);
    
    string publication;
    publication = argv[2];
    // publication = "publications.txt";
    readPublication(academic, publication);
    
    academic->createGraph();
    academic->fordFulkerson();
    academic->output();
    
    return 0;
}

void readPublication(Graph* academic, string in)
{
    // input File
    ifstream inputStream;
    const char* input = in.c_str();
    inputStream.open(input, ios::in);
    int size;
    string publicationName;
    // read Publications
    inputStream >> size;
    Publication *tempPublication;
    while (inputStream>>publicationName)
    {
        tempPublication = new Publication(publicationName);
        academic->publications.pb(tempPublication);
    }
    inputStream.close();
}
void readReviewer(Graph* academic, string in)
{
    // input File
    ifstream inputStream;
    const char* input = in.c_str();
    inputStream.open(input, ios::in);
    int size;
    string reviewerName;
    int numberOfReview;
    // read Reviewers
    inputStream >> size;
    Reviewer *tempReviewer;
    while (inputStream>>reviewerName>>numberOfReview)
    {
        tempReviewer = new Reviewer(reviewerName, numberOfReview);
        academic->reviewers.pb(tempReviewer);
    }
    inputStream.close();
}

