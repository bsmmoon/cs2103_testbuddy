#include "stdafx.h"
#include "TextBuddyMain.h"


void printLine(string str) {
	cout << str << "\n";
}

int getCommandIndex(string command) {
	int index = -1;
	for (int i = 0; i < LIST_OF_COMMANDS.size(); i++) {
		if (LIST_OF_COMMANDS[i].compare(command) == 0) {
			index = i;
			break;
		}
	}
	return index;
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

void addTask(string command, string argument, string fileName) {
	if (argument.compare("NULL") == 0) {
		printLine(command + " needs argument");
		return;
	}
	printLine("added to " + fileName + ": \"" + argument + "\"");
	taskList.push_back(argument);
}

void displayList() {
	printLine("Task List: ");
	for (int i = 0; i < taskList.size(); i++) {
		printLine(to_string(i + 1) + ": " + taskList[i]);
	}
}

void deleteTask(string command, string argument, string fileName) {
	if (argument.compare("NULL") == 0) {
		printLine(command + " needs argument");
		return;
	}
	int target;
	try {
		target = stoi(argument) - 1;
	} catch (invalid_argument e) {
		printLine("Invalid argument \"" + argument + "\"");
		return;
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
}

void clearList(string fileName) {
	taskList.erase(taskList.begin(), taskList.begin() + taskList.size());
	printLine("All content deleted from " + fileName);
}

bool execCommand(string fileName, vector<string> commandVector) {
	string command = commandVector[0];
	string argument;
	if (commandVector.size() > 1) {
		argument = commandVector[1];
	} else {
		argument = "NULL";
	}
	TextBuddyLibrary::tolowercase(command);

	if (command.compare("add") == 0) {
		addTask(command, argument, fileName);
	} else if (command.compare("display") == 0) {
		displayList();
	} else if (command.compare("delete") == 0) {
		deleteTask(command, argument, fileName);
	} else if (command.compare("clear") == 0) {
		clearList(fileName);
	} else if (command.compare("exit") == 0) {
		printLine("Bye!");
		return false;
	} else {
		printLine("Command \"" + command + "\" not found");
	}

	TextBuddyLibrary::writeFile(fileName, taskList);
	return true;
}

int main(int argc, char* argv[]) {
	string fileName = readFileName(argc, argv);
	taskList = TextBuddyLibrary::readFile(fileName);

	printWelcomeMessage(fileName);

	string commandLine;
	vector<string> commandVector;

	while (true) {
		cout << "\nCommand: ";
		getline(cin, commandLine);
		TextBuddyLibrary::readCommand(commandVector, commandLine);
		if (!execCommand(fileName, commandVector)) {
			break;
		}
	}

	return 0;
}