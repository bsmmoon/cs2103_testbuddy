#pragma once

#include "stdafx.h"
#include "TextBuddyLibrary.h"

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

using namespace std;

array<string, 5> LIST_OF_COMMANDS = { "add", "display", "delete", "clear", "exit" };
array<string, 2> LIST_OF_SUB_COMMANDS = { "on", "by" };
string DEFAULT_DB_NAME = "mytextfile.txt";

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
	bool execCommand(string fileName, vector<string> &taskList, vector<string> commandVector);
	
	vector<string> addTask(string fileName, vector<string> taskList, string command, string argument);
	vector<string> deleteTask(string fileName, vector<string> taskList, string command, string argument);
	vector<string> clearList(string fileName, vector<string> taskList);
	void displayList(vector<string> taskList);

	// print the input string with line breaker
	// can be used for a specific printing behaviour later
	void printLine(string str);
public:
	int main(int argc, char* argv[]);
	
	TextBuddyMain();
	~TextBuddyMain();
};

