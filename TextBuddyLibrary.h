#pragma once

#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

using namespace std;

class TextBuddyLibrary
{
public:
	TextBuddyLibrary();
	~TextBuddyLibrary();

	// write the lines to file
	static void writeFile(string fileName, vector<string> lines);

	// store the actual command and the argument at commnadVector
	// by extracting them from the given command line
	static void readCommand(vector<string> &commandVector, string commandLine);

	// read file
	static vector<string> readFile(string fileName);

	// convert string to lower case
	static void tolowercase(string &str);

	// returns ifstream of the file with the specified name
	// if the file does not exist, create.
	static ifstream makeSureFileExist(string fileName);
};
