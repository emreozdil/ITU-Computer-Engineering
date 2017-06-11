#include <iostream>
#include <ctime>
#include "tree.h"
using namespace std;

void tree::createTree() {
	srand(time(NULL));
	root = NULL;
	temp_recursive = 0;
	cout << "Enter number to find a node in Tree: ";
	int N, random;
	cin >> N;
	int *RandomArray = new int[N];
	int *check = new int[N];
	for (int i = 0; i < N; i++)
	{
		check[i] = 0;
	}
	for (int i = 0; i < N; i++) {
		random = rand() % N;
		if (check[random]==0)
		{
			check[random] = 1;
			RandomArray[i] = random + 1;
			cout << RandomArray[i] << endl;
			add(RandomArray[i]);
		}
		else	i--;		
	}
}

void tree::removeTree(node *p) {
	if (p) {
		if (p->left != NULL) {
			removeTree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			removeTree(p->right);
			p->right = NULL;
		}
		delete p;
	}
}

void tree::add(int toadd) {  //Binary tree, Binary search tree de?il!!!!  (d-1) bo?ken (d)'ye eleman eklemez
	node *traverse, *newnode;
	traverse = root;
	int comparison;
	bool added = false;
	newnode = new node;
	newnode->number = toadd;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL) {//first node being added
		root = newnode;
		return;
	}
	if (root->left == NULL) {
		root->left = newnode;
		return;
	}
	if (root->right == NULL) {
		root->right = newnode;
		return;
	}

	int l, r;

	while (findNumNode(traverse)>2) {
		temp_recursive = 0;
		l = findNumNode(traverse->left);
		temp_recursive = 0;
		r = findNumNode(traverse->right);
		temp_recursive = 0;
		if (l < r)
			traverse = traverse->left;
		else if (l>r)
			traverse = traverse->right;
		else
			traverse = traverse->left;
	}

	if (traverse->left == NULL) {
		traverse->left = newnode;
		return;
	}

	if (traverse->right == NULL) {
		traverse->right = newnode;
		return;
	}
}

void tree::printInorder(node *nptr) {
	if (nptr) {
		printInorder(nptr->left);
		cout << nptr->number << " ";
		printInorder(nptr->right);
	}
}

int tree::findNumNode(node* ptr) {
	if (ptr) {
		temp_recursive++;
		findNumNode(ptr->left);
		findNumNode(ptr->right);
	}
	return temp_recursive;
}
