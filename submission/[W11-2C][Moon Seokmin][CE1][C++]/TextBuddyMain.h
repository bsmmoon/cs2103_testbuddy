#pragma once

#include "stdafx.h"
#include "TextBuddyLibrary.h"

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

using namespace std;

vector<string> taskList;
array<string, 5> LIST_OF_COMMANDS = { "add", "display", "delete", "clear", "exit" };
array<string, 2> LIST_OF_SUB_COMMANDS = { "on", "by" };
string DEFAULT_DB_NAME = "defaultDB.txt";

class TextBuddyMain
{
private:
	// prints welcome message and indicates which file is opened
	void printWelcomeMessage(string fileName);

	// returns file name
	// if the file name is provided, returns it.
	// otherwise, returns the default name
	string readFileName(int argc, char* argv[]);

	// returns false if the command is 'exit' in order to indicate the termination
	bool execCommand(string file_name, vector<string> commandVector);

	// returns the indicative integer of the command
	// *This function is made because c++ switch only accepts integer
	int getCommandIndex(string command);

	// print the input string
	void printLine(string str);
public:
	int main(int argc, char* argv[]);
	
	TextBuddyMain();
	~TextBuddyMain();
};

