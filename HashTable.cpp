// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// define functions for HashTable class

#include <cmath>
#include "HashTable.h"

//default constructor, creates a vector of pointers of proper size for hash table
HashTable::HashTable()
{
for (int i = 0;i<TableSize;i++)
{
	hashTable.push_back(NULL);//initialize hash table array of correct size
}
return;
}

HashTable::~HashTable()
{

}


/*
Prototype:
std::string HashTable::htFindWord(std::string in_word)
Description:
takes a string as input, gets the hash for the string, searches for string in appropriate bucket
returns 'nil' if not found, returns input word if found
Example:
HashTable Table;
Table.FindWord("cat");
Pre-conditions:
instance of class has been declared.  Table can contain data, or be empty
Post-conditions:
returns a string, hash table is unchanged
*/
std::string HashTable::htFindWord(std::string in_word)
{opCount++;
	std::string toReturn = "nil";
	int hash = getHash(in_word);
	HashTableElement* x = hashTable[hash];

	while (x!=NULL)
		{if (x->word == in_word)
			{opCount++;
				toReturn = x->word;
				break;}
			x=x->next;

		}
	return toReturn;
}


/*
Prototype:
void HashTable::htPrintInventory() 
Description:
not used in final program, can be used for debugging
prints contents of hash table, starting at index[0], alphabetically for each index[i]
Example:
Table.printInventory();
Pre-conditions:
class instance declared.  Table may be empty
Post-conditions:
table is unchanged.  contents of table printed via cout<<
*/
void HashTable::htPrintInventory() //from HashTable[0]->[9], prints each linked list
{opCount++;
	bool isEmpty=true;
	HashTableElement*x = NULL;
	for (int i = 0;i<hashTable.size();i++)
	{opCount++;

		x = hashTable[i];
		if (x!=NULL)
		{isEmpty=false; //if ANY movie found in ANY linked list, then not empty...
			std::cout << i << " " << x->word <<std::endl;
			while (x->next!=NULL)
				{x=x->next;
					opCount++;
					std::cout << i << " " << x->word << std::endl;}}
	}
	if (isEmpty)
	{std::cout << "empty" << std::endl;}


return;
}

/*
Prototype:
void HashTable::htAddWord(std::string in_word)
Description:
takes a string as input, calls another function to get hash number, inserts string alphabetically into linked list at 
corresponding bucket
Example:
Table.htAddWord("whatever");
Pre-conditions:
input string can be letters,numbers,punctuation
Post-conditions:
new node is created,added into linked list at designated hash index
counts and displays operations count
*/
void HashTable::htAddWord(std::string in_word)
{
	opCount++;
	
	HashTableElement* newWord = new HashTableElement;
	newWord->word=in_word;
	int hash = getHash(in_word);
	//std::cout << hash << std::endl;
	HashTableElement *x = hashTable[hash];
	if (x==NULL||x->word > newWord->word) //newWord goes at head of list
		{hashTable[hash] = newWord;
			newWord->next = x;
			opCount++;
			std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
			return;}
	if (x->next == NULL) //special check if list has only 1 item, prevent segfaults later
		{if (newWord->word < x->word)
			{hashTable[hash] = newWord;
				newWord->next=x;
			opCount++;}
		else
			{x->next = newWord;
			opCount++;}
			std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
		return;
	}

	HashTableElement *y = NULL;
	while (x->next != NULL)
		{if (x->word > newWord->word)
			{newWord->next = x;
				y->next = newWord;
				opCount++;
				std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
				return;}
				opCount++;
			y=x;
			x=x->next;}

	if (x->word > newWord->word)
		{newWord->next=x;
			y->next=newWord;
			opCount++;
			std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
			return;}
			opCount++;
		x->next = newWord;
	std::cout << '\r'<< "Operations Count = " << opCount << std::flush;
	return;

}


/*
Prototype:
int HashTable::getHash(std::string in_word) 
Description:
sums up the ASCII values of input string and uses modulus to produce hash number corresponding to predetermined table size
returns an integer
Example:
Table.getHash("cat");
Pre-conditions:
table size is predeclared in class definition
Post-conditions:
no changes to hash table, returns an integer between 0 and tableSize
*/
int HashTable::getHash(std::string in_word) // generate hash number
{opCount++;
	//std::cout << in_word << std::endl;
	int hash=1;
	for (int i = 0;i<in_word.size();i++)
	{
		int j = in_word[i];
		hash=hash*j;
		//std::cout << j << std::endl; // make this number large enough to fo (mod TableSize) (addition gives results too small)

	}

	if (hash<0) // because "é" gives a negative value in the for loop and I don't know why...
		{hash = hash*-1;}
	hash = hash % TableSize;
	
	

	return hash;
}

/*
Prototype:
void HashTable::htDeleteWord(std::string toDelete)
Description:
input is a string.  First gets corresponding hash number, uses hash number to find node containing string, deleted node, 
adjusts pointers in linked list as necessary
Example:
Table.htDeleteWord("somethingToDelete");
Pre-conditions:
assumes input can be found in hash table (should be checked by main() before this function is called)
Post-conditions:
node containing designated string is deleted, pointers adjusted
*/
void HashTable::htDeleteWord(std::string toDelete)
{opCount++;
	int hash = getHash(toDelete);
	HashTableElement*x=hashTable[hash];
	HashTableElement*y=NULL;
	if (x->word == toDelete)
	{hashTable[hash]=x->next;
	delete x;
	return;
	}
	while (x!=NULL)
	{
		y=x;
		x=x->next;
		if (x->word==toDelete)
		{
			y->next = x->next;
			delete x;
			return;
		}
	}
return;
	
}


/*
Prototype:
void HashTable::htEditWord(std::string oldSpelling,std::string newSpelling)
Description:
this is a public function that will edit a word already in the table.
First, the designated word is found and deleted, then the new word is added (not actually changed)
Example:
Table.htEditWord("colour","color")
Pre-conditions:
assumes first word can be found in hash table, and second word has not been added yet
Post-conditions:
node containing first word deleted, node containing second word added and inserted into table
*/
void HashTable::htEditWord(std::string oldSpelling,std::string newSpelling)
{opCount++;
	htDeleteWord(oldSpelling);
	htAddWord(newSpelling);
	return;
}

void HashTable::resetOpCount()
{
    opCount=0;
    return;
}

int HashTable::getOpCount()
{
	return opCount;
}


/*
Prototype:
void HashTable::emptyHashTable()
this function is called before creating a new hash table, to avoid conflicts/confusion
Description:
deletes all nodes in hash table, does not destroy table itself
Example:
Table.emptyHashTable();
Pre-conditions:
requires no input; table can contain data, or be empty
Post-conditions:
instance of class is intact, but all nodes are deleted
*/
void HashTable::emptyHashTable()
{
	HashTableElement* x = NULL;
	
	for (int i = 0;i<hashTable.size();i++)
	{	x = hashTable[i];
		while (x!=NULL)
		{HashTableElement*y = x;
			x=x->next;
			delete y;
		}
		hashTable[i]=NULL;
	}
	return;
}