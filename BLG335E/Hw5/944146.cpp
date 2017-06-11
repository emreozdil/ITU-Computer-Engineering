//
//  main.cpp
//  Algo5
//
//  Created by Emre Özdil on 28/12/2016.
//  Copyright © 2016 Emre Özdil. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Node
{
private:
	char gender;
	char color;
	int age;
	string name;

public:
    Node(); 
	int numAdult;
	int numNonAdult;
    Node *parent;
    Node* left;
    Node* right;

	// Getter Methods
	char getGender() { return this->gender; };
	char getColor() { return this->color; };
	int getAge() { return this->age; };
	string getName() { return this->name; };

	//Setter Methods
	void setGender(char gender) { this->gender = gender; };
	void setColor(char color) { this->color = color; };
	void setAge(int age) { this->age = age; };
	void setName(string name) { this->name = name; };
};

class RedBlack
{
private:
	Node* root;
    Node* grandParent(Node*);
    Node* Uncle(Node*);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void insertCase1(Node*);
    void insertCase2(Node*);
    void insertCase3(Node*);
    void insertCase4(Node*);
    void insertCase5(Node*);
    
public:
    RedBlack();
    void insert(Node*);
    void print(Node*, int, char);
    string nthAdult(int);
    string nthNonAdult(int);

	// Getter Method
	Node* getRoot() { return this->root; };
};

RedBlack* readFile(char*);
void writeTree(RedBlack*);

int main(int argc, char** argv)
{
    char* fileName = argv[1];
	//char* fileName = "input.txt";
    RedBlack* redBlackTree = new RedBlack;
    redBlackTree = readFile(fileName);
    writeTree(redBlackTree);
    return 0;
}
          
RedBlack* readFile(char* fileName)
{
    string name;
    char gender;
    int age;
    RedBlack* tree = new RedBlack;
    char* inputFileName = fileName;
    ifstream inputStream;
    inputStream.open(inputFileName, ios::in);
    while(inputStream >> name >> gender >> age)
    {
        Node* node = new Node;
        node->setName(name);
        node->setGender(gender);
        node->setAge(age);
        if(age < 18)
        {
            node->numNonAdult++;
        }
        else
        {
            node->numAdult++;
        }
        tree->insert(node);
    }
    return tree;
}

void writeTree(RedBlack* tree)
{
    tree->print(tree->getRoot(), 0, 'M');
    cout << endl << endl;
    cout << "The 5th Adult is: " << tree->nthAdult(5) << endl;
    cout << "The 3th Non-Adult is: " << tree->nthNonAdult(3) << endl;
}

// Node constructor
Node::Node()
{
    color ='R';
    numAdult = 0;
    numNonAdult = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}

// RedBlack constructor
RedBlack::RedBlack()
{
    root = NULL;
}

void RedBlack::insert(Node *node)
{
    if (root == NULL)
    {
        root = node;
    }
    else
    {
        Node* traverse = root;
        while (true) {
            if(traverse->getName().compare(node->getName())>0)
            {
                if (traverse->left == NULL)
                {
                    node->parent = traverse;
                    traverse->left = node;
                    break;
                }
                else
                {
                    traverse = traverse->left;
                }
            }
            else
            {
                if (traverse->right == NULL)
                {
                    node->parent = traverse;
                    traverse->right = node;
                    break;
                }
                else
                {
                    traverse = traverse->right;
                }
            }
        }
        while (traverse) {
            if (node->getAge() < 18) {
				traverse->numNonAdult++;
            }
            else
            {
				traverse->numAdult++;
            }
            traverse = traverse->parent;
        }
    }
    insertCase1(node);
}

// Insert Cases
void RedBlack::insertCase1(Node * node)
{
    if(node->parent == NULL)
    {
        node->setColor('B');
    }
    else
    {
        insertCase2(node);
    }
}

void RedBlack::insertCase2(Node * node)
{
    if(node->parent->getColor() == 'B')
    {
        return;
    }
    else
    {
        insertCase3(node);
    }
}

void RedBlack::insertCase3(Node * node)
{
    Node* uncle = Uncle(node);
    Node* grandparent = grandParent(node);
    if((uncle != NULL) && (uncle->getColor() == 'R'))
    {
        node->parent->setColor('B');
        uncle->setColor('B');
        grandparent->setColor('R');
        insertCase1(grandparent);
    }
    else
    {
        insertCase4(node);
    }
}

void RedBlack::insertCase4(Node * node)
{
    Node* grandparent = grandParent(node);
	if ((node == node->parent->right) && (node->parent == grandparent->left))
    {
        rotateLeft(node->parent);
        node = node->left;
    }
	else if ((node == node->parent->left) && (node->parent == grandparent->right))
    {
        rotateRight(node->parent);
        node = node->right;
    }
    else
    {
        insertCase5(node);
    }
}

void RedBlack::insertCase5(Node * node)
{
    Node* grandparent = grandParent(node);
	node->parent->setColor('B');
    grandparent->setColor('R');
	if (node->parent->left == node)
    {
        rotateRight(grandparent);
    }
    else
    {
        rotateLeft(grandparent);
    }
}

// Grandpatent and Uncle
Node* RedBlack::grandParent(Node * node)
{
	if ((node) && (node->parent))
    {
        return node->parent->parent;
    }
    else
    {
        return NULL;
    }
}

Node* RedBlack::Uncle(Node * node)
{
    Node* grandparent = grandParent(node);
    if(grandparent == NULL)
    {
        return NULL;
    }
    else if(grandparent->left == node->parent)
    {
        return grandparent->right;
    }
    else
    {
        return grandparent->left;
    }
}

// Rotate functions
void RedBlack::rotateLeft(Node * node)
{
    Node* rightChild = node->right;
    if (node->parent == NULL)
    {
        root = rightChild;
    }
    else
    {
        if(node == node->parent->left)
        {
            node->parent->left = rightChild;
        }
        else
        {
            node->parent->right = rightChild;
        }
    }
    rightChild->parent = node->parent;
    node->right = rightChild->left;
    if(rightChild->left)
    {
        rightChild->left->parent = node;
    }
    rightChild->left = node;
    node->parent = rightChild;
    
    // The number of adult or nonadult calculation
    if(node->left)
    {
        rightChild->numAdult += node->left->numAdult;
        rightChild->numNonAdult += node->left->numNonAdult;
    }
    
    if(node->right)
    {
        node->numAdult -= rightChild->right->numAdult;
        node->numNonAdult -= rightChild->right->numNonAdult;
    }
	if (node->getAge() < 18)
    {
        rightChild->numNonAdult++;
    }
    else
    {
        rightChild->numAdult++;
    }
	if (rightChild->getAge() < 18)
    {
        node->numNonAdult--;
    }
    else
    {
        node->numAdult--;
    }
}

void RedBlack::rotateRight(Node * node)
{
    Node* leftChild = node->left;
    if (node->parent == NULL)
    {
        root = leftChild;
    }
    else
    {
        if(node == node->parent->left)
        {
            node->parent->left = leftChild;
        }
        else
        {
            node->parent->right = leftChild;
        }
    }
    leftChild->parent = node->parent;
    node->left = leftChild->right;
    if(leftChild->right)
    {
        leftChild->right->parent = node;
    }
    leftChild->right = node;
    node->parent = leftChild;
    
    // The number of adult or nonadult calculation
    if(node->right)
    {
        leftChild->numAdult += node->right->numAdult;
        leftChild->numNonAdult += node->right->numNonAdult;
    }
    if(node->left)
    {
        node->numAdult -= leftChild->left->numAdult;
        node->numNonAdult -= leftChild->left->numNonAdult;
    }
	if (node->getAge() < 18)
    {
        leftChild->numNonAdult++;
    }
    else
    {
        leftChild->numAdult++;
    }
	if (leftChild->getAge() < 18)
    {
        node->numNonAdult--;
    }
    else
    {
        node->numAdult--;
    }
}

//Print preorder style
void RedBlack::print(Node * node, int depth, char direction)
{
    
    for (int i=0; i < depth; i++) {
       cout << "-";
    }
    cout << "(" << node->getColor() << ")" << node->getName() << " " << node->getGender() << " "<< node->getAge() << endl;
    if (node->left)
    {
        //cout<<"left"<<endl;
        print(node->left, depth+1, 'L');
        
    }
    if (node->right)
    {
        //cout<<"right"<<endl;
        print(node->right, depth+1, 'R');
    }
}

// Calculate Adult and non-Adult
string RedBlack::nthAdult(int index)
{
    Node* traverse = root;
    while (true)
    {
        if (traverse->left)
        {
            if (index <= traverse->left->numAdult)
            {
                traverse = traverse->left;
                continue;
            }
            else if ((traverse->getAge() >= 18) && (index == traverse->left->numAdult+1))
            {
                return traverse->getName();
            }
            else
            {
                index -= traverse->left->numAdult;
            }
        }
        else if ((traverse->getAge() >= 18) && (index == 1))
        {
            return traverse->getName();
        }
        if (traverse->getAge() >= 18)
        {
            index--;
        }
        traverse = traverse->right;
    }
}

string RedBlack::nthNonAdult(int index)
{
    Node* traverse = root;
    while (true)
    {
        if (traverse->left)
        {
            if (index <= traverse->left->numNonAdult)
            {
                traverse = traverse->left;
                continue;
            }
            else if ((traverse->getAge() < 18) && (index == traverse->left->numNonAdult+1))
            {
                return traverse->getName();
            }
            else
            {
                index -= traverse->left->numNonAdult;
            }
        }
        else if ((traverse->getAge() < 18) && (index == 1))
        {
            return traverse->getName();
        }
        if (traverse->getAge() < 18)
        {
            index--;
        }
        traverse = traverse->right;
    }
}
