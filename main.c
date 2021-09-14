/*****************************************************************************************
* Programmer: Josh Maloy                                                                 *
* Class: CptS 122, Fall 2021; Lab Section 1                                              *
* Programming Assignment: PA1                                                            *
* Date: September 1, 2021                                                                *
* Description: This program displays a user interface in a commandline window with       *
* multiple controls simulating a music player. It can load from a file, save to a file,  *
* edit songs, rate songs, print out the list of songs, "play" songs, and exit.           *
******************************************************************************************/


#include "PA2.h"

int main()
{
	int c; //for clearing stdin
	int exit = 0;
	int userInput = 0;
	char userInputStr[50] = "";
	List list = { NULL };
	do {
		userInput = 0;
		//while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c //these two fflush every loop just to make sure weird stuff doesnt happen
		fflush(stdout);
		displayMenu();

		//fgets(userInputStr); //https://stackoverflow.com/questions/10156696/fgets-not-waiting-for-input

		scanf("%d", &userInput);

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
			while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c 
			if (userInput == 1) //dispay all songs
			{
				printList(&list);
			}
			else if (userInput == 2)
			{
				printf("Which artist? Example: \"Eilish,_Billie\" or \"Eminem\"\n");
				scanf("%s", userInputStr);
				while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c

				List tempList = *artistSearch(&list, underscoreRemover(userInputStr)); //calling the artist search function - returns a list of songs made by the given artiste
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
			printf("This option is not yet complete\n\n");
		}

		else if (userInput == 5) //delete
		{
			printf("This option is not yet complete\n\n");
		}

		else if (userInput == 6) //edit
		{
			printf("Which artist? Example: \"Eilish,_Billie\" or \"Eminem\"\n");
			scanf("%s", userInputStr);
			while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			char songTitle[50] = "";
			Node* titlePlacer = list.pHead;
			List tempList = *artistSearch(&list, underscoreRemover(userInputStr));
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
					printf("\nWhich song would you like to edit? Please type the exact song name with underscores instead of spaces\n\n");
					scanf("%s", songTitle);
					strcpy(songTitle, underscoreRemover(songTitle)); //taking the song title and removing underscores
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
					Record tempRecord = *recordEditor(titleReader->data); //calling the recordEditor function and setting equal to a tempRecord where the edits are
					while (strcmp(titlePlacer->data.songTitle, titleReader->data.songTitle) != 0  || strcmp(titlePlacer->data.artist, titleReader->data.artist) != 0) //going through the original list and finding the song intended to edit
					{
						titlePlacer = titlePlacer->pNext;
					}
					titlePlacer->data = tempRecord; //adding the edits to the original list
				}
			}
			}

		else if (userInput == 7) //sort
		{
			printf("This option is not yet complete\n\n");
		}

		else if (userInput == 8) //rate
		{
			int rating = 0;
			printf("Which artist? Example: \"Eilish,_Billie\" or \"Eminem\"\n");
			scanf("%s", userInputStr);
			while ((c = getchar()) != '\n' && c != EOF) { } //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
			char songTitle[50] = "";
			List tempList = *artistSearch(&list, underscoreRemover(userInputStr));
			Node* titleReader = tempList.pHead;
			if (titleReader != NULL) //checking if the artist has any songs in the list
			{
				if (titleReader->pNext != NULL) //checking if the artist has more than just one song
				{
					printf("\n"); //formatting
					printf("Songs by %s:\n", titleReader->data.artist);
					while (titleReader != NULL) //iterating through the list of songs written by the given artist and printing the titles
					{
						printf("%s\n", titleReader->data.songTitle);
						titleReader = titleReader->pNext;
					}
					printf("\nWhich song would you like to edit? Please type the exact song name with underscores instead of spaces\n\n");
					scanf("%s", songTitle);
					while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
					strcpy(songTitle, underscoreRemover(songTitle)); //taking the song title and removing underscores
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
						while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
						Node* pTemp = list.pHead;
						while (strcmp(pTemp->data.songTitle, titleReader->data.songTitle) != 0 || strcmp(pTemp->data.artist, titleReader->data.artist) != 0)
						{
							pTemp = pTemp->pNext;      //traversing through the list of songs to find the song that needs to be edited
						}
						pTemp->data.rating = rating; //setting the rating value to the new value
					}
					else
					{
						while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
						printf("Rating invald. Please try again\n\n"); //if the user inputs anything other than 12345 then it prints this message and displays main menu
					}
				}

			}
		}

		else if (userInput == 9) //play
		{
			printf("(1) Play\n(2) Play a specific song\n");
			scanf("%d", &userInput);
			while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c 
			if (userInput == 1)
			{
				playSong(&list.pHead, "\0");
			}
			else if (userInput == 2)
			{
				printf("\nWhat song do you want to play? Please use underscores instead of spaces\n");
				scanf("%s", userInputStr);
				while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c 
				playSong(&list.pHead, underscoreRemover(userInputStr));
			}
			else { printf("Invalid value\n\n"); }
		}

		else if (userInput == 10) //shuffle
		{
			printf("This option is not yet complete\n\n");
		}

		else if (userInput == 11) //exit
		{
			saveFile(&list);
			exit = 1;
		}

		else
		{
			printf("Invalid value, please try again. [PRESS ENTER]\n\n");
			while ((c = getchar()) != '\n' && c != EOF) {} //from https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c //these two fflush every loop just to make sure weird stuff doesnt happen
			//scanf("%s", &userInputStr);			//incase the user inputs a non-int value. if this isnt here the program loops infinitely
		}
	}while (exit != 1);
	return 1;
}
