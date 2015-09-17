#include "stdafx.h"
#include "TextBuddyMain.h"

TextBuddyMain::TextBuddyMain() {}
TextBuddyMain::~TextBuddyMain() {}

void printLine(string str) {
	cout << str << "\n";
}

string readFileName(int argc, char* argv[]) {
	string fileName;

	if (argc > 1) {
		for (int i = 0; i < argc; i++) {
			cout << argv[i] << "\n";
		}
		fileName = argv[1];
	} else {
		fileName = DEFAULT_DB_NAME;
	}

	return fileName;
}

void printWelcomeMessage(string fileName) {
	printLine("\nWelcome to TextBuddy. " + fileName + " is ready for use");
}

vector<string> addTask(string fileName, vector<string> taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		printLine("'add' command requires argument");
		return taskList;
	}
	printLine("added to " + fileName + ": \"" + argument + "\"");
	taskList.push_back(argument);

	return taskList;
}

void displayList(vector<string> taskList) {
	printLine("Task List: ");
	for (int i = 0; i < taskList.size(); i++) {
		printLine(to_string(i + 1) + ": " + taskList[i]);
	}
}

vector<string> deleteTask(string fileName, vector<string> taskList, string argument) {
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

vector<string> clearList(string fileName, vector<string> taskList) {
	taskList.erase(taskList.begin(), taskList.begin() + taskList.size());
	printLine("All content deleted from " + fileName);
	return taskList;
}

vector<string> sortList(string fileName, vector<string> taskList) {
	sort(taskList.begin(), taskList.end());
	return taskList;
}

void searchList(string fileName, vector<string> taskList, string argument) {
	vector<string> foundList;
	string element;
	for (int i = 0; i < taskList.size(); i++) {
		element = taskList.at(i);
		if (element.find(argument) != -1) {
			foundList.push_back(element);
		}
	}
	displayList(foundList);
}

bool execCommand(string fileName, vector<string> &taskList, vector<string> commandVector) {
	string command = commandVector[0];
	string argument;
	if (commandVector.size() > 1) {
		argument = commandVector[1];
	} else {
		argument = "NULL";
	}
	TextBuddyLibrary::tolowercase(command);

	if (command.compare("add") == 0) {
		taskList = addTask(fileName, taskList, argument);
	} else if (command.compare("display") == 0) {
		displayList(taskList);
	} else if (command.compare("delete") == 0) {
		taskList = deleteTask(fileName, taskList, argument);
	} else if (command.compare("clear") == 0) {
		taskList = clearList(fileName, taskList);
	} else if (command.compare("exit") == 0) {
		printLine("Bye!");
		exit(0);
	} else if (command.compare("sort") == 0) {
		taskList = sortList(fileName, taskList);
	} else if (command.compare("search") == 0) {
		searchList(fileName, taskList, argument);
	} else {
		printLine("Command \"" + command + "\" not found");
	}

	TextBuddyLibrary::writeFile(fileName, taskList);
	return true;
}

int main(int argc, char* argv[]) {
	string fileName = readFileName(argc, argv);
	vector<string> taskList = TextBuddyLibrary::readFile(fileName);

	printWelcomeMessage(fileName);

	string commandLine;
	vector<string> commandVector;

	while (true) {
		cout << "\nCommand: ";
		getline(cin, commandLine);
		TextBuddyLibrary::readCommand(commandVector, commandLine);
		if (!execCommand(fileName, taskList, commandVector)) {
			break;
		}
	}

	return 0;
}