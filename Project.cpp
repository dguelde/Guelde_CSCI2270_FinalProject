// Author: Donovan Guelde
// csci 2270 spring 2015
// Prof. Hoenigman
// Final Project: Spell checker with suggestions

//#include <iostream>
#include <fstream>

#include "HashTable.h"
#include "LinkedList.h"
#include "RedBlackTree.h"
#include "Utilities.h"

//using namespace std;

//void readFile(RBTree* Tree, WordList* List, HashTable* Table);



int main(){

	RBTree RedBlackTree;
	WordList LinkedList;
	HashTable Table;

	//readFile(&RedBlackTree, &LinkedList, &Table, instruction);

string input;
string input2;
int command=-1;
int command2 = -1;
int command3 = -1;
bool rbTreebuilt = false;
bool listBuilt = false;
bool hashBuilt = false;
while (command !=6)
{
	command=-1;
	printMenu();
	cin >> ws;
	getline(cin,input,'\n');
	try
	{command = stoi(input);}
	catch (...)
	{}

switch (command)
{
case 1: //build dictionary
{
	command2=-1;
	while (command2 != 5) //switch case for build dictionary submenu
	{

	printBuildMenu();
	cin>>ws;
	getline(cin,input,'\n');
	try
	{command2 = stoi(input);}
	catch (...)
	{} //ignore garbage input
	switch (command2)
	{
	case 1: // build red-black tree
	{	RedBlackTree.emptyTree(); //clears any previously built dictionary before (re)construction
		//RBTree RedBlackTree;

		readFile(&RedBlackTree, &LinkedList, &Table, 1);
		command2=5;
		rbTreebuilt = true;
		break;
	}
	case 2: //build hash table
	{	Table.emptyHashTable(); //clears any previously built hash table before (re)construction
		//HashTable Table;
		readFile(&RedBlackTree, &LinkedList, &Table, 2);
		command2=5;
		hashBuilt = true;
		break;
	}
	case 3: //build linked list
	{
		bestOrWorstCaseLinkedList();
		cin>>ws;
		getline(cin,input,'\n');
		try
		{command3 = stoi(input);}
		catch (...)
		{} //ignore garbage input
		switch (command3)
		{case 1:
			{	LinkedList.emptyList();
				//WordList LinkedList;
				LinkedList.resetOpCount();
				readFile(&RedBlackTree, &LinkedList, &Table, 3);
				command2=5;
				listBuilt = true;
				break;}
		case 2:
			{	LinkedList.emptyList();
				//WordList LinkedList;
				LinkedList.resetOpCount();
				readFile(&RedBlackTree, &LinkedList, &Table, 4);
				command2=5;
				listBuilt = true;
				break;}



			default:
			{break;}
		}

		break;
	}
	case 4: //build all
	{	RedBlackTree.emptyTree(); //empty dictionaries to prevent problems/conflicts/reset to default
		Table.emptyHashTable();
		LinkedList.emptyList();


		resetOpCounts(&RedBlackTree, &LinkedList, &Table);
		readFile(&RedBlackTree, &LinkedList, &Table, 1);
		readFile(&RedBlackTree, &LinkedList, &Table, 2);
		readFile(&RedBlackTree, &LinkedList, &Table, 3);


		command2=5;
		rbTreebuilt = true;
		listBuilt = true;
		hashBuilt = true;
		break;
	}
	default:
	{
			//do nothing if command is outside of menu options
		break;
	}
	}}// end submenu switch case


break;
}
case 2: //search for a word
{
	resetOpCounts(&RedBlackTree, &LinkedList, &Table);
	int command2 = chooseDictionary();
	if (command2 == 5)
		{break;}
	cout << "Enter word:" << endl;
	cin>>ws;
	getline(cin,input,'\n');

	if (command2 == 1 || command2 == 4)
		{
		    if(rbTreebuilt){
		    if (RedBlackTree.rbFindWord(input) == input)
			{
				cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
				cout << input << " found in Red-Black Tree" << endl;
			}
			RedBlackTree.resetOpCount();

			if (RedBlackTree.rbFindWord(input) == "nil")
				{cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
					cout << input << " not found in Red-Black Tree" << endl;
					/*getSuggestions(input, &RedBlackTree, &Table, &LinkedList, command2);*/}
		    }
		    else{
                cout << "Red-Black Tree empty, please built or add to it first" << endl;
		    }
        }
	if (command2 == 2 || command2 == 4)
		{
		    if(hashBuilt){
		    if (Table.htFindWord(input) == input)
			{cout << "Operations Count: " << Table.getOpCount() << endl;
				cout << input << " found in Hash Table" << endl;
			}
			Table.resetOpCount();

			if (Table.htFindWord(input) == "nil")
				{cout << "Operations Count: " << Table.getOpCount() << endl;
					cout << input << " not found in Hash Table" << endl;}
            else{
                cout << "Hash Table empty, please built or add to it first" << endl;
		    }
            }
		}
	if (command2 == 3 || command2 == 4)
		{
		    if(listBuilt){
		    LinkedList.resetOpCount();
			if (LinkedList.llFindWord(input) == input)
			{cout << "Operations Count: " << LinkedList.getOpCount() << endl;
				cout << input << " found in Linked List" << endl;
			}
			LinkedList.resetOpCount();

			if (LinkedList.llFindWord(input) == "nil")
				{cout << "Operations Count: " << LinkedList.getOpCount() << endl;
					cout << input << " not found in Linked List" << endl;}
            else{
                cout << "Linked List empty, please built or add to it first" << endl;
		    }
        }
		}


	break;
}
case 3: // add word to selected dictionary
{
    resetOpCounts(&RedBlackTree, &LinkedList, &Table);
	int command2 = chooseDictionary();
	if (command2 == 5)
		{break;}

	cout << "Enter word:" << endl;
	cin>>ws;
	getline(cin,input,'\n');

	if (command2 == 1 || command2 == 4)
	{
		RedBlackTree.rbAddWord(input);
		cout << '\n';
		cout << input << " added to Red-Black Tree" << endl;
		rbTreebuilt = true;
	}
	if (command2 == 2 || command2 == 4)
	{
		Table.htAddWord(input);
		cout << '\n';
		cout << input << " added to Hash Table" << endl;
		hashBuilt = true;
	}
	if (command2 == 3 || command2 == 4)
	{
		LinkedList.llAddWordFast(input);
		cout << '\n';
		cout << input << " added to Linked List" << endl;
		listBuilt = true;
	}
	break;
}
case 4: //edit a word
{
	int command2 = chooseDictionary();
	if (command2 == 5)
		{break;}
	string oldSpelling,newSpelling;
	cout << "Enter old spelling:" << endl;
	cin>>ws;
	getline(cin,oldSpelling,'\n');
	cout << "Enter new spelling:" << endl;
	cin>>ws;
	getline(cin,newSpelling,'\n');





	resetOpCounts(&RedBlackTree, &LinkedList, &Table);
	if (command2 == 1 || command2 == 4)
	{
	    if(rbTreebuilt){
		if (RedBlackTree.rbFindWord(oldSpelling)!=oldSpelling)
			{cout << oldSpelling << " not found in Red-Black Tree" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		if (RedBlackTree.rbFindWord(newSpelling)==newSpelling)
			{cout << newSpelling << " already exists in Red-Black Tree" << endl;
			cout << "Operation cancelled" << endl;
			break;}
		//cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
		RedBlackTree.rbEditWord(oldSpelling,newSpelling);
		cout << '\n';
		cout << oldSpelling << " changed to " << newSpelling<< " in Red-Black Tree" << endl;
	    }
	    else{
                cout << "Red-Black Tree empty, please built or add to it first" << endl;
        }
	}
	if (command2 == 2 || command2 == 4)
	{
        if(hashBuilt){
		if (Table.htFindWord(oldSpelling)!=oldSpelling)
			{cout << oldSpelling << " not found in Hash Table" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		if (Table.htFindWord(newSpelling)==newSpelling)
			{cout << newSpelling << " already exists in Hash Table" << endl;
			cout << "Operation cancelled" << endl;
			break;}
		//cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
		Table.htEditWord(oldSpelling,newSpelling);
		cout << '\n';
		cout << oldSpelling << " changed to " << newSpelling << " in Hash Table" << endl;
        }
        else{
                cout << "Red-Black Tree empty, please built or add to it first" << endl;
        }
	}
	if (command2 == 3 || command2 == 4)
	{
	    if(listBuilt){
		if (LinkedList.llFindWord(oldSpelling)!=oldSpelling)
			{cout << oldSpelling << " not found in Linked List" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		if (LinkedList.llFindWord(newSpelling)==newSpelling)
			{cout << newSpelling << " already exists in Linked List" << endl;
			cout << "Operation cancelled" << endl;
			break;}
		//cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
		LinkedList.llEditWord(oldSpelling,newSpelling);
		cout << '\n';

		cout << oldSpelling << " changed to " << newSpelling << " in Linked List" << endl;
	    }
	    else{
                cout << "Linked List empty, please built or add to it first" << endl;
        }
	}




	break;
}
case 5: //delete a word
{
	int command2 = chooseDictionary();
	if (command2 == 5)
		{break;}
	string toDelete;
	cout << "Enter word to delete" << endl;
	cin>>ws;
	getline(cin,toDelete,'\n');

	resetOpCounts(&RedBlackTree, &LinkedList, &Table);
	if (command2 == 1 || command2 == 4)
	{
        if(rbTreebuilt){
		if (RedBlackTree.rbFindWord(toDelete)!=toDelete)
			{cout << toDelete << " not found in Red-Black Tree" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		RedBlackTree.rbDeleteWord(toDelete);
		cout << "Operations Count: " << RedBlackTree.getOpCount() << endl;
		cout << toDelete << " deleted from Red-Black Tree" << endl;
        }
        else{
                cout << "Red-Black Tree empty, please built or add to it first" << endl;
        }
	}
	if (command2 == 2 || command2 == 4)
	{
	    if(hashBuilt){
		if (Table.htFindWord(toDelete)!=toDelete)
			{cout << toDelete << " not found in Hash Table" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		Table.htDeleteWord(toDelete);
		cout << "Operations Count: " << Table.getOpCount() << endl;
		cout << toDelete << " deleted from Hash Table" << endl;
	    }
	    else{
                cout << "Hash Table empty, please built or add to it first" << endl;
        }
	}
	if (command2 == 3 || command2 == 4)
	{
	    if(listBuilt){
		if (LinkedList.llFindWord(toDelete)!=toDelete)
			{cout << toDelete << " not found in Linked List" << endl;
		cout << "Operation cancelled" << endl;
		break;}
		LinkedList.llDeleteWord(toDelete);
		cout << "Operations Count: " << LinkedList.getOpCount() << endl;
		cout << toDelete << " deleted from Linked List" << endl;
	    }
	    else{
                cout << "Linked List empty, please built or add to it first" << endl;
        }
	}
}

default:
{break;}


} // end switch case
} // end menu command loop
cout << "Goodbye!" << endl;






return 0;
}

