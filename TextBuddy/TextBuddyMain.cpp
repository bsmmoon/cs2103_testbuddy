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

vector<string> TextBuddyMain::addTask(string fileName, vector<string> &taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		throw invalid_argument("'add' command requires argument");
	}

	printLine("added to " + fileName + ": \"" + argument + "\"");
	taskList.push_back(argument);

	return taskList;
}

vector<string> TextBuddyMain::deleteTask(string fileName, vector<string> &taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		throw invalid_argument("'delete' command requires argument");
	}

	int target;
	try {
		target = stoi(argument) - 1;
	} catch (invalid_argument e) {
		throw invalid_argument("Invalid argument \"" + argument + "\"");
	}

	if (target < taskList.size()) {
		printLine("Deleted from " + fileName + ": \"" + taskList[target] + "\"");
		for (int i = target; i < taskList.size() - 1; i++) {
			taskList[i] = taskList[i + 1];
		}
		taskList.erase(taskList.begin() + taskList.size() - 1);
	} else {
		throw invalid_argument("No task with index " + argument);
	}

	return taskList;
}

vector<string> TextBuddyMain::clearList(string fileName, vector<string> &taskList) {
	taskList.clear();
	printLine("All content deleted from " + fileName);

	return taskList;
}

vector<string> TextBuddyMain::sortList(string fileName, vector<string> &taskList) {
	sort(taskList.begin(), taskList.end());
	printLine("List sorted alphabetically.");
	
	return taskList;
}

vector<string> TextBuddyMain::searchList(string fileName, vector<string> &taskList, string argument) {
	if (argument.compare("NULL") == 0) {
		throw invalid_argument("'search' command requires argument");
	}

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

	return foundList;
}

void TextBuddyMain::exitBuddy() {
	printLine("Bye!");
	exit(0);
}

vector<string> TextBuddyMain::execCommand(string fileName, vector<string> &taskList, vector<string> commandVector) {
	string command = commandVector[0];
	string argument = commandVector.at(1);

	TextBuddyLibrary::tolowercase(command);

	vector<string> outputList = taskList;
	bool returnsMessage = false;

	try {
		if (command.compare("add") == 0) {
			outputList = addTask(fileName, taskList, argument);
		} else if (command.compare("display") == 0) {
			printLine("Task List: ");
			outputList = taskList;
			TextBuddyLibrary::printList(outputList);
		} else if (command.compare("delete") == 0) {
			outputList = deleteTask(fileName, taskList, argument);
		} else if (command.compare("clear") == 0) {
			outputList = clearList(fileName, taskList);
		} else if (command.compare("exit") == 0) {
			exitBuddy();
		} else if (command.compare("sort") == 0) {
			outputList = sortList(fileName, taskList);
		} else if (command.compare("search") == 0) {
			outputList = searchList(fileName, taskList, argument);
			TextBuddyLibrary::printList(outputList);
		} else {
			string message = "Command \"" + command + "\" not found";
			throw invalid_argument(message);
		}
	} catch (invalid_argument message) {
		throw invalid_argument(message);
	} catch (exception e) {
		throw invalid_argument("Unhandled Exception");
	}

	TextBuddyLibrary::writeFile(fileName, taskList);

	return outputList;
}

int TextBuddyMain::run(string fileName) {
	vector<string> taskList = TextBuddyLibrary::readFile(fileName);

	string commandLine;
	vector<string> commandVector;

	while (true) {
		cout << "Command: ";
		getline(cin, commandLine);
		TextBuddyLibrary::readCommand(commandVector, commandLine);
		try {
			execCommand(fileName, taskList, commandVector);
		} catch (invalid_argument message) {
			printLine(string(message.what()));
		}
	}

	return 0;
}