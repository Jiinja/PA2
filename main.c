/*****************************************************************************************
* Programmer: Josh Maloy                                                                 *
* Class: CptS 122, Fall 2021; Lab Section 1                                              *
* Programming Assignment: PA1                                                            *
* Date: September 1, 2021                                                                *
* Description: This program displays a user interface in a commandline window with       *
* multiple controls simulating a music player. It can load from a file, save to a file,  *
* edit songs, rate songs, print out the list of songs, "play" songs, and exit.           *
******************************************************************************************/


#include "TestFunction.h"

int main()
{
	int c; //for clearing stdin
	int exit = 0;
	int userInput = 0;
	char userInputStr[50] = "";
	List list = { NULL };
	do {
		userInput = 0;
		displayMenu();
		scanf(" %d", &userInput);
		while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
		if (userInput == 1) //load
		{
			printf("Loading from file .");
			Sleep(500);
			printf(" .");
			Sleep(500);
			printf(" .\n");
			loadFile(&list);
			printf("Load complete\n\n"); //call read function
			userInput = 0;
		}

		else if (userInput == 2) //store
		{
			printf("Writing to file .");
			Sleep(500);
			printf(" .");
			Sleep(500);
			printf(" .\n");
			saveFile(&list);
			printf("Write complete\n\n"); //call write function
			userInput = 0;
		}

		else if (userInput == 3) //display
		{
			printf("\nWould you like to:\n(1) Display all records\n(2) Display all records from a specific artist?\n\n");
			scanf("%d", &userInput);
			if (userInput == 1) //dispay all songs
			{
				printList(&list);
			}
			else if (userInput == 2)
			{
				printf("Please type the Artist name in the format: [Last, First]\n");
				scanf(" %[^\n]s", userInputStr);
				printf("%s", userInputStr);
				List tempList = *artistSearch(&list, userInputStr); //calling the artist search function - returns a list of songs made by the given artiste
				printList(&tempList);
				printf("\n\n");
			}
			else
			{
				printf("Invalid selection\n\n");
			}
			userInput = 0;
		}

		else if (userInput == 4) //insert
		{
			Record tempRecord;
			int scanChecker = 1;
			int rating = 0;
			char tempMin[5];
			while (scanChecker > 0) {
				printf("Please type the Artist name in the format: [Last, First]\n");
				scanChecker = scanf(" %[^\n]s", userInputStr);
				strcpy(tempRecord.artist, userInputStr); //getting artist

				printf("\nPlease type the Album Title:\n");
				scanChecker = scanf(" %[^\n]s", userInputStr);
				strcpy(tempRecord.albumTitle, userInputStr); //getting album title

				printf("\nPlease type the Song Title:\n");
				scanChecker = scanf(" %[^\n]s", userInputStr);
				strcpy(tempRecord.songTitle, userInputStr); //getting song title

				printf("\nPlease type the Song Genre:\n");
				scanChecker = scanf(" %[^\n]s", userInputStr);
				strcpy(tempRecord.genre, userInputStr); //getting song genre

				printf("\nPlease type the length of the song in the format: [m:ss]\n");
				scanChecker = scanf(" %[^\n]s", userInputStr);
				numberReader(userInputStr, &(tempRecord.songLength));

				tempRecord.timesPlayed = 0;

				printf("\nPlease type the rating of of the song from 1-5:\n");
				scanChecker = scanf("%d", &rating);
				if (rating > 0 && rating < 6) tempRecord.rating = rating;
				else tempRecord.rating = 0;
				insertFront(&list, &tempRecord);
				printf("\nRecord inserted successfully!\n\n");
				scanChecker = -1;
			}
			if (scanChecker = 0) printf("\n[INPUT ERROR, PLEASE TRY AGAIN]\n\n");
		}

		else if (userInput == 5) //delete
		{
			printf("Please type the exact name of the song you want to delete.\n");
			scanf(" %[^\n]s", userInputStr);
			if (recordDeleter(&list, userInputStr) == 1) printf("Record deleted successfully\n\n");
			else printf("Error: Record not found.\n\n");
		}

		else if (userInput == 6) //edit
		{
			printf("Please type the Artist name in the format: [Last, First]\n");
			scanf(" %[^\n]s", userInputStr);
			char songTitle[50] = "";
			Node* titlePlacer = list.pHead;
			List tempList = *artistSearch(&list, userInputStr);
			Node* titleReader = tempList.pHead;
			if (titleReader != NULL) //checking if there are any songs written by the artist given
			{
				if (titleReader->pNext != NULL) //checking if there is more than 1 song written by the artist given
				{
					printf("\n"); //formatting
					printf("Songs by %s:\n", titleReader->data.artist);
					while (titleReader != NULL) //iterating through the list of songs written by the given artist and printing the titles
					{
						printf("%s\n", titleReader->data.songTitle);
						titleReader = titleReader->pNext;
					}
					printf("\nWhich song would you like to edit? Please type the exact song name.\n\n");
					scanf(" %[^\n]s", songTitle);
					strcpy(songTitle, songTitle); //taking the song title and removing underscores
				}
				else { strcpy(songTitle, titleReader->data.songTitle); } //if the artist only has one song
				titleReader = tempList.pHead;
				{
					titleReader = titleReader->pNext; 
				}
				if (titleReader == NULL) { printf("There is no song with that title.\n\n"); }
				else
				{
					Record tempRecord = *recordEditor(titleReader->data); //calling the recordEditor function and setting equal to a tempRecord where the edits are
					{
						titlePlacer = titlePlacer->pNext;
					}
					titlePlacer->data = tempRecord; //adding the edits to the original list
				}
			}
			}

		else if (userInput == 7) //sort
		{
			int sortChoice = 0;
			printf("How would you like to sort?\n(1) Sort based on artist [a-z]\n");
			printf("(2) Sort based on album title[a - z]\n(3) Sort based on rating[5 - 1] \n(4) Sort based on times played\n");
			if (scanf("%d", &sortChoice) == 0) continue; //if userinput is not int then go back to main menu
			if (sortChoice < 1 || sortChoice > 4) printf("Invalid input, please try again\n\n"); //if choice is out of bounds, back to main menu
			else {
				if (sortList(&list, (sortChoice - 1)) == 1) printf("Sort Successful\n\n");
				else printf("Sort failed, make sure the list is not empty\n\n");
			}
		}

		else if (userInput == 8) //rate
		{
			int rating = 0;
			printf("Please type the Artist name in the format: [Last, First]\n");
			scanf(" %[^\n]s", userInputStr);
			char songTitle[50] = "";
			List tempList = *artistSearch(&list, userInputStr);
			Node* titleReader = tempList.pHead;
			if (titleReader != NULL) //checking if the artist has any songs in the list
			{
				if (titleReader->pNext != NULL) //checking if the artist has more than just one song
				{
					printf("\n"); //formatting
					printf("Songs by %s:\n", titleReader->data.artist);
					while(titleReader != NULL) //iterating through the list of songs by the given artist and printing them out
					{
						printf("%s\n", titleReader->data.songTitle);
						titleReader = titleReader->pNext;
					}
					printf("\nWhich song would you like to edit? Please type the exact song name.\n\n");
					scanf(" %[^\n]s", songTitle);
					strcpy(songTitle, songTitle); //taking the song title and removing underscores
				}
				else { strcpy(songTitle, titleReader->data.songTitle); } //if the artist only has one song
				titleReader = tempList.pHead;
				while (titleReader != NULL && strcmp(titleReader->data.songTitle, songTitle) != 0) //iterating through the list of songs by the given artist to find the song the user wants to edit
				{
					titleReader = titleReader->pNext;
				}
				if (titleReader == NULL) { printf("There is no song with that title\n\n"); } 
				else 
				{
					printf("What would you like to rate the song? [1 - 5]\n");
					if (scanf("%d", &rating) == 1 && rating >0 && rating < 6)
					{
						Node* pTemp = list.pHead;
						while (strcmp(pTemp->data.songTitle, titleReader->data.songTitle) != 0 || strcmp(pTemp->data.artist, titleReader->data.artist) != 0)
						{
							pTemp = pTemp->pNext;      //traversing through the list of songs to find the song that needs to be edited
						}
						pTemp->data.rating = rating; //setting the rating value to the new value
					}
					else
					{
						printf("Rating invald. Please try again\n\n"); //if the user inputs anything other than 12345 then it prints this message and displays main menu
					}
				}
			}
		}

		else if (userInput == 9) //play
		{
			printf("(1) Play\n(2) Play a specific song\n");
			scanf("%d", &userInput);
			if (userInput == 1)
			{
				playSong(&list.pHead, "\0");
			}
			else if (userInput == 2)
			{
				printf("\nWhat song do you want to play? Please type the exact song name.\n");
				scanf(" %[^\n]s", userInputStr);
				playSong(&list.pHead, userInputStr);
			}
			else { printf("Invalid value\n\n"); }
		}

		else if (userInput == 10) //shuffle
		{
			printf("This option is not yet complete\n\n");
		}

		else if (userInput == 11) //exit
		{
			if (list.pHead != NULL) saveFile(&list); //if the list isnt empty then save the list -> if user forgets to load then close, this prevents loss of all records
			exit = 1;
		}

		else if (userInput == 1337) //hidden test cases
		{
			printf("Testing in progress.");
			Sleep(500);
			printf(" .");
			Sleep(500);
			printf(" .\n\n");
			testDelete();
			testInsert();
			testShuffle();
		}

		else
		{
			printf("Invalid value, please try again. \n\n");
		}
	}while (exit != 1);
	return 1;
}
