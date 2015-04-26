// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// define functions for RedBlackTree class

#include "RedBlackTree.h"
#include <iomanip>


/*
Prototype:

Description:  constructor for class RBTree.  Doesn't do much except fill in values for 'nil' node root

Example:
RBTree Treename;

Precondition:
None

Post condition:
An instance of class RBTree is created
*/
RBTree::RBTree()
{
	nil = new RBTreeNode;
	root=nil;
	nil->isRed=false;
	nil->parent = nil;
	nil->left=nil;
	nil->right=nil;
	nil->word = "nil";
}

RBTree::~RBTree()
{}

/*
Prototype:
void RBTree::rbAddWord(std::string word);
Description:
Takes user input, searches red-black tree for proper place, creates new node, and inserts node into red-black tree.  Calls
other functions to maintain red-black properties
Example:
RBTree Tree;
Tree.rbAddWord("cat");

Precondition:
instance of class must exist.  Node is created and sorted alphabetically by input word

Post condition:
New word is inserted into red-black tree

**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::rbAddWord(std::string word)
{
	//create node to insert
    opCount++;
    
	int length = word.size();
	RBTreeNode* newWord = new RBTreeNode(word, length);
	//std::cout << newWord->word << std::endl;
	newWord->left = nil;
	newWord->right = nil;
	newWord->parent = nil;
	RBTreeNode* x = root;
	RBTreeNode* y = nil;

	//is tree empty?
	if (root == nil)
		{root = newWord;
            opCount++;
		root->isRed=false;}

	// if tree is not empty
	else
	{
        opCount++;
		// go to end of tree, where this node will be added
		while (x !=nil)
		{
            opCount++;
			y=x;
			if(newWord->word.compare(x->word)<0)
				{opCount++;
                    x=x->left;
                }
			else
				{opCount++;
                    x=x->right;}
		}

		// set parent of new node

		newWord->parent=y;
		//  set parent->(left or right)->newWord
		if (newWord->word < y->word)
			{opCount++;
                y->left = newWord;}
		else
			{opCount++;
                y->right = newWord;}
	}

	rbAddFixup(newWord);
	//int treeCheck=rbValid(x);
    //std::cout << treeCheck << std::endl;
    //std::cout << root->word << std::endl;
    std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
	return;
}

/*
Prototype:
void RBTree::rbAddFixup(RBTreeNode* x) 

Description:
ensures red-black properties are maintained after addition is performed

Example:
RBTree Tree;
Tree.rbAddFixup(&nodeN);

Precondition:
Red-Black Tree may or may not adhere to proper red-black tree properties after a node is addded.
The input is the node just added.

Postcondition;
Red-Black tree is reorganized to ensure red-black properties are intact

**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::rbAddFixup(RBTreeNode* x) //maintain red-black properties after addition
{
    opCount++;
	x->isRed=true;
	while ((x != root) && (x->parent->isRed==true) && (x->parent->parent!=nil))
	{opCount++;
		if (x->parent == x->parent->parent->left)
		{opCount++;
			RBTreeNode* y = x->parent->parent->right;
			if (y->isRed==true)
			{opCount++;
				x->parent->isRed=false;
				y->isRed=false;
				x->parent->parent->isRed=true;
				x=x->parent->parent;
			}
			else
			{opCount++;
				if (x==x->parent->right)
					{opCount++;
					x=x->parent;
					leftRotate(x);
					}
				x->parent->isRed=false;
				x->parent->parent->isRed=true;
				rightRotate(x->parent->parent);
			}
			
		}
		else
		{opCount++;
			if (x->parent == x->parent->parent->right)
			{opCount++;
				RBTreeNode* y = x->parent->parent->left;
				if (y->isRed==true)
				{opCount++;
					x->parent->isRed = false;
					y->isRed=false;
					x->parent->parent->isRed=true;
					x=x->parent->parent;
				}
				else{opCount++;
					if (x==x->parent->left)
						{opCount++;
                            x=x->parent;
							rightRotate(x);
						}
						x->parent->isRed=false;
						x->parent->parent->isRed=true;
						leftRotate(x->parent->parent);

				}
			}
		}
	}
	root->isRed=false;
	return;
}

/*
Prototype:
void RBTree::rbDeleteWord(std::string word)
Description:
Takes user input (string), calls a function to find the corresponding node, and calls another function to delete that node
Example:
RBTree Tree;
Tree.rbDeleteWord(cat);
Pre-conditions:
word must already exist in the tree (checked by another function)
Post-Conditions:
corresponding node is deleted, tree rebalanced by other functions

**code originally provided for previous homework assignment, modified for this project
*/

void RBTree::rbDeleteWord(std::string word)
{
    RBTreeNode *y = root;
    RBTreeNode* x=findWord(y, word);
    rbDelete(x);
    return;
}

/*
Prototype:
void RBTree::rbDelete(RBTreeNode * z)
Description:
deletes node from red-black tree, uses other helper functions to rebalance tree/ensure red-black properties maintained
Example:

Pre-conditions:
input is a node, not a word.  This is a private function, called by another, public function.
node must exist in tree
Post-Conditions:
node is removed from tree, tree properties are checked, adjusted
**code originally provided for previous homework assignment, modified for this project
*/

void RBTree::rbDelete(RBTreeNode * z) //delete node z
{opCount++;
    RBTreeNode *y = z;
    RBTreeNode*x=nil;
    bool yOriginalIsRed=y->isRed;
    if (z->left==nil)
    {opCount++;
        x=z->right;
        rbTransplant(z,z->right);

    }
    else if (z->right==nil)
    {opCount++;
        x=z->left;
        rbTransplant(z,z->left);
    }
    else
    {opCount++;
        y=z->right;
        while (y->left!=nil)
        {opCount++;
            y=y->left;
        }
        yOriginalIsRed=y->isRed;
        x=y->right;
        if (y->parent==z)
        {opCount++;
            x->parent=y;
        }
        else
        {opCount++;
            rbTransplant(y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        rbTransplant(z,y);
        opCount++;
        y->left=z->left;
        y->left->parent=y;
        y->isRed=z->isRed;
    }
    if (yOriginalIsRed==false)
    {opCount++;
        rbDeleteFixup(x);
    }
}


/*
Prototype:
void RBTree::rbDeleteFixup(RBTreeNode* x)
Description:
ensures that red-black properties are maintained after a node is deleted
Example:
rbDeleteFixup(Node& X);
Pre-conditions:
private function, called by other function, after a node is deleted
Post-Conditions:
red-black properties are maintained
**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::rbDeleteFixup(RBTreeNode* x)
{opCount++;
	RBTreeNode* w=nil;
    while ((x!= root) && (x->isRed == false))
    {opCount++;
        if (x==x->parent->left)
        {opCount++;
            w=x->parent->right;
            if (w->isRed==true)
            {opCount++;
                w->isRed=false;
                x->parent->isRed=true;
                leftRotate(x->parent);
                w=x->parent->right;
            }

            if ((w->left->isRed==false)&&(w->right->isRed==false))
            {opCount++;
                w->isRed=true;
                x=x->parent;
            }
            else if (w->right->isRed==false)
            {opCount++;
                w->left->isRed=false;
                w->isRed=true;
                rightRotate(w);
                w=x->parent->right;
            }
            w->isRed=x->parent->isRed;
            x->parent->isRed=false;
            w->right->isRed=false;
            if (x->parent->right!=nil)
           {opCount++;
            leftRotate(x->parent);}
            x=root;
            }

        else if (x == x->parent->right)
        {opCount++;
            w=x->parent->left;
            if (w->isRed==true)
            {opCount++;
                w->isRed=false;
                x->parent->isRed=true;
                rightRotate(x->parent);
                w=x->parent->left;
            }
            if (w->right->isRed==false&&w->left->isRed==false)
            {opCount++;
                w->isRed=true;
                x=x->parent;
            }
            else if (w->left->isRed==false)
            {opCount++;
                w->right->isRed=false;
                w->isRed=true;
                leftRotate(w);
                w=x->parent->left;
            }
            w->isRed=x->parent->isRed;
            x->parent->isRed=false;
            w->left->isRed=false;
            rightRotate(x->parent);
            x=root;
        }

    }
x->isRed=false;
}


/*
Prototype:
void RBTree::rbTransplant(RBTreeNode *u, RBTreeNode*v)
Description:
swaps the places of two designated nodes as a step in rebalancing tree after insertion/deletion
Example:
RBTree Tree;
rbTransplant (NodeX,NodeY)

Pre-conditions:
red-black tree properties are not maintained, tree requires adjustment
Post-Conditions:
Red-Black properties are maintained
designated nodes have been swapped, pointers updated as necessary
**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::rbTransplant(RBTreeNode *u, RBTreeNode*v)
{opCount++;
	if (u->parent == nil)
    {opCount++;
        root=v;
    }
    else if (u==u->parent->left)
    {opCount++;
        u->parent->left=v;
    }
    else if (u==u->parent->right)
    {opCount++;
        u->parent->right=v;
    }
    v->parent=u->parent;
}


/*
Prototype:
void RBTree::leftRotate(RBTreeNode* x)
Description:
performs a left-rotation around designated node
Example:
leftRotate(NodeX)
Pre-conditions:
this is a private function, called in order to maintain red-black properties of tree
Post-Conditions:
tree has been rotated around designated node.  Pointers updated,
**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::leftRotate(RBTreeNode* x)
{opCount++;
	RBTreeNode *y = x->right;
	x->right=y->left;
	if (y->left != nil)
	{opCount++;
		y->left->parent=x;
	}
	y->parent=x->parent;
	if (x->parent == nil)
	{opCount++;
		root=y;
	}
	else if (x==x->parent->left)
		{opCount++;
            x->parent->left=y;}
	else
	{opCount++;;
		x->parent->right=y;
	}
	y->left=x;
	x->parent=y;
	return;
}

/*
Prototype:

Description:
performs a right-rotation around designated node
Example:
rightRotate(NodeX);
Pre-conditions:
this is a private function, called in order to maintain red-black properties of tree
Post-Conditions:
tree has been rotated around designated node.  Pointers updated,
**code originally provided for previous homework assignment, modified for this project
*/
void RBTree::rightRotate(RBTreeNode* x)
{opCount++;
	RBTreeNode *y = x->left;
	x->left=y->right;
	if (y->right != nil)
		{opCount++;
            y->right->parent=x;}
	y->parent=x->parent;
	if (x->parent == nil)
		{opCount++;
            root=y;}
	else if (x==x->parent->right)
		{opCount++;
            x->parent->right=y;}
	else
		{opCount++;
            x->parent->left=y;}
	y->right=x;
	x->parent=y;
	return;
}


/*
Prototype:
int RBTree::rbValid(RBTreeNode * node)
Description:
Checks to ensure that red-black properties are intact.  Not actually used in final program, but left in for 
debugging purposes, if necessary
Example:
int isValid = Tree.rbValid(root);
Pre-conditions:
instance of class has been declared.  Does not need to be filled.
Post-Conditions:
returns height of tree (ignoring red nodes)
**code originally provided for previous homework assignment, modified for this project
*/
int RBTree::rbValid(RBTreeNode * node) //verify red-black tree properties maintained
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->left->isRed || node->right->isRed)
            {
                std::cout << "This tree contains a red violation" << std::endl;
                return 0;
            }
        }

        // Check for valid binary search tree.
        if ((node->left != nil && node->left->word.compare(node->word) > 0) || (node->right != nil && node->right->word.compare(node->word) < 0))
        {
            std::cout << "This tree contains a binary tree violation" << std::endl;
            return 0;
        }

        // Deteremine the height of let and right children.
        lh = rbValid(node->left);
        rh = rbValid(node->right);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            std::cout << "This tree contains a black height violation" << std::endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}



void RBTree::isValid() //public function, calls rbValid()~a private function 
{


	int x = rbValid(root);
	std::cout << x << std::endl;
}


//public, uses another private function to search for node containing specified word, 
//if word is found, returns the same word.  If not found, returns 'nil'
std::string RBTree::rbFindWord(std::string word) 
{
RBTreeNode *y = root;
RBTreeNode* x=findWord(y, word);
return x->word;
}

/*
Prototype:
RBTreeNode* RBTree::findWord(RBTreeNode* x, std::string word) 
Description:
a private function, called by a public function.  Input is a node (root) and a string (word to find)
recursively calls itself until node containing the designated word is found.  returns that node
Example:
Tree.findWord(root,"cat");
Pre-conditions:
assumes that an instance of the class has been declared (checked by main())
Post-Conditions:
tree is unchanged, a pointer to th node containing desired word is returned
*/
RBTreeNode* RBTree::findWord(RBTreeNode* x, std::string word) // private
{	opCount++;
	if (x==nil)
		{return x;}
	if (x->word == word)
		{return x;}
	
	
	
		if (x->word > word)
			{return findWord(x->left,word);}
		if (x->word < word)
			{return findWord(x->right,word);}
	
    return x; // this line will never be executed, added just to avoid warning about 'may reach end of non-void function'...

}


void RBTree::showRoot()
{
	std::cout << root->word << std::endl;
}


/*
Prototype:
void RBTree::rbEditWord(std::string oldSpelling, std::string newSpelling)
Description:
takes in two strings, one already in dictionary, to be changed to second
calls two other functions, first is to delete the node containing 'oldSpelling'
second is to create amd add node containing 'newSpelling'
Example:
RBTree Tree;
rbEditWord("colour","color")
Pre-conditions:
node containing oldSpelling must exist (checked by main())
Post-Conditions:
one node deleted, one node added, tree rebalanced after each operation
*/
void RBTree::rbEditWord(std::string oldSpelling, std::string newSpelling)
{
	RBTreeNode* nodeToEdit = findWord(root, oldSpelling);
	rbDelete(nodeToEdit);
	rbAddWord(newSpelling);


	return;
}



void RBTree::resetOpCount()
{
    opCount=0;
    return;
}

int RBTree::getOpCount()
{
    return opCount;
}


void RBTree::emptyTree()
{
    emptyTree(root);
    root=nil;
}


/*
Prototype:
void RBTree::emptyTree(RBTreeNode* x)
Description:
recursively calls itself to delete every node in the red-black tree
Example:
RBTree Tree;
Tree.emptyTree(root);
Pre-conditions:
instance of class declared.  Tree can be empty
Post-Conditions:
instance of class exists, tree exists, but root = nil, all nodes/information deleted
*/
void RBTree::emptyTree(RBTreeNode* x)
{
    if (x==nil)
        {return;}
    if(x->left!=nil)
{emptyTree(x->left);}
if (x->right != nil)
{emptyTree(x->right);}
delete x;
return;
}
