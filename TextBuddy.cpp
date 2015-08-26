// TextBuddy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TextBuddyTool.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> task_list;
array<string, 5> list_of_commands = { "add", "display", "delete", "clear", "exit" };
array<string, 2> list_of_subcommands = { "on", "by" };

bool exec_command(string file_name, vector<string> command_vector) {
	string command = command_vector[0];
	string argument;
	if (command_vector.size() > 1) {
		argument = command_vector[1];
	} else {
		argument = "NULL";
	}
	TextBuddyTool::tolowercase(command);

	int index = -1;
	for (int i = 0; i < list_of_commands.size(); i++) {
		if (list_of_commands[i].compare(command) == 0) {
			index = i;
		}
	}

	switch (index) {
	case 0:   // add
	{
		if (argument.compare("NULL") == 0) {
			cout << command << " needs argument\n";
			break;
		}
		cout << "added to " << file_name << ": \"" << argument << "\"\n";
		task_list.push_back(argument);
		break;
	}
	case 1:   // display
	{
		cout << "Task List: \n";
		for (int i = 0; i < task_list.size(); i++) {
			cout << i + 1 << ": " << task_list[i] << "\n";
		}
		break;
	}
	case 2:   // delete
	{
		if (argument.compare("NULL") == 0) {
			cout << command << " needs argument\n";
			break;
		}
		int target;
		try {
			target = stoi(argument) - 1;
		}
		catch (invalid_argument e) {
			cout << "Invalid argument \"" << argument << "\"\n";
			break;
		}
		
		if (target < task_list.size()) {
			cout << "Deleted from " << file_name << ": \"" << task_list[target] << "\"\n";
			for (int i = target; i < task_list.size()-1; i++) {
				task_list[i] = task_list[i + 1];
			}
			task_list.erase(task_list.begin() + task_list.size() - 1);
		}
		else {
			cout << "No task with index " << argument << "\n";
		}
		break;
	}
	case 3:   // clear
	{
		task_list = vector<string>();
		cout << "All content deleted from " << file_name << "\n";
		break;
	}
	case 4:   // exit
	{
		cout << "Bye!\n";
		return false;
	}
	default:
	{
		cout << "Command \"" << command << "\" not found\n";
	}
	}

	TextBuddyTool::write_file(file_name, task_list);
	return true;
}

int _tmain(int argc, char* argv[])
{
	//Task a("Birthday","March 17th");

	//cout << a.get_task_name() << "\n";
	//cout << a.get_task_dday() << "\n";

	string file_name = argv[1];
	task_list = TextBuddyTool::read_file(file_name);

	string command_line;
	vector<string> command_vector;

	while (true) {
		cout << "\nCommand: ";
		getline(cin, command_line);
		TextBuddyTool::read_command(command_vector, command_line);
		if (!exec_command(file_name, command_vector)) {
			break;
		}
	}
	
	return 0;
}

