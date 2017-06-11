//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <climits>
#include "tree.h"

using namespace std;

bool add();
void PrintMenu();

tree agac;

int main() {
	tree tree;
	tree.createTree();
	cout << endl << "Postorder:   ";
	tree.printPostorder(tree.root);
	cout << endl << "Inorder:   ";
	tree.printInorder(tree.root);
	cout << endl << "Preorder:   ";
	tree.printPreorder(tree.root);
	
	cout << endl;
	tree.temp_recursive = INT_MIN;
	cout << endl << "Max:   " << tree.findMax(tree.root) << endl;

	tree.temp_recursive = INT_MAX;
	cout << endl << "Min:   " << tree.findMin(tree.root) << endl;

	tree.temp_recursive = 0;
	cout << endl << "Node Number:   " << tree.findNumNode(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << "Sum: " << tree.calculateSum(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << "Average: " << tree.calculateAverage(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << "Leaf Number:   " << tree.findNumLeaf(tree.root) << endl;
	
	tree.temp_recursive = 0;
	cout << "Depth:   " << tree.calculateDepth() << endl;

	tree.removeTree(tree.root);
	system("pause");
	return 0;
}
