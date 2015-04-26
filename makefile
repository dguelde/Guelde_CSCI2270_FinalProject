CPPFLAGS = -Wall -std=c++11
PROG = project
OBJS = Project.o  HashTable.o  LinkedList.o  RedBlackTree.o  Utilities.o


project: Project.o  HashTable.o  LinkedList.o  RedBlackTree.o  Utilities.o
	c++ Project.o  HashTable.o  LinkedList.o  RedBlackTree.o  Utilities.o -o project

Project.o: Project.cpp
	c++ $(CPPFLAGS) -c Project.cpp

HashTable.o:  HashTable.h HashTable.cpp
	c++ $(CPPFLAGS) -c HashTable.cpp 

LinkedList.o:  LinkedList.h LinkedList.cpp
	c++ $(CPPFLAGS) -c LinkedList.cpp 

RedBlackTree.o:  RedBlackTree.h RedBlackTree.cpp
	c++ $(CPPFLAGS) -c RedBlackTree.cpp 

Utilities.o:  Utilities.h Utilities.cpp
	c++ $(CPPFLAGS) -c Utilities.cpp 


clean:
	$(RM) $(PROG) $(OBJS)
