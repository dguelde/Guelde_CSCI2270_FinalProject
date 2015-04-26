// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// declare RadBlackTree class

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>

struct RBTreeNode{
	std::string word;
	int length;
	RBTreeNode *parent;
	RBTreeNode *left;
	RBTreeNode *right;
	bool isRed;

	RBTreeNode(){};

	RBTreeNode(std::string in_word, int in_length)
	{
		word = in_word;
		left = NULL;
		right = NULL;
		parent = NULL;
		isRed = true;
	}

};

class RBTree
{
	int opCount;

public:
	RBTree();
	virtual ~RBTree();
	void rbEditWord(std::string oldSpelling, std::string newSpelling);
	void rbAddWord(std::string word);
	std::string rbFindWord(std::string word);
	void rbDeleteWord(std::string word);
	void isValid();
	void showRoot();
	void resetOpCount();
	void emptyTree();
	int getOpCount();

private:
	void emptyTree(RBTreeNode* x);
	RBTreeNode* findWord(RBTreeNode*, std::string);
	void rbAddFixup(RBTreeNode* x);
	void leftRotate(RBTreeNode* x);
	void rbDelete(RBTreeNode* x);
	void rightRotate(RBTreeNode* x);
	void rbDeleteFixup(RBTreeNode* x);
	void rbTransplant(RBTreeNode *x, RBTreeNode*y);
	int rbValid(RBTreeNode *x);
	RBTreeNode *root;
	RBTreeNode *nil;

};


#endif // REDBLACKTREE_H