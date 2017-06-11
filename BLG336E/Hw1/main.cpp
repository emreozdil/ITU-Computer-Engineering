//
//  main.cpp
//  Rush Hour
//
//  Created by Emre Özdil on 10/03/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//
#include "node.h"
#define pb push_back
using namespace std;

void readFile(string, string, string);
void addBFSNode(Maze*, string);
void addDFSNode(Maze*, string);

set<vector< vector<int> > > allNodes;
stack<Node*> BFSstack;
queue<Node*> DFSqueue;
vector<Car*> cars;

int main(int argc, char ** argv)
{
    string algorithm;
    string inputName;
    string outputName;
    algorithm = argv[1];
    inputName = argv[2];
    outputName = argv[3];
    //algorithm = "bfs";
    //inputName = "blocks.txt";
    //outputName = "BFS.txt";
    readFile(algorithm, inputName, outputName);
    return 0;
}

// Read txt
void readFile(string algorithm, string in, string out)
{
    
    ifstream inputStream;
    const char* input = in.c_str();
    inputStream.open(input, ios::in);
    int xCordinate;
    int yCordinate;
    int length;
    char direction;
    vector< vector<int> > maze(6, vector<int>(6));
    
    int counter = 1;
    
    Car *newCar;
    while (inputStream >> xCordinate >> yCordinate >> length >> direction)
    {
        newCar = new Car();
        newCar->id = counter;
        newCar->direction = direction;
        newCar->length = length;
        cars.pb(newCar);
        int x = xCordinate - 1;
        int y = yCordinate - 1;
        maze[x][y] = counter;
        if (direction == 'v')
        {
            while (--length)
            {
                maze[--x][y] = counter;
            }
        }
        else
        {
            while (--length)
            {
                maze[x][++y] = counter;
            }
        }
        counter++;
    }
    Maze *newMaze = new Maze;
    newMaze->maze = maze;
    if (algorithm == "bfs" || algorithm == "BFS")
    {
        addBFSNode(newMaze, out);
    }
    else if (algorithm == "dfs" || algorithm == "DFS")
    {
        addDFSNode(newMaze, out);
    }
    else
    {
        cout<<"Wrong algorithm"<<endl;
    }
}

/**
 **
 ** BFS
 **
 */

void addBFSNode(Maze* maze, string out)
{
    allNodes.insert(maze->maze);
    //Maze *x;
    //for (std::set<Maze*>::iterator it = allNodes.begin(); it != allNodes.end(); ++it)
    // x = *it;
    Node *head = new Node;
    head->maze = maze->maze;
    Nodes *row = new Nodes;
    head->above = NULL;
    head->below = row;
    row->above = head;
    Node *nNode = new Node;
    vector< vector<int> > tempMaze = maze->maze;
    int id;
    int flagUp=0;
    int flagRight=0;
    int tempInumber;
    int tempJnumber;
    int rowNumber =0;
    int rowBelowNumber =0;
    // BFS ekleme
    bool finish = false;
    while(!finish)
    {
        Nodes *tempRow = new Nodes;
        // BFS traverse
        if(row->nodes.size())
        {
            if (row->nodes.size() == rowNumber)
            {
                if (rowBelowNumber == 0)
                {
                    row = row->nodes[rowBelowNumber]->below;
                    rowNumber = 0;
                    rowBelowNumber++;
                }
                else if (rowBelowNumber != 0 && row->above->above->below->nodes.size() == rowBelowNumber)
                {
                    rowBelowNumber = 0;
                    row = row->above->above->below->nodes[rowBelowNumber]->below->nodes[rowBelowNumber]->below ;
                    rowNumber = 0;
                }
                else
                {
                    row = row->above->above->below->nodes[rowBelowNumber]->below;
                    rowNumber = 0;
                    rowBelowNumber++;
                }
                
            }
            maze->maze = row->nodes[rowNumber]->maze;
            row->nodes[rowNumber]->below = tempRow;
            tempRow->above = row->nodes[rowNumber];
            rowNumber++;
        }
        else
        {
            tempRow = row;
        }
        
        id = 0;
        flagUp=0;
        flagRight=0;
        tempMaze = maze->maze;
        for (int j = 5; j>=0; j--)
        {
            if (finish)
                break;
            for (int i = 0; i<6; i++)
            {
                if (maze->maze[i][j])
                {
                    id = maze->maze[i][j];
                    
                    // HORIZONTAL
                    if (cars[id - 1]->direction == 'h')
                    {
                        // Go right
                        if (j<5 && maze->maze[i][j + 1] == 0 && id != flagRight)
                        {
                            maze->maze[i][j + 1] = id;
                            tempInumber = i-1;
                            tempJnumber = j;
                            while (j != 0)
                            {
                                flagRight = id;
                                if (maze->maze[i][j - 1] == id)
                                {
                                    j--;
                                }
                                else
                                {
                                    maze->maze[i][j] = 0;
                                    break;
                                }
                            }
                            if(j == 0)
                                maze->maze[i][j] = 0;
                            i = tempInumber;
                            j = tempJnumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                nNode->above = tempRow->above;
                                nNode->below = NULL;
                                tempRow->nodes.pb(nNode);
                                if (maze->maze[2][5]==1)
                                {
                                    BFSstack.push(nNode);
                                    finish = true;
                                    break;
                                }
                            }
                            maze->maze = tempMaze;
                        }
                        
                        // Go left
                        else if (j>0 && maze->maze[i][j + 1] != id)
                        {
                            tempJnumber = j;
                            while (j != 0)
                            {
                                if (maze->maze[i][j - 1] == id)
                                {
                                    j--;
                                }
                                else if (maze->maze[i][j - 1] == 0)
                                {
                                    maze->maze[i][j - 1] = id;
                                    maze->maze[i][tempJnumber] = 0;
                                    i++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            j = tempJnumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                nNode->above = tempRow->above;
                                nNode->below = NULL;
                                tempRow->nodes.pb(nNode);
                            }
                            maze->maze = tempMaze;
                        }
                    }
                    
                    // VERTICAL
                    else if (cars[id - 1]->direction == 'v')
                    {
                        // Go up
                        if (i>0 && maze->maze[i - 1][j]==0 && id != flagUp)
                        {
                            maze->maze[i - 1][j] = id;
                            tempInumber = i-1;
                            while (i!=5)
                            {
                                flagUp = id;
                                if (maze->maze[i + 1][j] == id)
                                {
                                    i++;
                                }
                                else
                                {
                                    maze->maze[i][j] = 0;
                                    break;
                                }
                            }
                            if(i==5)
                                maze->maze[i][j] = 0;
                            i = tempInumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                nNode->above = tempRow->above;
                                nNode->below = NULL;
                                tempRow->nodes.pb(nNode);
                                maze->maze = tempMaze;
                            }
                            else
                            {
                                maze->maze = tempMaze;
                            }
                        }
                        // Go down
                        else if (i < 5 && (i==0 || maze->maze[i - 1][j] != id))
                        {
                            tempInumber = i;
                            while (i != 5)
                            {
                                if (maze->maze[i + 1][j] == id)
                                {
                                    i++;
                                }
                                else if (maze->maze[i + 1][j] == 0)
                                {
                                    maze->maze[i + 1][j] = id;
                                    maze->maze[tempInumber][j] = 0;
                                    i++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                nNode->above = tempRow->above;
                                nNode->below = NULL;
                                tempRow->nodes.pb(nNode);
                            }
                            maze->maze = tempMaze;
                        }
                    }
                }
            }
        }
    }
    nNode = nNode->above;
    while (nNode)
    {
        BFSstack.push(nNode);
        nNode = nNode->above;
    }
    const char* output = out.c_str();
    ofstream outputStream;
    outputStream.open(output, ios::out | ios::trunc);
    while (!BFSstack.empty())
    {
        Node* path = new Node;
        path = BFSstack.top();
        BFSstack.pop();
        bool flag =false;
        
        // Print cars
        for (int i = 0; i<cars.size(); i++)
        {
            flag =false;
            for (int k = 5; k>=0; k--)
            {
                for (int l = 0; l<6; l++)
                {
                    if (path->maze[k][l] == i+1)
                    {
                        outputStream<< k + 1 <<" "<< l + 1 << " " << cars[i]->length <<" " <<cars[i]->direction;
                        outputStream << endl ;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
        }
        outputStream<<endl;
    }
    outputStream.close();
}

/**
 **
 ** DFS
 **
 */

void addDFSNode(Maze* maze, string out)
{
    allNodes.insert(maze->maze);
    Node *nNode = new Node;
    nNode->maze = maze->maze;
    DFSqueue.push(nNode);
    vector< vector<int> > tempMaze = maze->maze;
    int id;
    int tempInumber;
    int tempJnumber;
    // DFS ekleme
    bool finish = false;
    while(!finish)
    {
        id = 0;
        for (int j = 5; j>=0; j--)
        {
            if (finish)
                break;
            for (int i = 0; i<6; i++)
            {
                tempMaze = maze->maze;
                
                if (maze->maze[i][j])
                {
                    id = maze->maze[i][j];
                    
                    // HORIZONTAL
                    if (cars[id - 1]->direction == 'h')
                    {
                        // Go right
                        while (j<5 && maze->maze[i][j + 1] == 0)
                        {
                            maze->maze[i][j + 1] = id;
                            tempInumber = i;
                            tempJnumber = j + 1;
                            while (j != 0)
                            {
                                if (maze->maze[i][j - 1] == id)
                                {
                                    j--;
                                }
                                else
                                {
                                    maze->maze[i][j] = 0;
                                    break;
                                }
                            }
                            if(j == 0)
                                maze->maze[i][j] = 0;
                            i = tempInumber;
                            j = tempJnumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                DFSqueue.push(nNode);
                                tempMaze = maze->maze;
                                if (maze->maze[2][5]==1)
                                {
                                    finish = true;
                                    break;
                                }
                            }
                            else
                            {
                                maze->maze = tempMaze;
                                break;
                            }
                        }
                        if (finish)
                            break;
                        
                        // Go left
                        while (j>0 && (j==5 || maze->maze[i][j + 1] != id))
                        {
                            tempJnumber = j;
                            while (j != 5) // j!= 0 dene
                            {
                                if (maze->maze[i][j - 1] == id)
                                {
                                    j--;
                                }
                                else if (maze->maze[i][j - 1] == 0)
                                {
                                    maze->maze[i][j - 1] = id;
                                    maze->maze[i][tempJnumber] = 0;
                                    i++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            j = tempJnumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                DFSqueue.push(nNode);
                                tempMaze = maze->maze;
                            }
                            else
                            {
                                maze->maze = tempMaze;
                                break;
                            }
                        }
                    }
                    
                    // VERTICAL
                    else if (cars[id - 1]->direction == 'v')
                    {
                        // Go up
                        while (i>0 && maze->maze[i - 1][j]==0)
                        {
                            maze->maze[i - 1][j] = id;
                            tempInumber = i-1;
                            while (i!=5)
                            {
                                if (maze->maze[i + 1][j] == id)
                                {
                                    i++;
                                }
                                else
                                {
                                    maze->maze[i][j] = 0;
                                    break;
                                }
                            }
                            if(i==5)
                                maze->maze[i][j] = 0;
                            i = tempInumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                DFSqueue.push(nNode);
                                tempMaze = maze->maze;
                            }
                            else
                            {
                                maze->maze = tempMaze;
                                break;
                            }
                        }
                        // Go down
                        while (i < 5 && (i==0 || maze->maze[i - 1][j] != id))
                        {
                            tempInumber = i;
                            while (i != 5)
                            {
                                if (maze->maze[i + 1][j] == id)
                                {
                                    i++;
                                }
                                else if (maze->maze[i + 1][j] == 0)
                                {
                                    maze->maze[i + 1][j] = id;
                                    maze->maze[tempInumber][j] = 0;
                                    i++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            i=tempInumber;
                            if (allNodes.find(maze->maze) == allNodes.end()) // if this maze is not exist insert row and allNodes set
                            {
                                allNodes.insert(maze->maze);
                                nNode = new Node;
                                nNode->maze = maze->maze;
                                DFSqueue.push(nNode);
                                tempMaze = maze->maze;
                                i++;
                            }
                            else
                            {
                                maze->maze = tempMaze;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    const char* output = out.c_str();
    ofstream outputStream;
    outputStream.open(output, ios::out | ios::trunc);
    while (!DFSqueue.empty())
    {
        Node* path = new Node;
        path = DFSqueue.front();
        DFSqueue.pop();
        bool flag =false;
        
        // Print cars
        for (int i = 0; i<cars.size(); i++)
        {
            flag =false;
            for (int k = 5; k>=0; k--)
            {
                for (int l = 0; l<6; l++)
                {
                    if (path->maze[k][l] == i+1)
                    {
                        outputStream<< k + 1 <<" "<< l + 1 << " " << cars[i]->length <<" " <<cars[i]->direction;
                        outputStream << endl ;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
        }
        outputStream<<endl;
    }
    outputStream.close();
}
