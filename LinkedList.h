// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// declare LinkedList class

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

struct WordListNode{
	std::string word;
	WordListNode* next = NULL;

	WordListNode(){};

	WordListNode(std::string in_word)
	{
		word = in_word;
		next=NULL;
	}


};

class WordList{
	int opCount;

public:
	WordList();
	virtual~WordList();
	void llAddWordSlow(std::string word);
	void llAddWordFast(std::string word);
	std::string llFindWord(std::string word);
	void llDeleteWord(std::string word);
	void llEditWord(std::string,std::string);
	WordListNode getSuggestion(std::string word);
	void resetOpCount();
	void emptyList();
	int getOpCount();


private:
	WordListNode* head;
	void emptyList(WordListNode*);

};

#endif // LINKEDLIST_H