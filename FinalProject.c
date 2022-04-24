/* 
Team xx (please insert your team number instead of xx)
Team member 1 Kaden Wingert | "Percentage of Contribution to The Project"
Team member 2 Daniel Karpov | "Percentage of Contribution to The Project"
Team member 3 Ethan Meyer | "Percentage of Contribution to The Project"
Team member 4 Camden Fergen | "Percentage of Contribution to The Project"
*/

////////////////////
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
////////////////////

/* Constant variables */
#define COLUMNS 50
#define ROWS 50
#define FLOOR '_'
#define WALL '|'
#define EMPTY_SPACE ' '
#define WORDLENGTH 20

/////////////////////////////////
/* Function initialization */

/* Iterates over a file to read all the words from
   it and then returns the num of words avalible to use */
int readWords(char* fileName, int minLength);

/* Iterates over the BOARD[][] variable and then
   uses drawChar to print it to the screen */
void drawBoard(void);

/* This function draws a character to the screen
   Using x and y */
void drawChar(int x, int y, char use);

/* Generates an empty board to print to the screen
   using WALL, FLOOR, and EMPTY_SPACE assigned to
   the BOARD[][] variable */
void generateBoard();

/* End function initialization */
/////////////////////////////////

/* Structure to hold the words during the game */
typedef struct {
	char word[WORDLENGTH];
	int row;
	int col;
} wordStruct;

/////////////////////////////////
/* Global variables */

/* Variable for the game board */
char BOARD[ROWS][COLUMNS];

/* Varible of game words */
//Fun fact, there are 1000 words in the word list already...
wordStruct gameWords[2000];

/* Varible to hold number of words */
int numWords = 0;
int numGameWords = 0;

/* End global variables */
/////////////////////////////////

/* Main function to run the game */
int main() {

	/* Min length of a word */
	int minWordLen = 0;

	/* Game setup */

	//Reads from wordList file and calcs numWords
	char wordsFile[20] = "wordList.txt";
	FILE* fp = fopen(wordsFile, "r");

	//Checks to make sure the file exists
		if(fp == NULL) {
			printf("The file could not be opened");
		return -1;
	}

	//Reads num of words in file
	char* p;
	while(!feof(fp)) {
		char temp[WORDLENGTH];
		p = fgets(temp, WORDLENGTH, fp);

		if(p != NULL) {
			numWords++;
		}
	}
	fclose(fp);

	/* End game setup */
	

	//Generate board, move later
    // initscr();
    // refresh();
	// generate_board();
	// draw_board();
	// refresh();

	//Variable to hold user response
	char response;

	//Staring messages
	printf("Hello, this is a typing game. You will need to type the words as they appear\n");
	printf("Would you like to play or add a word?\n");
	printf("You currently have %d words that can be used.\n", numWords);
	printf("Type 'p' to play, 'w' to add a word or any other button to exit: ");
	scanf("%c", &response);
	
	/* Enters conditional if the user wants to add a word 
	   Uses do while loop to add words till user is done
	   adding words. */
	if(response == 'w') {
		FILE* fp = fopen(wordsFile, "a");

		//Checks to make sure the file exists
		if(fp == NULL) {
			printf("The file could not be opened");
		return -1;
		}

		while(response == 'w') {
			//Varible to hold word to be added
			char word[WORDLENGTH];

			printf("What word would you like to add?\n");
			scanf("%s", word);

			//Write into file with contents of new word
			fprintf(fp, "\n%s", word);

			//Increment the number of words
			numWords++;

			//Ask the user if they want to add any more words or play the game
			printf("There are now %d words. Would you like to play or add another word? (p/w): ", numWords);
			scanf(" %c", &response);
		}

	} else if(response == 'p') {

		printf("What would you like you minimum word length to be? ");
		scanf("%d", &minWordLen);

		//Uses readWords function to popualte words for game
		numGameWords = readWords(wordsFile, minWordLen);

	} else {
		return 0;
	}

	for(int i = 0; i < numGameWords; i++) {
		printf("%s\n", gameWords[i].word);
	}

	//Cleanup board
	endwin();
	return 0;
}

//////////////////////////////////////
//User Defined Functions' Definition//
//////////////////////////////////////


/* Iterates over a file to read all the words from
   it and then returns the num of words in file */

//RE DO THIS TO ONLY SCAN CERTAIN WORDS
int readWords(char* fileName, int minLength) {
	int numread = 0;
	char line[WORDLENGTH];
	char *p;

	//Opens the file through filename
	FILE* fp = fopen(fileName, "r");

	//Checks to make sure the file exists
	if(fp == NULL) {
		printf("The file could not be opened");
		return -1;
	}

	//While its not the end of file (feof)
	while (!feof(fp)) {

		//Gets the first word
		p = fgets(line, WORDLENGTH, fp);

		//If there is a word
		//Note, its minLength + 1 to account for null char and new line
		if (p != NULL && strlen(p) > minLength + 1) {
			//trimws(line); This was a function from lab 9? didnt add it here yet

			wordStruct tempWord;

			//Copies data over to temp word to be added to array
			strncpy(tempWord.word, line, 20);
			tempWord.row = 0; tempWord.col = 0;

			gameWords[numread] = tempWord;
			numread++;
		}
	}

	//Closes the file
	fclose(fp);
	return numread;
}

/* This function draws a character to the screen
   Using x and y */
void drawChar(int x, int y, char use) {
    mvaddch(x, y, use);
    refresh();
}

///////////////////////////////////////////////////////
/* Functions to create and draw board the the screen */
///////////////////////////////////////////////////////

/* Iterates over the BOARD[][] variable and then
   uses drawChar to print it to the screen */
void drawBoard(void) {
	for(int irow = 0; irow < ROWS; irow++){
		for(int jcol = 0; jcol < COLUMNS; jcol++){
		drawChar(irow, jcol, BOARD[irow][jcol]);	
		}
	}
}

/* Generates an empty board to print to the screen
   using WALL, FLOOR, and EMPTY_SPACE assigned to
   the BOARD[][] variable */
void generateBoard() {

	//Iterates over the rows
	for(int irow = 0; irow < ROWS; irow++) {

		//Iterates over the columns
		for(int jcol = 0; jcol < COLUMNS; jcol++) {

			/* This condition checks if its the first or last two rows
		       then prints a line of FLOORS */
			if(irow == 0 || irow == ROWS - 1 || irow == ROWS - 2) {
				BOARD[irow][jcol] = FLOOR;
			
			/* This condition places walls on left and right */
			} else if (jcol == 0 || jcol == COLUMNS - 1) {
				BOARD[irow][jcol] = WALL;

			/* Else places everything as empty space */
			} else {
				BOARD[irow][jcol] = EMPTY_SPACE;
			}

		//end for
		}
	//end for
	}
}