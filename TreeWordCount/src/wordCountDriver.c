/***************************************************************************
File name:  wordCountDriver.c
Author:     Damon Holland
Date:       Nov 9, 2019
Class:      CS300
Assignment: TreeWordCount
Purpose:    
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

int main (int argc, char *argv[])
{
	TreeNodePtr psRoot;

	char word[26];
	int currentWordCount;

	//The file used to read data
	FILE* inFile = fopen (argv[1], "r");

	//Open and validate file
	if(!inFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//Initialize Tree
	trLoadErrorMessages ();
	trCreate (&psRoot);

	//Read the data from the file
	while (!feof (inFile))
	{
		fscanf(inFile, "%s", word);
		//If the word is already in the tree, update the count
		if (trFind (psRoot, word, &currentWordCount))
		{
			trUpdate (psRoot, word, currentWordCount + 1);
		}
		//If the word isnt already in the tree, add it
		else
		{
			trInsert (&psRoot, word, 1);
		}
	}

	trPrintInOrder (psRoot);

	trTerminate (&psRoot);

	fclose (inFile);
	return EXIT_SUCCESS;
}
