/*******************************************************************************
* Assignment: Project 1 - The Game of Wordle with Single Letters Only!         *
* Author: Dr. Watts                                                            *
* Date: Fall 2022                                                              *
* File: execute.cpp                                                            *
*                                                                              *
* Description: This file contains the implementation of the execute function.  *
*******************************************************************************/

#include <cstdio>
#include <string>

std::string execute (const std::string & cmd)
{
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
	return "ERROR";
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    pclose(pipe);
    return result;
}
