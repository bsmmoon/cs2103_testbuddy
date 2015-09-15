#include "stdafx.h"
#include "Library.h"

namespace Library {
	void write_file(string file_name, vector<string> lines) {
		ofstream file;
		file.open(file_name);
		for (int i = 0; i < lines.size(); i++) {
			file << lines[i] << "\n";
		}
		file.close();
	}

	void read_command(vector<string> &command_vector, string command_line) {
		vector<string> out;

		int pos = command_line.find(" ");
		string command = command_line.substr(0, pos);
		out.push_back(command);

		if (pos > 0) {
			string argument = command_line.substr(pos + 1, command_line.length());
			out.push_back(argument);
		}

		command_vector = out;
	}

	vector<string> read_file(string file_name) {
		cout << "reading " << file_name << "\n";
		ifstream file;
		file.open(file_name);
		string line;

		vector<string> lines;
		if (!file.good()) {
			cout << "No file called " << file_name << " exists\n";
			ofstream temp(file_name);
			temp.close();
			cout << file_name << " created\n";
		}
		else {
			while (!file.eof()) {
				getline(file, line);
				if (line.length() > 0) {
					lines.push_back(line);
				}
			}
		}

		file.close();
		return lines;
	}

	void tolowercase(string &str) {
		transform(str.begin(), str.end(), str.begin(), ::tolower);
	}
}