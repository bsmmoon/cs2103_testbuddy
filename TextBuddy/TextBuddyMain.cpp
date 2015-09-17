#include "stdafx.h"
#include "TextBuddyMain.h"

TextBuddyMain::TextBuddyMain(string fileName) {
	printWelcomeMessage(fileName);
}
TextBuddyMain::~TextBuddyMain() {}

void TextBuddyMain::printLine(string str) {
	cout << str << "\n";
}

void TextBuddyMain::printWelcomeMessage(string fileName) {
	printLine("\nWelcome to TextBuddy. " + fileName + " is ready for use");
}

vector<string> TextBuddyMain::addTask(string fileName, vector<string> taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		printLine("'add' command requires argument");
		return taskList;
	}
	printLine("added to " + fileName + ": \"" + argument + "\"");
	taskList.push_back(argument);

	return taskList;
}

void TextBuddyMain::displayList(vector<string> taskList) {
	printLine("Task List: ");
	for (int i = 0; i < taskList.size(); i++) {
		if (taskList.at(i) != "NULL") {
			printLine(to_string(i + 1) + ": " + taskList.at(i));
		}
	}
}

vector<string> TextBuddyMain::deleteTask(string fileName, vector<string> taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		printLine("'delete' command requires argument");
		return taskList;
	}
	int target;
	try {
		target = stoi(argument) - 1;
	} catch (invalid_argument e) {
		printLine("Invalid argument \"" + argument + "\"");
		return taskList;
	}

	if (target < taskList.size()) {
		printLine("Deleted from " + fileName + ": \"" + taskList[target] + "\"");
		for (int i = target; i < taskList.size() - 1; i++) {
			taskList[i] = taskList[i + 1];
		}
		taskList.erase(taskList.begin() + taskList.size() - 1);
	} else {
		printLine("No task with index " + argument);
	}
	return taskList;
}

vector<string> TextBuddyMain::clearList(string fileName, vector<string> taskList) {
	taskList.clear();
	printLine("All content deleted from " + fileName);
	return taskList;
}

vector<string> TextBuddyMain::sortList(string fileName, vector<string> taskList) {
	sort(taskList.begin(), taskList.end());
	printLine("List sorted alphabetically.");
	displayList(taskList);
	return taskList;
}

vector<string> TextBuddyMain::searchList(string fileName, vector<string> taskList, string argument) {
	vector<string> foundList;
	string element;
	for (int i = 0; i < taskList.size(); i++) {
		element = taskList.at(i);
		if (element.find(argument) != -1) {
			foundList.push_back(element);
		}
		else {
			foundList.push_back("NULL");
		}
	}
	for (int i = 0; i < foundList.size(); i++) {
		cout << foundList.at(i) << " ";
	}
	cout << "\n";
	return foundList;
}

vector<string> TextBuddyMain::execCommand(string fileName, vector<string> &taskList, vector<string> commandVector) {
	string command = commandVector[0];
	string argument;
	if (commandVector.size() > 1) {
		argument = commandVector[1];
	} else {
		argument = "NULL";
	}
	TextBuddyLibrary::tolowercase(command);

	vector<string> outputList = taskList;
	if (command.compare("add") == 0) {
		outputList = addTask(fileName, taskList, argument);
	} else if (command.compare("display") == 0) {
		displayList(taskList);
	} else if (command.compare("delete") == 0) {
		outputList = deleteTask(fileName, taskList, argument);
	} else if (command.compare("clear") == 0) {
		outputList = clearList(fileName, taskList);
	} else if (command.compare("exit") == 0) {
		printLine("Bye!");
		exit(0);
	} else if (command.compare("sort") == 0) {
		outputList = sortList(fileName, taskList);
	} else if (command.compare("search") == 0) {
		outputList = searchList(fileName, taskList, argument);
		displayList(outputList);
	} else {
		printLine("Command \"" + command + "\" not found");
	}

	TextBuddyLibrary::writeFile(fileName, taskList);
	return outputList;
}

string test() {
	return "TEST";
}

int TextBuddyMain::run(string fileName) {
	vector<string> taskList = TextBuddyLibrary::readFile(fileName);

	string commandLine;
	vector<string> commandVector;

	while (true) {
		cout << "\nCommand: ";
		getline(cin, commandLine);
		TextBuddyLibrary::readCommand(commandVector, commandLine);
		execCommand(fileName, taskList, commandVector);
	}

	return 0;
}