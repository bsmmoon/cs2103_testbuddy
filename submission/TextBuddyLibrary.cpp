#include "stdafx.h"
#include "TextBuddyLibrary.h"

void TextBuddyLibrary::writeFile(string fileName, vector<string> lines) {
	ofstream file;
	file.open(fileName);
	for (int i = 0; i < lines.size(); i++) {
		file << lines[i] << "\n";
	}
	file.close();
}

void TextBuddyLibrary::readCommand(vector<string> &commandVector, string commandLine) {
	vector<string> out;

	int pos = commandLine.find(" ");
	string command = commandLine.substr(0, pos);
	out.push_back(command);

	if (pos > 0) {
		string argument = commandLine.substr(pos + 1, commandLine.length());
		out.push_back(argument);
	}

	commandVector = out;
}

ifstream TextBuddyLibrary::makeSureFileExist(string fileName) {
	ifstream file;
	file.open(fileName);
	if (!file.good()) {
		ofstream temp(fileName);
		temp.close();
		file.open(fileName);
	}
	return file;
}

vector<string> TextBuddyLibrary::readFile(string fileName) {
	cout << "reading " << fileName << "\n";
	string line;
	
	vector<string> lines;
	ifstream file = makeSureFileExist(fileName);
	while (!file.eof()) {
		getline(file, line);
		if (line.length() > 0) {
			lines.push_back(line);
		}
	}

	file.close();
	return lines;
}

void TextBuddyLibrary::tolowercase(string &str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}