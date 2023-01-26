/** ***************************************************************************
* Assignment: Project 3 - The Game of Wordle!
* @author Dr. Watts                                                            
* @date Fall 2022                                                              
* @file Game.cpp                                                               
*                                                                              
* @details This file contains the implementation of the Game class.        
*************************************************************************** **/

#include <fstream>
#include <algorithm>
#include "execute.h"
#include "Game.h"
using namespace std;

/** ***************************************************************************
* @def DEBUG false
*        Sets the DEBUG flag
* @def debug if (DEBUG) cout
*        Writes to standard output if DEBUG is true
*************************************************************************** **/

#define DEBUG false
#define debug if (DEBUG) cout

/** ***************************************************************************
* @brief Game Default Constructor                                           
*                                                                              
* @param None                                                             
* @return None                                                           
* @details This function will initialize an instance of the Game class.    
*************************************************************************** **/

Game::Game ()
{
	GetWords ();
	sort (list.rbegin(), list.rend());
	InitInfo ();
	position = 0;
}

/** ***************************************************************************
* @brief Game Destructor                                                    
*                                                                              
* @param None                                                             
* @return None                                                           
* @details This function will clear the vectors used by this instance      
*              of the Game.                                                    
*************************************************************************** **/

Game::~Game ()
{
	list.clear();
	for (int p = 0; p < 5; p++)
		for (int c = 0; c < 26; c++)
			info[p][c].clear();
}

/** ***************************************************************************
* @brief ChooseWord                                                         
*                                                                              
* @param None                                                             
* @return string value                                                   
* @details This function will return the next possible word in the word    
*              list vector.                                                    
*************************************************************************** **/

string Game::ChooseWord ()
{
	result = "";
	while (position < list.size() && list[position].GetPossible() == false)
		position++;
	// If no possible words remain
	if (position >= list.size())
		return "quit!";
	return list[position].GetWord();
}

/** ***************************************************************************
* @brief CheckWord                                                          
*                                                                              
* @param guess is a string containing the current guess                            
* @return an integer inducting the status of the check
* @details This function will use the check program to determine the level  
*              of similarity between the guess and the secret word. It will    
*              also update the info vectors and will set the possible flags    
*              in the word list to "false" if it determines that a word is     
*              no longer an option.                                            
*              This function will return 1 if the guess is the secret words;   
*              it will return 0 otherwise.                                     
*************************************************************************** **/

int Game::CheckWord (const string & guess)
{
	string cmd = "./check " + guess;
	result = execute (cmd).substr(0,5);
	debug << "\nGuess is " << guess << "; result is " << result
              << "; updating info.\n";
	if (result == "ERROR")
		return 0;
	if (result == "+++++")
		return 1;
	for (int i = 0; i < 5; i++)
	{
		debug << "\tposition: " << i << " letter: " << guess[i]
	              << " result: " << result[i] << "\n\t";
		int idx = guess[i]-'a';
		switch (result[i])
		{
			// If letter is not in word, mark all words in list containing
			// that letter, in any position, as not a possibility.
			case '-':
				// If there is a repeat letter already found to exist and this
                // case is a '-' then that means that this case should be run
                // as if it were a '.'
                if (letFound(guess, result, guess[i])) {
                    debug << guess[i]
                          << " is in secret word, but not at this position\n";
                    ClearInfoList (info[i][idx]);
                    break;
                }
                debug << guess[i]
				      << " is not in secret word\n";
				for (int j = 0; j < 5; j++)
					ClearInfoList (info[j][idx]);
				break;
			// If letter is in this position, mark all words in list
			// containing a different letter in this position as not a
			// possibility.
			case '+':
				debug << guess[i]
				      << " is in secret word at this position\n";
				for (int j = 0; j < 26; j++)
					if (j != idx)
						ClearInfoList (info[i][j]);
				break;
			// If letter is in the word, but not in this position, mark 
			// all words in list with letter in this position as not a 
			// possibility.
			case '.':
				debug << guess[i]
				      << " is in secret word, but not at this position\n";
				ClearInfoList (info[i][idx]);
				break;
		}
	}
	debug << endl;
	return 0;
}

/** ***************************************************************************
* @brief Letter Found
*
* @param guess is a string for the guess
* @param output is the string that holds the check
* @param letterToSearch is the letter to check
* @return The bool result (true/false)
* @details Function returns true if the letter was already searched and
*               was a '.'. The function is only implemented when checking to
*               see if the current letter should be a '.'.
*************************************************************************** **/

bool Game::letFound(string guess, string output, char letterToSearch) {
    for (int i = 0; i < output.length(); i++) {
        //If the current letter is a duplicate and was already found to be a
        //'.' then return true, otherwise, return false
        if (letterToSearch == guess[i] && output[i] == '.')
            return true;
    }
    return false;
}

/** ***************************************************************************
* @brief << operator                                                        
*                                                                              
* @param outs is the output stream
* @param G is the Game object                            
* @return The output stream                                              
* @details This function will insert the value of result into the desired  
*              output stream.                                                  
*************************************************************************** **/

ostream & operator << (ostream & outs, const Game & G)
{
	outs << G.result;
	return outs;
}

/** ***************************************************************************
* @brief GetWords                                                           
*                                                                              
* @param None                                                             
* @return None                                                           
* @details This function will read the words from the dictionary and       
*              store them in a vector of WordInfo objects. Each word will      
*              be assigned key values used when the vector is sorted.          
*************************************************************************** **/

void Game::GetWords ()
{
	srand (time(NULL));
	ifstream DF ("Dictionary5.txt");
	string word;
	while (DF >> word)
		list.push_back (WordInfo (word));
	DF.close ();
}

/** ***************************************************************************
* @brief InitInfo                                                           
*                                                                              
* @param None                                                             
* @return None                                                           
* @details This function will initialize the lists that correlate letters,   
*              positions, and words. info is a 5 x 26 array of integer         
*              vectors. Each vector contains a list of the indices of the      
*              words in the dictionary that contain that letter at that        
*              position.              
*************************************************************************** **/

/******************************************************************************
*              For example, if the dictionary contains:                      
*	       about brief diary globe maybe noble probe scuba today zebra     
*	         0     1     2     3     4     5     6     7     8     9       
*                                                                              
*	       info vectors for 'a'		info vectors for 'b'           
*	       info[0][0] = {0}			info[0][1] = {1}               
*	       info[1][0] = {4}			info[1][1] = {0}               
*	       info[2][0] = {2}			info[2][1] = {5, 9}            
*	       info[3][0] = {8}			info[3][1] = {3, 4, 6, 7}      
*	       info[4][0] = {7, 9}		info[4][1] = {}                
*                                                                              
******************************************************************************/

void Game::InitInfo ()
{
	for (int w = 0; w < list.size(); w++)
	{
		string word = list[w].GetWord ();
		for (int i = 0; i < 5; i++)
			info[i][word[i]-'a'].push_back (w);
	}
}

/** ***************************************************************************
* @brief ClearInfoList                                                      
*                                                                              
* @param info is a vector of indices for words to be marked as "not possible"     
* @return None                                                           
* @details This function will be called when it is determined that a       
*              specific letter is not in a specific position.                  
*************************************************************************** **/

void Game::ClearInfoList (vector <int> & info)
{
	for (int k = 0; k < info.size (); k++) 
	{
		int w = info[k];
		list[w].SetPossible (false);
		//debug << "Eliminating " << words[w].GetWord () << endl;
	}
	info.clear();
}

