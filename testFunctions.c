#include "TestFunction.h"

void testInsert(void)
{
	List testList = { NULL };
	Record testRecord = { NULL };
	strcpy(testRecord.artist, "Perry, Katy");
	strcpy(testRecord.albumTitle, "Witness");
	strcpy(testRecord.songTitle, "Chained to the Rhythm");
	strcpy(testRecord.genre, "Pop");
	testRecord.songLength.minutes = 4;
	testRecord.songLength.seconds = 36;
	testRecord.timesPlayed = -1;
	testRecord.rating = 6;
	insertFront(&testList, &testRecord);
	if(testList.pHead != NULL && testList.pHead->data.rating < 6 &&	testList.pHead->data.timesPlayed > -1) 
	{ 
		printf("Insert test successful:\n1. Head node != NULL\n2. Rating = %d\n3. Times Played = %d\n\n", testList.pHead->data.rating, testList.pHead->data.timesPlayed);
	}
	else 
	{
		if (testList.pHead == NULL) printf("Insert test failed:\n1. Head node == NULL\n2. Rating = N/A\n3. Times Played = N/A\n\n");
		else printf("Insert test failed:\n1. Head node != NULL\n2. Rating = %d\n3. Times Played = %d\n\n", testList.pHead->data.rating, testList.pHead->data.timesPlayed);
	}
}

void testDelete(void)
{
	List testList = { NULL };
	Record testRecord = { NULL };
	strcpy(testRecord.artist, "Perry, Katy");
	strcpy(testRecord.albumTitle, "Witness");
	strcpy(testRecord.songTitle, "Chained to the Rhythm");
	strcpy(testRecord.genre, "Pop");
	testRecord.songLength.minutes = 4;
	testRecord.songLength.seconds = 36;
	testRecord.timesPlayed = -1;
	testRecord.rating = 6;
	
	insertFront(&testList, &testRecord);

	recordDeleter(&testList, "Chained to the Rhythm");
	if (testList.pHead == NULL) printf("Delete test successful:\n1. Record removed\n2. pHead == NULL\n\n");
	else if (strcmp(testList.pHead->data.songTitle, "Chained to the Rhythm") == 0) printf("Delete test failed:\n1. Record not removed\n2. pHead != NULL\n\n");
	else printf("Delete test failed:\n1. Record status unknown\n2. pHead != NULL\n\n");
}

void testShuffle(void)
{
	List testList = { NULL };
	Record testRecord = { NULL };
	strcpy(testRecord.artist, "Perry, Katy");
	strcpy(testRecord.albumTitle, "Witness");
	strcpy(testRecord.songTitle, "Chained to the Rhythm");
	strcpy(testRecord.genre, "Pop");
	testRecord.songLength.minutes = 4;
	testRecord.songLength.seconds = 36;
	testRecord.timesPlayed = 3;
	testRecord.rating = 6;
	insertFront(&testList, &testRecord);
	testRecord.timesPlayed = 2;
	insertFront(&testList, &testRecord);
	testRecord.timesPlayed = 1;
	insertFront(&testList, &testRecord);
	shuffle(testList, "3,1,2", 3);
	printf("\nIf times played of the three were in order 3-1-2, Shuffle was successful\n\n");
}