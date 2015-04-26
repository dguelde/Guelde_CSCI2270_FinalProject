// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions
// define functions for main()

#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include "RedBlackTree.h"
#include "Utilities.h"


/*
not used...incomplete...the following function will search the red-black tree for words that are different from
user input by 1 or 2 characters~~~caa will return cat, car, can, ran, rat, ...etc.
when used on short (3-letter) words, returns a lot of suggestions.  Longer words are more manageable.

*/

void getSuggestions(string word, RBTree* Tree,  HashTable* table,WordList* List, int instruction)
{
int length = word.size();
vector<char> wordArray;
for (int i = 0;i<length;i++)
{wordArray.push_back(word[i]);}
vector<string> possibleSuggestions;
	
	for (int g = 0;g<length;g++)
	{
		for (int h = 65;h<123;h++)
		{
		vector<char>tempArray2 = wordArray;
		char character2 = h;
		tempArray2[g] = character2;
	for (int i = 0;i<length;i++)
	{
	for (int j = 65;j<123;j++)
	{
	vector<char> tempArray=tempArray2;
	char character = j;
	tempArray[i]= character;
	string newWord;
	for (int k = 0;k<length;k++)
	{
		newWord=newWord+tempArray[k];
	}
	string toCheck = Tree->rbFindWord(newWord);
	if (toCheck == newWord)
		{
			bool alreadyFound=false;
			int numberPossibles = possibleSuggestions.size();
			for (int l = 0;l<numberPossibles;l++)
			{
				if (possibleSuggestions[l]==toCheck)
					{alreadyFound=true;}
			}
			if (!alreadyFound)
				{possibleSuggestions.push_back(toCheck);}
		}
	}
	}

}

}
for (int i = 0;i<possibleSuggestions.size();i++)
{
	cout << '\n' << "Did you mean " << possibleSuggestions[i];
}


return;
}

void printMenu() //prints menu...
{
	cout << "==============Main Menu=============" << endl;
	cout << "1. Build a dictionary" << endl;
	cout << "2. Search for a word" << endl;
	cout << "3. Add a word to the dictionary" << endl;
	cout << "4. Edit a word in the dictionary" << endl;
	cout << "5. Delete a word from the dictionary" << endl;
	cout << "6. Quit" << endl;

	return;

}

int chooseDictionary() //prints a menu, returns user's choice
{	int command=0;
	string input;
	while (command==0)
	{cout << "Choose dictionary:" << endl;
	cout << "1. Red-Black Tree" << endl;
	cout << "2. Hast Table" << endl;
	cout << "3. Linked List" << endl;
	cout << "4. All" << endl;
	cout << "5. Cancel" << endl;
	cin >> ws;
	getline(cin,input,'\n');
	try
	{command = stoi(input);}
	catch (...)
	{}
	}

	return command;
}

void printBuildMenu()
{
	cout << "What type of data structure would you like to use for the dictionary?" << endl;
	cout << "1. Red-Black Tree" << endl;
	cout << "2. Hash Table" << endl;
	cout << "3. Linked List" << endl;
	cout << "4. All" << endl;
	cout << "5. Cancel" << endl;
	return;
}

void bestOrWorstCaseLinkedList()
{
	cout << "Would you like to implement:" << endl;
	cout << "1.  Best-case" << endl;
	cout << "2.  Worst case (caution:slooooow)" << endl;
}

void resetOpCounts(RBTree* Tree, WordList* List, HashTable* Table) //sets the variable 'opCount' in every class to 0
{
	Tree->resetOpCount();
	List->resetOpCount();
	Table->resetOpCount();
	return;
}



/*
Function Prototype:
void readFile(RBTree* Tree, WordList* List, HashTable* Table, int instruction);

Function Description:
This function opens a predesignated text file and uses the information therein to fill the designated date
structure (makes a dictionary).  The variable 'int instruction' designates which data structure to use.

Example:
void readFile(&Tree,&List,&Table, 1)

Precondition:
Data structures can be already filled, or empty.  If already filled, will be emptied, then refilled from text file.
All classes must have an instance declared (happens at the beginning of main())

Post condition:
Designated data structure is filled with words from text file
*/
void readFile(RBTree* Tree, WordList* List, HashTable* Table, int instruction)
{
	int count=0;
	string input;
	ifstream infile;
	infile.open("/usr/share/dict/american-english");
	//infile.open("american-english.txt");    //	/usr/share/dict/american-english
	if (!infile)
		{cout << "Cannot open file" << endl;
		return;}
	else if (instruction==1)
		{
			count = 0;
			Tree->resetOpCount();
			getline(infile,input,'\n');
			while (getline(infile,input,'\n'))
			{
				count++;
				Tree->rbAddWord(input);
			}
			cout << '\n';
			cout << "Red-Black Tree constructed of " << count << " entries" << endl;
		}
	else if (instruction==2)
	{
		count = 0;
		Table->resetOpCount();
		getline(infile,input,'\n');
			while (getline(infile,input,'\n'))
			{
				count++;
				Table->htAddWord(input);
			}
			cout << '\n';
			cout << "Hash Table constructed of " << count << " entries" << endl;

	}
	else if (instruction==3)
	{
		count = 0;
		List->resetOpCount();
		getline(infile,input,'\n');
			while (getline(infile,input,'\n'))
			{
				count++;
				List->llAddWordFast(input);
			}
			cout << '\n';
			cout << "Linked List constructed of " << count << " entries" << endl;

	}
	else if (instruction==4)
	{
		count = 0;
		List->resetOpCount();
		getline(infile,input,'\n');
			while (getline(infile,input,'\n'))
			{
				count++;
				List->llAddWordSlow(input);
			}
			cout << '\n';
			cout << "Linked List constructed of " << count << " entries" << endl;

	}
	else if (instruction==5)
	{
		count = 0;
		List->resetOpCount();
		getline(infile,input,'\n');
			while (getline(infile,input,'\n'))
			{
				count++;
				Tree->rbAddWord(input);
				List->llAddWordFast(input);
				Table->htAddWord(input);
				
			}
			cout << '\n';

	}
		infile.close();


return;
}