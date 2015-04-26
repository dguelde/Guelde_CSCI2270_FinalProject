# Guelde_CSCI2270_FinalProject
CSCI2270 Final Project


Project Summary:
  This project will implement a spell-checking function along with an operations counter to compare various methods of data storage and retreival.  A dictionary (see here: http://stackoverflow.com/questions/4456446/dictionary-text-file) will be read in and stored in three different data structures: a linked list, a red-black tree, and a hash table.  The user will have the option to manually add, edit, or delete words from the dictionary in memory (not the accompanying text file.)  Basic functionality will consist of the user entering a word to be checked, and the program searching the various data structures for the word, while keeping an operations count.  If the word is found, the user is notified of correct spelling and how many operations were performed to find the word in each of the competing data structures.  If the word is not found, the user will be notified, and provided with the operations count.  
  
  How to Run:
    This program will be menu driven, with a main menu providing options for adding, editing, and deleting words, as well as searching.  
    
  Dependencies:
    This program will not require any libraries not already a part of C++11.
  
  System requirements:
    This program will be written for Ubuntu running under Oracle VirtualBox, as provided by the University of Colorado Boulder Computer Science department for 2015 spring semester (cu-cs-vm-spring15-xfce-x64.)  The dictionary used by this program is included in this installation, therefore, the program will not work under OS X or Windows.
  
  Group Members:
    None
    
  Contributors:
  
  Open Issues/Bugs:
  
  Possible additions: implement the 'suggestions' feature~this is partially completed, it is functional for the red-black tree, it just needs to be altered for the other two data structures.
  
  Refinement of operations counter.  Not sure how accurate it is, maybe some skips or double counting somewhere, not sure.
  
  Interface is really boring...
  
  
  
  
