/** ***************************************************************************   
* Assignment: Project 3 - The Game of Wordle!
* @author Dr. Watts                                                               
* @date Fall 2022                                                                 
* @file WordInfo.cpp                                                              
*                                                                                 
* @details This file contains the implementation of the WordInfo class.       
*************************************************************************** **/

#include "WordInfo.h"
using namespace std;

// Values associated with letters when calculating key1 value
//                     abcdefghijklmnopqrstuvwxyz
//const string values = "55555555555555555555555555"; 	// all the same
//                       abcdefghijklmnopqrstuvwxyz
const string values = "94669345824757851897633252"; 	// based on counts

/** ***************************************************************************   
* @brief WordInfo Default Constructor                                          
*                                                                                 
* @param None                                                                
* @return None                                                              
* @details This function will initialize a WordInfo object.                   
*************************************************************************** **/

WordInfo::WordInfo ()
{	
	key1 = 0;
	key2 = rand () % 100;
	possible = true;
}

/** ***************************************************************************   
* @brief WordInfo string Constructor                                           
*                                                                                 
* @param S is a string containing the word to be stored in the object.            
* @return                                                                   
* @details This function will initialize a WordInfo object for a specific     
*              word.                                                              
*************************************************************************** **/

WordInfo::WordInfo (string S)
{	
	word = S;
	// Calculate key1 based on values associated with letters in the word.
	key1 = 0;
	for (int i = 0; i < S.length(); i++)
		key1 += values[S[i]-'a'] - '0';
	// Select a random value for second key
	key2 = rand () % 100;
	possible = true;
}

/** ***************************************************************************   
* @brief Less than Operator                                                    
*                                                                                 
* @param WD is a second WordInfo object to be compared to "this" WordInfo    
*             object.                                                             
* @return A boolean value                                                   
* @details This function will compare two WordInfo objects based on their     
*              key values. This function will be called by sort.                  
*************************************************************************** **/

bool WordInfo::operator < (const WordInfo & WD) const
{
	if (key1 == WD.key1)
		return key2 < WD.key2;
	return key1 < WD.key1;
}

/** ***************************************************************************   
* @brief GetWord                                                               
*                                                                                 
* @param None                                                                
* @return string value                                                      
* @details This function will return the word stored in the object.           
*************************************************************************** **/

string WordInfo::GetWord () const
{
	return word;
}

/** ***************************************************************************   
* @brief GetPossible                                                           
*                                                                                 
* @param None                                                                
* @return boolean value                                                     
* @details This function will return the current value of possible.           
*************************************************************************** **/

bool WordInfo::GetPossible () const
{
	return possible;
}

/** ***************************************************************************   
* @brief SetPossible                                                           
*                                                                                 
* @param TF is boolean value                                                      
* @return None                                                              
* @details This function will set the value of possible to the passed         
*              value.                                                             
*************************************************************************** **/

void WordInfo::SetPossible (bool TF)
{
	possible = TF;
}
