// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// declare functions for main()

#ifndef UTILITIES_H
#define UTILITIES_H

#include "RedBlackTree.h"
#include "HashTable.h"
#include "LinkedList.h"

using namespace std;



void readFile(RBTree* Tree, WordList* List, HashTable* Table, int instruction); 
void getSuggestions(std::string, RBTree*, HashTable*,WordList*, int);
void printMenu();
void printBuildMenu();
void printBuildMenu();
void bestOrWorstCaseLinkedList();
void resetOpCounts(RBTree* Tree, WordList* List, HashTable* Table);
int chooseDictionary();





#endif // UTILITIES_H