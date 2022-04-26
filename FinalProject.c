/* 
Team member 1 Kaden Wingert | "30%"
Team member 2 Daniel Karpov | "Percentage of Contribution to The Project"
Team member 3 Ethan Mayer 	| "100000000%"
Team member 4 Camden Fergen | "90%"
*/

////////////////////
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <time.h>
////////////////////

/* Constant variables */
#define COLUMNS 50
#define ROWS 30
#define FLOOR '_'
#define WALL '|'
#define EMPTY_SPACE ' '
#define WORDLENGTH 20

/////////////////////////////////
/* Function initialization */

/* Function to hold the game running
   Use getstr(userWord) to get input from user */
int game();

/* Prints a word to the screen if it hasnt been printed before */
void newPrintToScreen(char* word, int* wordsOnScreen, int newRow);

/* Updates the location of words on the screen 
   Also increments them all down by num seconds
   passed since last call */
void updateLoc(int secsPast, int wordsOnScreen);

/* Removes a word from the screen */
void removeWord(char userWord[], int wordsOnScreen);

/* Finds the lowest word and returns an int */
int lowestWord(int wordsOnScreen);

/* Clears the typing space so its empty */
void clearTypingSpace();

/* Iterates over a file to read all the words from
   it and then returns the num of words avalible to use */
int readWords(char* fileName, int minLength);

/* This function draws a character to the screen
   Using x and y */
void drawChar(int x, int y, char use);

/* Trims the whitespace of a string */
void trimws(char* str);

/* Iterates over the BOARD[][] variable and then
   uses drawChar to print it to the screen */
void drawBoard(void);

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

/* Varible for avalible words based on length */
//Fun fact, there are 1000 words in the word list already...
char wordsToUse[2000][WORDLENGTH];

/* Variable of words on screen */
wordStruct gameWords[100];

/* Variable to hold number of words */
int numWords = 0; //For total words
int numGameWords = 0; //For words that can be used

time_t begin;
time_t end;

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

		//Uses readWords function to populate words for game
		numGameWords = readWords(wordsFile, minWordLen);
	} else {
		return 0;
	}

	int score = game();
	printf("You made it %d seconds! Congrats", score);

	//Cleanup board
	endwin();
	return 0;
}

////////////////////////////////
/* Functions to play the game */
////////////////////////////////

/* Function to hold the game running
   Use getstr() to get input from user 
   or use getUserInput */
int game() {
	/* Setup for board */
	//Sets up ncurses board
    initscr();
    refresh();

	//Generates and draws board
	generateBoard();
	drawBoard();
	refresh();
	/* End setup for board */

	/* Random setup */
	srand(time(NULL));

	/* Variables for the game */
	int score = 0; //Score, stored in seconds
	int numWordsOnScreen = 0; //Number of words on screen
	int timeTaken = 0; //Time taken to enter a word
	char userWord[WORDLENGTH]; //Word typed
	/* End variables for the game */

	/* Setup game before while loo */

	//Gets a random num for random word
	int randNum = rand() % numGameWords;
		
	//Variable to hold the newWord to be added
	char newWord[WORDLENGTH];

	//Copies the random word to newWord, then prints it
	strcpy(newWord, wordsToUse[randNum]);
	newPrintToScreen(newWord, &numWordsOnScreen, 1);

	do {
		timeTaken = 0;

		//Clears the typing space, then gets user input
		clearTypingSpace();
		mvprintw(ROWS + 2, 0, "Type here: ");

		time_t secondsBefore = time(NULL);
		time_t secondsAfter;

		getstr(userWord);

		secondsAfter = time(NULL);

		removeWord(userWord, numWordsOnScreen);
		timeTaken = secondsAfter - secondsBefore;

		updateLoc(timeTaken, numWordsOnScreen);
		
		for(int i = 0; i < timeTaken; i++) {
			//Gets a random num for random word
			int randNum = rand() % numGameWords;
		
			//Variable to hold the newWord to be added
			char newWord[WORDLENGTH];

			//Copies the random word to newWord, then prints it
			strcpy(newWord, wordsToUse[randNum]);
			newPrintToScreen(newWord, &numWordsOnScreen, (timeTaken - i));

			//gameWords[numWordsOnScreen].row = gameWords[numWordsOnScreen].row + (timeTaken - i);
		}

		for(int i = 0; i < numWordsOnScreen; i++) {
			mvprintw(ROWS + 3 + i, 0, "%d/%d: %s", i, numWordsOnScreen, gameWords[i].word);
		}

		//TODO
		//move words down the x amount
		//generate x words dependent on how many seconds passed

		score += timeTaken;

	} while(lowestWord(numWordsOnScreen) < ROWS);

	endwin();
	return score;
}

/* Prints a word to the screen if it hasnt been printed before */
void newPrintToScreen(char* word, int* wordsOnScreen, int newRow) {
	wordStruct tempWord;
	srand(time(NULL));

	int length = strlen(word);
	int col = (rand() % COLUMNS) + 1;

	//Makes sure that the words are printed within the walls of the board
	if(col + length >= COLUMNS){
		col -= length+1;
	}

	mvprintw(1, col, "%s", word);

	//Initialize word struct
	strncpy(tempWord.word, word, 20);
	tempWord.col = col;
	tempWord.row = newRow;

	//Adds the struct to array of words on screen
	int val = *wordsOnScreen;
	gameWords[val] = tempWord;

	*wordsOnScreen = *wordsOnScreen + 1;
}

/* Updates the location of words on the screen 
   Also increments them all down by num seconds
   passed since last call */
void updateLoc(int secsPast, int wordsOnScreen) {
	//Calls draw board to clear the space
	drawBoard();

	for(int i = 0; i < wordsOnScreen; i++) {

		//Passes over removed words
		if(strcmp(gameWords[i].word, "NULL") == 0) {
			continue;
		}

		//Updates to new location
		gameWords[i].row = gameWords[i].row + secsPast;
		
		//Used to test this function, comment out
		//mvprintw(ROWS + 3 + i, 0, "%d/%d: %s", i, wordsOnScreen, gameWords[i].word);

		//Printing of word
		mvprintw(gameWords[i].row, gameWords[i].col, "%s", gameWords[i].word);
	}
}

/* Removes a word from the screen */
void removeWord(char userWord[], int wordsOnScreen) {
	//Iterates over the array of words on screen
	for (int i = 0; i < wordsOnScreen; i++) {

		//If the user word is found
		if(strcmp(userWord, gameWords[i].word) == 0) {

			//Iterates over the location of the user word, removing it
			for(int j = 0; j < strlen(userWord); j++) {
				mvprintw(gameWords[i].row, gameWords[i].col + j, " ");;
				refresh();
			}

			//Copies NULL into the word that was removed
			strncpy(gameWords[i].word, "NULL", 20);
		}
	}
}

/* Finds the lowest word and returns an int */
int lowestWord(int wordsOnScreen) {
	//Base case
	if(wordsOnScreen == 1) {
		return gameWords[0].row;
	}

	int lowest = gameWords[0].row;

	//Iterates over remaining words on screen
	for(int i = 1; i < wordsOnScreen; i++) {
		int temp = gameWords[i].row;

		//If the new word is lower, assign the lowest to temp
		if(temp > lowest) {
			lowest = temp;
		}
	}

	return lowest;
}

/* Clears the typing space so its empty */
void clearTypingSpace() {
	for(int i = 0; i < COLUMNS; i++) {
		mvprintw(ROWS + 2, i, " ");
	}
}

////////////////////
/* Misc functions */
////////////////////


/* Iterates over a file to read all the words from
   it and then returns the num of words in file */
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
			trimws(line);

			//Copies data over to array of words to use
			strncpy(wordsToUse[numread], line, 20);

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

/* Trims the whitespace of a string */
void trimws(char* str) {
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
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
