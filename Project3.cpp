/** ***************************************************************************   
* Assignment: Project 3 - The Game of Wordle!
* @author Dr. Watts                                                               
* @date Fall 2022                                                                 
* @file Project1.cpp                                                              
*                                                                                 
* @details This file contains the driver program for the game of Wordle.
*************************************************************************** **/

#include <iostream>
#include <iomanip>
#include <vector>
#include "Game.h"
using namespace std;

/** ***************************************************************************   
* Function: main                                                                  
*                                                                                 
* @param None                                                                
* @return An integer - 0 on completion                                      
* @details This function will play a game of Worldle by creating an           
*              instance of the Game class and guessing words from an initial      
*              list of starter words followed by words suggested by the           
*              Game class object.                                                 
*************************************************************************** **/

int main ()
{
	Game wordle;
	vector <string> startingWords;
	startingWords.push_back ("slate");
	
	int code = 0;
	int attempt = 1;
	do
	{
		string guess;
		// Use starting words before asking wordle to choose a word
		if (attempt <= startingWords.size())
			guess = startingWords[attempt-1];
		else
			 guess = wordle.ChooseWord ();
		// If wordle has run out of possibilities it will return
		// the string "quit!"
		if (guess == "quit!")
			code = 2;
		else
		{
			code = wordle.CheckWord (guess);
			cout << setw (2) << attempt << " : " << guess << " ==> " << wordle << endl;
		}
		// Only permit 20 guesses
		if (attempt++ > 20)
			code = 3;
	} while (!code);
	// Display message based on value stored in code
	switch (code)
	{
		case 1:
			cout << "I Win!" << endl;
			break;
		case 2:
			cout << "I Quit!!" << endl;
			break;
		case 3:
			cout << "I'll do better next time!" << endl;
			break;
	}
	return 0;
}
