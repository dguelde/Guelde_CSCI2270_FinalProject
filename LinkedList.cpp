// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// define functions for LinkedList class

#include "LinkedList.h"


WordList::WordList(){
	head = NULL;
}

WordList::~WordList()
{

}


/*
Prototype:
void WordList::llAddWordFast(std::string in_word)
Description:
takes a string as input, creates node, and adds node to linked list
this is called 'fast' because, on file read-in, the words will come in alphabetical order.
this function will build the list in reverse alphabetical order, meaning every new word read in will go at the beginning
of the list, resulting in very fast operation.  For contrast, see Slow
Example:
List.llAddWordFast("cat");
Pre-Conditions:
word does not exist in list yet, class instance has been declared
Post:conditions:
node containing designated word has been created/inserted into list and pointers adjusted accordingly
*/
void WordList::llAddWordFast(std::string in_word)
{//opCount++;
	
	WordListNode* x = head;
	WordListNode* y = NULL;

	WordListNode *newWord = new WordListNode(in_word);
	if (x==NULL)
		{head=newWord;
		opCount++;
		std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	if (x->word < newWord->word)
		{head=newWord;
		opCount++;
		newWord->next=x;
		std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	if (x->next==NULL)
	{
	if (x->word > newWord->word)
		{x->next=newWord;
			opCount++;
			std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	}
	
		
		while (x->word > newWord->word) //after exiting this loop, newWord will fit between x and y
		{
			y=x;
			x=x->next;
			opCount++;
			

			if (x->next==NULL)
			{
				if (x->word > newWord->word) //newWord goes at the end of the list
				{
					x->next=newWord;
					newWord->next=NULL;
					opCount++;
					std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
					return;
				}
				else //newWord is second to last in the list
				{
					y->next = newWord;
					opCount++;
					newWord->next=x;
					std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
				
					return;
				}
			}
		}

	opCount++;
	y->next = newWord;
	newWord->next = x;

	
	std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
	return;
}

/*
Prototype:
void WordList::llAddWordSlow(std::string in_word)
Description:
takes a string as input, creates node, and adds node to linked list
this is called 'slow' because, on file read-in, the words will come in alphabetical order.
this function will build the list in alphabetical order, meaning every new word read in will go at the end
of the list, resulting in very slow (worst case) operation.  For contrast, see Fast
Example:
List.llAddWordSlow("cat");
Pre-Conditions:
word does not exist in list yet, class instance has been declared
Post:conditions:
node containing designated word has been created/inserted into list and pointers adjusted accordingly
*/
void WordList::llAddWordSlow(std::string in_word)
{opCount++;
	
	WordListNode* x = head;
	WordListNode* y = NULL;

	WordListNode *newWord = new WordListNode(in_word);
	if (x==NULL)
		{head=newWord;
			//opCount++;
		newWord->next=NULL;
		std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	if (x->word > newWord->word)
		{head=newWord;
			//opCount++;
		newWord->next=x;
		std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	if (x->next==NULL)
	{
	if (x->word < newWord->word)
		{x->next=newWord;
			//opCount++;
			std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;}
	}
	
		
		while (x->word < newWord->word) //after exiting this loop, newWord will fit between x and y
		{
			y=x;
			x=x->next;
			opCount++;

			if (x->next==NULL)
			{
				if (x->word < newWord->word) //newWord goes at the end of the list
				{
					x->next=newWord;
					opCount++;
					std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
					return;
				}
				else //newWord is second to last in the list
				{
					y->next = newWord;
					newWord->next=x;
					opCount++;
					std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
					return;
				}
			}
		}
		opCount++;
	y->next = newWord;
	newWord->next = x;

	
	std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
	return;
}


/*
Prototype:
std::string WordList::llFindWord(std::string in_word)
Description:
takes a string as input, attempts to find the string in the list.
If found, the same string is returned.
If not found, returns 'nil'
Example:
List.llFindWord("cat");
Pre-conditions:
input can be letters, numbers, punctuation, etc.
list can contain data, or be empty
Post-conditions:
no change to list, returns string 'nil' if empty, same string as input if found
*/
std::string WordList::llFindWord(std::string in_word)
{
	std::string returnValue = "nil";
	WordListNode *x = head;

while (x!= NULL)
	{opCount++;
		if (x->word == in_word)
	{
		returnValue=x->word;
		return returnValue;
	}
	x=x->next;}
	return returnValue;
}


/*
Prototype:
void WordList::llDeleteWord(std::string toDelete)
Description:
deletes node containing input string, readjusts pointers as necessary
Example:
List.llDelete("colour");
Pre-conditions:
assumes that input string exists in list
Post-conditions:
node containing input string is deleted, memory freed, pointers adjusted
*/
void WordList::llDeleteWord(std::string toDelete)
{
WordListNode *x = head;
WordListNode *y = NULL;	
if (x->word == toDelete)
{head=x->next;
	delete x;
	return;}
while (x!= NULL)
	{opCount++;
		if (x->word == toDelete)
	{

		y->next=x->next;
		delete x;
		break;
	}
	y=x;
	opCount++;
	x=x->next;
	}
	return;

}


/*
Prototype:
void WordList::llEditWord(std::string oldSpelling,std::string newSpelling)
Description:
calls delete function and add function to 'change' spelling
doesn't actually edit...
Example:
List.llEditWord("colour","color");
Pre-conditions:
assumes oldSpelling exists in list, newSpelling does not
Post-conditions:
oldSpelling node is deleted, newSpelling node added, pointers adjusted
*/
void WordList::llEditWord(std::string oldSpelling,std::string newSpelling)
{
	llDeleteWord(oldSpelling);
	llAddWordSlow(newSpelling);
	return;
}

void WordList::resetOpCount()
{
    opCount=0;
    return;
}

int WordList::getOpCount()
{
	return opCount;
}

/*
Prototype:
void WordList::emptyList()
Description:
public function, calls private function to delet list, leaves instance intact
Example:
List.emptyList();
Pre-conditions:
class instance has been declared, list can contain data or be empty
Post-conditions:
list is empty, all nodes deleted, head pointer = NULL
*/
void WordList::emptyList()
{
emptyList(head);
head = NULL;
return;
}


/*
Prototype:
void WordList::emptyList(WordListNode* x)
Description:
private function to delete contents of list
Example:
emptyList(head);
Pre-conditions:
called by a public function, provided with the head node pointer
Post-conditions:
list is empty, memory freed
*/
void WordList::emptyList(WordListNode* x)
{
	if (x == NULL)
		{return;}
	WordListNode* y = x;
	x=x->next;
	delete y;
	return;

}