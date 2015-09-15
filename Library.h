#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

class Library
{
public:
	Library();
	~Library();

	static void write_file(string file_name, vector<string> lines);
	static void read_command(vector<string> &command_vector, string command_line);
	static vector<string> read_file(string file_name);
	static void tolowercase(string &str);
};

