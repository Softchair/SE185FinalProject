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
#include<stdio.h>
#include<stdlib.h>

//add more here////

//////////////////////
//Struct Definition//
////////////////////


/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//tehm below the main function////
/////////////////////////////////

int main(){
	
	char response;
	int minimumLength;
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
