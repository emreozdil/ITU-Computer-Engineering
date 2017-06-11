#ifndef tree_H
#define tree_H

struct node {
	int number;
	node* left;
	node* right;
};

struct tree {
	node *root;
	void add(int);
	void createTree();
	void removeTree(node *);
	void printInorder(node*);
	int findNumNode(node *);
	int temp_recursive;
};
#endif // !tree


