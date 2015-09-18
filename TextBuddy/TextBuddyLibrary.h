#pragma once

#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

using namespace std;

const string DEFAULT_DB_NAME = "mytextfile.txt";

class TextBuddyLibrary {
public:
	TextBuddyLibrary();
	~TextBuddyLibrary();

	static void writeFile(string fileName, vector<string> lines);

	// store the actual command and the argument at commnadVector
	static void readCommand(vector<string> &commandVector, string commandLine);

	static vector<string> readFile(string fileName);
	static void tolowercase(string &str);
	static void makeSureFileExist(string fileName);

	// returns file name
	// if no file given, returns the default name
	static string readFileName(int argc, char* argv[]);

	static void TextBuddyLibrary::printList(vector<string> list);
};
