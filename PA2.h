#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <string.h>


typedef struct duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct record
{
	char artist[50];
	char albumTitle[50];
	char songTitle[50];
	char genre[50];
	Duration songLength;
	int timesPlayed;
	int rating;

}Record;

typedef struct node 
{
	Record data;
	struct node* pNext;
	struct node* pPrev;

}Node;

typedef struct list
{
	Node* pHead; //points to the first node in the list.
}List;

void displayMenu();
Node* makeNode(const Record* pNewData);
int insertFront(List* pList, const Record* pNewData);
void printList(List* pList);
int numberReader(char* input, Duration* length);
List* artistSearch(List* inputList, char* artist);
void loadFile(List* pList);
Record* recordEditor(Record input);
void saveFile(List* pList);
void playSong(Node** pList, char* songTitle);
int recordDeleter(List* list, char* songTitle);
int sortList(List* inputList, int choice);