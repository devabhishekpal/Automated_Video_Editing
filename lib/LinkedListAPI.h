#ifndef _LIST_API_
#define _LIST_API_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Doubly Linked List
typedef struct listNode{
    void* data;
    struct listNode* prev;
    struct listNode* next;
} Node;

//Stores metadata about the list
//This means it contains information about the list head and tail as well as the 
//function pointers for working with the abstract list data
typedef struct listHead{
    Node* head;
    Node* tail;
    int length;
    void (*deleteData)(void* toBeDeleted);
    int (*conpare)(const void* first, const void* second);
    char* (*printData)(void* toBePrinted);
} List;

//This is an abstract data type to iterate through the list
typedef struct iter{
    Node* current;
} listIterator;

//Initialize list metadata head with appropriate function pointers
//printFunction ---> function pointer to print single node of the list
//deleteFunction ---> function pointer to delete a single piece of data from the list
//compareFunction ---> function pointer to compare two nodes of the list to check equality or order
List initList(char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second));

//Function for creating a node for the linkedList
//Node contains abstracted i.e (void*) data as well as prev and next pointers to connect other nodes in the list
Node* initNode(void* data);

//Inserts a node at front of a linkedList. List metadata is update so that head and tail pointers are correct
void insertFront(List* list, void* toBeAdded);

//Inserts a node at the back of a linked list
//Updates list metadata so that head and tail pointers are correct
void insertBack(List* list, void* toBeAdded);

//Clear the linkedList and free all memory
void clearList(List* list);

//Uses a conparision function pointer to place the element in an appropriate position in the list
void insertSorted(List* list, void* toBeAdded);

///Uses a conparision function pointer to place the element in an appropriate position in the list
//Also returns a the node of inserted element

Node* insertSortedGetNode(List* list, void* toBeAdded);

//Removes data from the list, deletes the node to free memory
void deleteDataFromList(List* list, void* toBeDeleted);

//Returns pointer to data at front of list
void* getFront(List list);

//Returns pointer to data at end of list
void* getBack(List list);

//Returns node containing search data
Node* getNodefromData(List* list, void* data);

//Returns a string that contains a string representation of the list traversal from head to tail
//Uses list's printData function pointer to create the string
char* toString(List list);

//Function to create an iterator for the linked list
listIterator createIterator(List list);

//Function to return next element of the list through the iterator
//First call returns data at head of the list
//Every subsequent call returns data associated with the next element
void* nextElement(listIterator* iter);

//Seek the list iterator to a specific index
int seekIterator(listIterator* iter, int index);

//Returns number of elements in list
int getLength(List list);

//Function that searches for an element in the list using a comparasion function
//Returns pointer to data of that element if found, else returns NULL
//customCompare ---> a pointer to comparator fuction for customizing the search
//searchRecord ---> a pointer to search data, which contains seach criteria
void* findElement(List list, bool (*customCompare)(const void* first, const void* second), const void* searchRecord);

#endif