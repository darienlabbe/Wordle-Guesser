/*******************************************************************************
* Assignment: Project3 - Check Program for Wordle Game                         *
* Author: Dr. Watts                                                            *
* Date: Fall 2022                                                              *
* File: check.cpp                                                              *
*                                                                              *
* Description: This file contains the the code for comparing the guess         *
*              (passed to it as a parameter) to the secret word.               *
*              If no word is passed, this program will exit with a 1.          *
*******************************************************************************/

#include <iostream>
#include <fstream>
#include "execute.h"
using namespace std;

// Function prototypes - implementations follow "main"

string getSecretWord ();
string checkWord (const string & secret, const string & guess);
bool letFound(string guess, string output, char letterToSearch);

/*******************************************************************************
* Function: main                                                               *
*                                                                              *
* Parameters: argc is the number of parameters passed and argv[1] should be    *
*             the word to be compared to the secret word.                      *
* Return value: 0 if successful. Will exit with 1 if no word is provided.      *
* Description: This function will check that a parameter has been passed.      *
*              It will call getSecretWord and checkWord and write out the      *
*              results.                                                        *
*******************************************************************************/

int main (int argc, char * argv [])
{
	// Check to see if a guess has been passed as an argument.
	if (argc < 2)
	{
		cout << "ERROR";
		exit (1);
	}
	// Call function to get the secret word.
	string secret = getSecretWord ();
	// Call function to compare the guess to the secret word.
	string result = checkWord (secret, argv[1]);
	// Write out the result string.
	// (The execute pipe will pick it up from standard output.)
	cout << result << endl;
	return 0;
}

/*******************************************************************************
* Function: getSecretWord                                                      *
*                                                                              *
* Parameters: None.                                                            *
* Return value: A string containing the secret word.                           *
* Description: This function will open the file "secret.txt" and read the      *
*              secret word from the file.                                      *
*******************************************************************************/

string getSecretWord ()
{
	ifstream SF ("secret.txt");
	string secret;
	SF >> secret;
	SF.close ();
	return secret;
}

/*******************************************************************************
* Function: checkWord                                                          *
*                                                                              *
* Parameters: Strings containing the secret word and the guess.                *
* Return value: A string containing the results of the comparison.             *
* Description: This function will compare the guess to the secret word and     *
*              create a string that describes the similarity.                  *
*              For example, secret word: world                                 *
*                                 guess: sword                                 *
*                                result: -...+                                 *
*              's' is not in the secret word.                                  *
*              'w', 'o', and 'r' are in the secret word in different positions.*
*              'd' is in both words at the same position.                      *
*******************************************************************************/

string checkWord (const string & tarWord, const string & guess)
{
    string output = "     ";
    size_t found;

    //Check if word is in Dictionary
    string cmd = "grep " + guess + " Dictionary5.txt";
    string resp = execute (cmd);
    if (resp == "") //If word is not present in Dictionary5.txt 
	return "ERROR";
    else {
        for (int i = 0; i < tarWord.length(); i++) {
            if (tarWord[i] == guess[i])         //If letter is right & pos
                output[i] = '+';
            found = tarWord.find(guess[i]);
            if (found != string::npos) {        //If letter is in tarWord
                if (output[i] != '+' && !letFound(guess, output, guess[i]))
                    output[i] = '.';
            }
        }
        //Remaining letters are simply not in tarWord if not + or .
        for (int i = 0; i < tarWord.length(); i++) {
            if (output[i] == ' ')
                output[i] = '-';
        }
    }
    return output;
}

/******************************************************************************
* Function name: Letter Found                                                 *
*                                                                             *
* Input parameters: string guess, string output, char letterToSearch          *
* Returned result: bool result (true/false)                                   *
* Description: Function returns true if the letter was already searched and   *
*         was a '.'. The function is only implemented when checking to see    *
*         if the current letter should be a '.'.                              *
******************************************************************************/

bool letFound(string guess, string output, char letterToSearch) {
    for (int i = 0; i < output.length(); i++) {
        //If the current letter is a duplicate and was already found to be a '.'
        //then return true, otherwise, return false
        if (letterToSearch == guess[i] && output[i] == '.')
            return true;
    }
    return false;
}
