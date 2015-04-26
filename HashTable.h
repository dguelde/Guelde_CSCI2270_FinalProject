// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// declare HashTable class

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

struct HashTableElement{
	std::string word;
	HashTableElement *next=NULL;

	HashTableElement(){};

	HashTableElement(std::string in_word)
	{
		word = in_word;
	}

};

class HashTable
{
	int opCount;
public:
	HashTable();
	~HashTable();
	int TableSize=19867; //
	void htAddWord(std::string word);
	std::string htFindWord(std::string);
	void htDeleteWord(std::string);
	int getHash(std::string);
	void htPrintInventory();
	void htEditWord(std::string,std::string);
	void resetOpCount();
	void emptyHashTable();
	int getOpCount();


private:
	std::vector <HashTableElement *> hashTable;
};




#endif // HASHTABLE_H