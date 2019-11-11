/**************************************************************************
File name:  wordCountDriver.c
Author:     Damon Holland
Date:       Nov 9, 2019
Class:      CS300
Assignment: TreeWordCount
Purpose:    The driver for TreeWordCount assignment. Takes a text file with
						words in it and outputs each word once with the amount of times
						that word was included in the file. Uses a tree data type to
						accomplish this.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"


/*************************************************************************
 Function: 	 	main

 Description: Main driver for the TreeWordCount assignment

 Parameters:	argc - an integer that will contain the number of files given
 	 	 	 	 	 	 	 	 	 	 as input to the program
 	 	 	 	 	 	 	argv[] - the string which contains the file name to read as
 	 	 	 	 	 	 						data for the program

 Returned:	 	Exit Status
 ************************************************************************/
int main (int argc, char *argv[])
{
	//Constant used to increment word count and used as an initial value
	const int INCREMENT = 1;

	//The tree
	TreeNodePtr psRoot;

	//String to store data from the file
	char szWord[WORD_MAX + 1];

	//Buffer to store number of times the word is included in the tree
	int currentWordCount;

	//The file used to read data
	FILE* inFile = fopen (argv[1], "r");

	//********** Open and validate file **********
	if (!inFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//********** Initialize Tree **********
	trLoadErrorMessages ();
	trCreate (&psRoot);

	//********** Read the data from the file **********
	while (!feof (inFile))
	{
		fscanf (inFile, "%s", szWord);
		//Tries to insert the new word
		if (!trInsert (&psRoot, szWord, INCREMENT))
		{
			//If the word was already contained, increment the count
			trFind (psRoot, szWord, &currentWordCount);
			trUpdate (psRoot, szWord, currentWordCount + INCREMENT);
		}
	}

	//********** Print the tree **********
	trPrintInOrder (psRoot);

	//********* Terminate tree and close file **********
	trTerminate (&psRoot);
	fclose (inFile);

	return EXIT_SUCCESS;
}
