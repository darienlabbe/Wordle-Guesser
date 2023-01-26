/** ***************************************************************************   
* Assignment: Project 3 - The Game of Wordle!
* @author Dr. Watts                                                               
* @date Fall 2022                                                                 
* @file WordInfo.h                                                                
*                                                                                 
* @details This file contains the description of the WordInfo class.          
*************************************************************************** **/

#ifndef WORDDATA_H
#define WORDDATA_H
#include <iostream>
using namespace std;

/** ***************************************************************************   
* @class WordInfo                                                                 
*                                                                                 
* @details This class is designed to hold attributes and provide methods      
*              for the words used for playing a game of Wordle1.                  
*************************************************************************** **/


class WordInfo
{
    public:
	WordInfo ();
	WordInfo (string S);
	bool operator < (const WordInfo & WD) const;
	string GetWord () const;
	bool GetPossible () const;
	void SetPossible (bool TF);
    private:

/**
* @var string word 
* @brief is a word read from dictionary
**/
	string word;	// Word read from dictionary
/**
* @var bool possible 
* @brief "true" indicates this word is still a possible choice
**/
	bool possible;	// True indicates this word is still a possible choice
/**
* @var int key1 
* @brief is a calculated key
**/
	int key1;	// Calculated key
/**
* @var int key2 
* @brief is a random value designed to provide variation in the game
**/
	int key2;	// Random to provide variation in the game
};

#endif
