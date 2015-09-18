#pragma once

#include "stdafx.h"
#include "TextBuddyLibrary.h"

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

using namespace std;

const string WELCOME_MESSAGE = "\nWelcome to TextBuddy. %s is ready for use";

class TextBuddyMain
{
private:
	// print the input string with line breaker
	// can be used for a specific printing behaviour later
	void printLine(string str);

	// prints welcome message and indicates which file is opened
	void printWelcomeMessage(string fileName);
	
	vector<string> addTask(string fileName, vector<string> &taskList, string argument);
	vector<string> displayList(vector<string> &taskList);
	vector<string> deleteTask(string fileName, vector<string> &taskList, string argument);
	vector<string> clearList(string fileName, vector<string> &taskList);
	vector<string> TextBuddyMain::searchList(string fileName, vector<string> &taskList, string argument);
	vector<string> TextBuddyMain::sortList(string fileName, vector<string> &taskList);
	void TextBuddyMain::exitBuddy();

public:
	int run(string fileName);

	// returns false if the command is 'exit' in order to indicate the termination
	vector<string> execCommand(string fileName, vector<string> &taskList, vector<string> commandVector);

	TextBuddyMain(string fileName);
	~TextBuddyMain();
};

