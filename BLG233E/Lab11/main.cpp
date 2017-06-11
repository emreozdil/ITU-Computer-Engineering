//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <climits>
#include "tree.h"
#include "queue.h"
#include "stack.h"

using namespace std;

tree agac;
Stack cuval;
Queue kuyruk;

int c = 0, step=-1;
void inorder(node*, int );
int bfs(node*, int);
int dfs(node*, int);
int main()
{
	agac.createTree();
	int x;
	cout << "aranacak sayiyi gir: ";
	cin >> x;
	cout << "BFS: " <<  bfs(agac.root, x) << endl;
	cout << "DFS: " <<  dfs(agac.root, x) << endl;
	inorder(agac.root, x);
	cout << "INORDER: " << step << endl;
	system("pause");
}

void inorder(node *root, int x)
{
	if (root) {
		inorder(root->left,x);
		c++;
		cout << root->number << "\t";
		if (root->number == x)
			step = c;
		inorder(root->right,x);
	}
}

int bfs(node *root, int x)
{
	node *u;
	int counter = 0;
	kuyruk.create();
	kuyruk.enqueue(root);
	while (!kuyruk.isempty())
	{
		counter++;
		u = kuyruk.front->data;
		cout << u->number << "\t";
		if (u->number == x)
			return counter;
		kuyruk.dequeue();
		if (u->left)
			kuyruk.enqueue(u->left);
		if (u->right)
			kuyruk.enqueue(u->right);
	}
	return -1;
}

int dfs(node *root, int x)
{
	node* u;
	int counter=0;
	cuval.create();
	cuval.push(root);
	while (!cuval.isempty())
	{
		counter++;
		u = cuval.head->data;
		cout << u->number << "\t";
		if (u->number == x)
			return counter;
		cuval.pop();
		if (u->right)
			cuval.push(u->right);
		if (u->left)
			cuval.push(u->left);		
	}
	return -1;
}
