/*****************************************************************************************
* Programmer: Josh Maloy                                                                 *
* Class: CptS 122, Fall 2021; Lab Section 1                                              *
* Programming Assignment: PA1                                                            *
* Date: September 1, 2021                                                                *
* Description: this program has multiple functions used by the main program that are     *
* necessary to carry out the main programs description.                                  *
******************************************************************************************/



#include "PA2.h"

void displayMenu()
{
	printf("====================[Main Menu]====================\n");
	printf("(1)  load\n");
	printf("(2)  store\n");
	printf("(3)  display\n");
	printf("(4)  insert\n");
	printf("(5)  delete\n");
	printf("(6)  edit\n");
	printf("(7)  sort\n");
	printf("(8)  rate\n");
	printf("(9)  play\n");
	printf("(10) shuffle\n");
	printf("(11) exit\n\n");
}

Node* makeNode(const Record* pNewData)
{
	Node* pMem = (Node*)malloc(sizeof(Node));  //we tried to allocate space
	if (pMem != NULL)
	{
		//malloc succeeded in allocating a node
		//setting all of the values of the node to the data from the record
		strcpy(pMem->data.artist, pNewData->artist);
		strcpy(pMem->data.albumTitle, pNewData->albumTitle);
		strcpy(pMem->data.songTitle, pNewData->songTitle);
		strcpy(pMem->data.genre, pNewData->genre);
		pMem->data.songLength.minutes = pNewData->songLength.minutes;
		pMem->data.songLength.seconds = pNewData->songLength.seconds;
		pMem->data.timesPlayed = pNewData->timesPlayed;
		pMem->data.rating = pNewData->rating;

		//setting up the pointers
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}

int insertFront(List* pList, const Record* pNewData)
{
	Node* pMem = makeNode(pNewData); //copying address into makeNode, returns address of the Node
	int success = 0;
	if (pMem != NULL)
	{
		success = 1; //malloc successful
		pMem->pNext = pList->pHead;  //the input node now points to the head
		pList->pHead = pMem;		 //the head is now the input node.
		if (pList->pHead->pNext != NULL) { pList->pHead->pNext->pPrev = pMem; } //if the next node != null, next.prev = head
	}
	return success;
}

void printList(List* pList)
{
	if (pList->pHead != NULL)
	{
		Node* pPrinter = pList->pHead;
		char record[100] = "";
		printf("\nTitle            | Artist            | mm:ss | Album Title          | Genre   | Times Played | Rating\n");
		while (pPrinter != NULL)
		{
			printf("%16s | %17s | %2d:%2d | %20s | %7s | %3d          | %d\n",
				pPrinter->data.songTitle,
				pPrinter->data.artist,
				pPrinter->data.songLength.minutes,
				pPrinter->data.songLength.seconds,
				pPrinter->data.albumTitle,
				pPrinter->data.genre,
				pPrinter->data.timesPlayed,
				pPrinter->data.rating);
			pPrinter = pPrinter->pNext;
		}
		printf("\n\n"); //formatting
	}
	else
	{
		printf("The list is empty\n\n");
	}
}

List* artistSearch(List* inputList, char* artist)
{
	List outputList = { NULL }; //initializing output list
	if (inputList->pHead != NULL) //checking if the input list is empty
	{
		Node* pSearch = inputList->pHead; //initializing pSearch node
		while (pSearch != NULL)
		{
			if (strcmp(pSearch->data.artist, artist) == 0) { insertFront(&outputList, pSearch); } //checking artist & inserting node into output list
			pSearch = pSearch->pNext; //going to the next node in the list
		}
	}
	if (outputList.pHead == NULL) { printf("There are no records from the artist %s\n\n", artist); }
	return &outputList;
}

void loadFile(List* pList)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	Record tempRecord = { NULL };
	char lineReader[100] = "";
	if (infile != NULL)
	{
		while (fgets(lineReader, 100, infile) != NULL)
		{
			if (lineReader[0] == '"')
			{
				//strtok(lineReader, "\"");
				strcpy(tempRecord.artist, strtok(lineReader, "\""));
				//strtok(NULL, ",");
			}
			else
			{
				strcpy(tempRecord.artist, strtok(lineReader, ","));
			}
			strcpy(tempRecord.albumTitle, strtok(NULL, ","));
			strcpy(tempRecord.songTitle, strtok(NULL, ","));
			strcpy(tempRecord.genre, strtok(NULL, ","));
			tempRecord.songLength.minutes = atoi(strtok(NULL, ":"));
			tempRecord.songLength.seconds = atoi(strtok(NULL, ","));
			tempRecord.timesPlayed = atoi(strtok(NULL, ","));
			tempRecord.rating = atoi(strtok(NULL, "\n"));
			insertFront(pList, &tempRecord);			//inserting the tempRecord into the list		
		}
		fclose(infile);
	}
}

void saveFile(List* pList)
{
	FILE* outfile = fopen("musicPlayList.csv", "w");
	Node* pReader = pList->pHead;
	if (outfile != NULL)
	{
		while (pReader != NULL)
		{
			if (strchr(pReader->data.artist, ',') != NULL) //if the artist name has a comma in it, it needs to have quotes around it
			{
				fprintf(outfile, "\"%s\",%s,%s,%s,%d:%d,%d,%d\n",
					pReader->data.artist,
					pReader->data.albumTitle,
					pReader->data.songTitle,
					pReader->data.genre,
					pReader->data.songLength.minutes,
					pReader->data.songLength.seconds,
					pReader->data.timesPlayed,
					pReader->data.rating);
			}
			else {
				fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n",  //if the artist name does not have a comma in it then it doesnt need to have quotes around it
					pReader->data.artist,
					pReader->data.albumTitle,
					pReader->data.songTitle,
					pReader->data.genre,
					pReader->data.songLength.minutes,
					pReader->data.songLength.seconds,
					pReader->data.timesPlayed,
					pReader->data.rating);
			}
			pReader = pReader->pNext;
		}
	}
}

char* underscoreRemover(char* input)
{
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == '_')
		{
			input[i] = ' ';
		}
	}
	return input;
}

Record* recordEditor(Record input)
{
	int c; //for clearing stdin
	int check = 1;
	int done = 0;
	int selection = 0;
	char selectionStr[20] = "";
	int selection2 = 0;
	do
	{
		printf("What do you want to edit?\n");
		printf("(1) Title:        %s\n", input.songTitle);
		printf("(2) Artist:       %s\n", input.artist);
		printf("(3) Album:        %s\n", input.albumTitle);
		printf("(4) Genre:        %s\n", input.genre);
		printf("(5) Length (M):   %d\n", input.songLength.minutes);
		printf("(6) Length (S):   %d\n", input.songLength.seconds);
		printf("(7) Times Played: %d\n", input.timesPlayed);
		printf("(8) Rating:       %d\n\n", input.rating);

		selection = 0;
		selection2 = 0;
		done = 0;
		strcpy(selectionStr, "Basic Value");
		scanf("%d", &selection);
		if (selection == 1)  //edit title
		{
			printf("Please type the edited Title - type \"_\" for every space, please\n");
			scanf("%s", selectionStr);
			strcpy(selectionStr, underscoreRemover(selectionStr));
			strcpy(input.songTitle, selectionStr);
			done = 2;
		}
		else if (selection == 2) //edit artist
		{
			printf("Please type the edited Artist - type \"_\" for every space, please\n");
			scanf("%s", selectionStr);
			strcpy(selectionStr, underscoreRemover(selectionStr));
			strcpy(input.artist, selectionStr);
			done = 2;
		}
		else if (selection == 3) //edit album title
		{
			printf("Please type the edited Album title - type \"_\" for every space, pleasen\n");
			scanf("%s", selectionStr);
			strcpy(selectionStr, underscoreRemover(selectionStr));
			strcpy(input.albumTitle, selectionStr);
			done = 2;
		}
		else if (selection == 4) //edit genre
		{
			printf("Please type the edited Genre - type \"_\" for every space, please\n");
			scanf("%s", selectionStr);
			strcpy(selectionStr, underscoreRemover(selectionStr));
			strcpy(input.genre, selectionStr);
			done = 2;
		}
		else if (selection == 5) //edit minute
		{
			printf("Please type the edited Minute\n");
			check = scanf("%d", &selection2);
			if (check != 1) {
				printf("Integer expected, please try again\n\n");
				while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			}
			else
			{
				input.songLength.minutes = selection2;
				done = 2;
			}
		}
		else if (selection == 6) //edit second
		{
			printf("Please type the edited Seconds\n");
			check = scanf("%d", &selection2);
			if (check != 1) {
				printf("Integer expected, please try again\n\n");
				while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			}
			else
			{
				input.songLength.seconds = selection2;
				done = 2;
			}
		}
		else if (selection == 7) //edit times played
		{
			printf("Please type the edited Times Played\n");
			check = scanf("%d", &selection2);
			if (check != 1) {
				printf("Integer expected, please try again\n\n");
				while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			}
			else
			{
				input.timesPlayed = selection2;
				done = 2;
			}
		}
		else if (selection == 8) //edit rating
		{
			printf("Please type the edited Rating\n");
			check = scanf("%d", &selection2);
			if (check != 1) {
				printf("Integer expected, please try again\n\n");
				while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			}
			else
			{
				input.rating = selection2;
				done = 2;
			}
		}
		else
		{
			scanf("%s", selectionStr);
		}
		if (done == 2)
		{
			printf("Are you done editing?\n(1) Yes\n(2) No\n");
			scanf("%d", &selection);
			if (selection == 1) { done = 1; }
			else
			{
				selection = 0;
				done = 0;
			}
		}
	} while (done != 1);
	return &input;
}

void playSong(Node** pList, char* songTitle)
{
	Node* pPlayer = *pList;
	Node* pChecker = *pList;
	if (songTitle[0] != '\0')
	{
		while (strcmp(pPlayer->data.songTitle, songTitle) != 0)
		{
			pPlayer = pPlayer->pNext;
		}
		pChecker = pPlayer;
	}
	while (pPlayer != NULL)
	{
		printf("Now Playing: %s by %s | %d:%d | Album: %s Genre %s [%d/5] Times Played: %d (+1)\n\n",
			pPlayer->data.songTitle,
			pPlayer->data.artist,
			pPlayer->data.songLength.minutes,
			pPlayer->data.songLength.seconds,
			pPlayer->data.albumTitle,
			pPlayer->data.genre,
			pPlayer->data.rating,
			pPlayer->data.timesPlayed
		);
		pPlayer->data.timesPlayed++;
		pPlayer = pPlayer->pNext;
		Sleep(1000);
	}
	pPlayer = *pList;
	while (strcmp(pPlayer->data.songTitle,pChecker->data.songTitle) != 0)
	{
		printf("Now Playing: %s by %s | %d:%d | Album: %s Genre %s [%d/5] Times Played: %d(+1) \n\n",
			pPlayer->data.songTitle,
			pPlayer->data.artist,
			pPlayer->data.songLength.minutes,
			pPlayer->data.songLength.seconds,
			pPlayer->data.albumTitle,
			pPlayer->data.genre,
			pPlayer->data.rating,
			pPlayer->data.timesPlayed
		);
		pPlayer->data.timesPlayed++;
		pPlayer = pPlayer->pNext;
		Sleep(1000);
	}
}