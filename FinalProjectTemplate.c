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

//add more here////
#define COLUMNS 70
#define ROWS 71
#define EMPTY_SPACE ' '
#define FLOOR '-'
#define WALL '|'

//2D character array which the maze is mapped into 
char BOARD[COLUMNS][ROWS];

//Struct Definition



/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//them below the main function////
/////////////////////////////////
//Function draws the characters on the board
void draw_board(void);

//Draws character use to the screen at position x,y 
void draw_character(int x, int y, char use);
//Determines which spots on the board should have a character '-' or '|'
void generate_board();


int main(){
	
	char response;
	int minmumLength;
	printf("Hello, this is a typing game. You will need to type the words as they appear/n");
	printf("Would you like to play or add a word?/n");
	printf("You currently have 58 words that can be used. (p/w)");
	scanf("%c", &response);
	//if they do want to enter a word:
	printf("What would you like you minimum word length to be?");
	scanf("%d", &minmumLength);
	//go into conditional that adds a word if they choose to add a word
	
	
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////


//I will edit this up a bit to make it work, this is copy pasted from lab 9
int read_words(char* WL[MAXWORDS], char* file_name) {
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp)) {
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL) 
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}

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
					//causes the board to have FLOOR on the top and bottom
					if( i == 0 || i == 70){
				BOARD[i][j] = FLOOR;
			}//causes the board to have WALL on the top and bottom
			else if (j == 0 || j == 70 || j == 71){
				BOARD[i][j] = WALL;
			}
		}

	}
	
}

//Paste in the function from lab 9 that stores the values of each word so that the words can each be removed