//SE 185: Final Project Template//
/////////////////////////
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

//Constant variables////
#define COLUMNS 30
#define ROWS 31
#define FLOOR '_'
#define WALL '|'
#define EMPTY_SPACE ' '

//2D character array which the maze is mapped into 
char BOARD[COLUMNS][ROWS];
//Keeps track of the remaining number of words the user can add from the file to the game
int remainingWords = 58;

//Struct Definition




/*
	USER-DEFINED FUNCTIONS
*/

//Function draws the characters on the board
void draw_board(void);

//Draws character use to the screen at position x,y 
void draw_character(int x, int y, char use);
//Determines which spots on the board should have a character '-' or '|'
void generate_board();





int main(){
	 /* 	Setup screen for Ncurses
        The initscr function is used to setup the Ncurses environment
        The refreash function needs to be called to refresh the outputs
        to the screen */
    initscr();
    refresh();
	
	//These 2 lines are going to be moved into the conditional; they are just here for testing the board
	generate_board();
	draw_board();
	refresh();
	
	char response;
	int minmumLength;
	printf("Hello, this is a typing game. You will need to type the words as they appear\n");
	printf("Would you like to play or add a word?\n");
	printf("You currently have %d words that can be used.\nType 'p' to play, 'w' to add a word or any other button to exit: ", remainingWords);
	scanf("%c", &response);
	//if they do want to enter a word:
	if(response == 'w')
	{
		remainingWords--;
	printf("What would you like you minimum word length to be? ");
	scanf("%d", &minmumLength);
	}// Does the same thing as above but without adding a word
	else if(response == 'p'){
		
	}
	else{
		exit(1);
	}

	endwin();
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////


//I will edit this up a bit to make it work, this is copy pasted from lab 9
// int read_words(char* WL[MAXWORDS], char* file_name) {
	// int numread = 0;
	// char line[WORDLENGTH];
	// char *p;
	// FILE* fp = fopen(file_name, "r");
	// while (!feof(fp)) {
		// p = fgets(line, WORDLENGTH, fp);
		// if (p != NULL) 
		// {
			// trimws(line);
			// WL[numread] = (char *)malloc(strlen(line) + 1);
			// strcpy(WL[numread], line);
			// numread++;
		// }
	// }
	// fclose(fp);
	// return numread;
// }

void draw_board(void){
	for(int i = 0; i< COLUMNS;++i){
		for(int j= 0; j< ROWS; ++j){
		draw_character(i,j,BOARD[i][j]);	
		}
	}
}

void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}


void generate_board(){
		for(int i = 0; i< COLUMNS;++i){
			for(int j= 0; j< ROWS; ++j){
					//causes the board to have WALL on the top and bottom
					if( i == 0 || i == ROWS-2 || i == ROWS-1){
				BOARD[i][j] = WALL;
			}//causes the board to have FLOOR on the left and right
					else if (j == 0 || j == COLUMNS-1){
				BOARD[i][j] = FLOOR;
			}
			else{
				BOARD[i][j] = EMPTY_SPACE;
			}
		}

	}
	
}

//Paste in the function from lab 9 that stores the values of each word so that the words can each be removed


