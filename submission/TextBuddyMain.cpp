#include "stdafx.h"
#include "TextBuddyMain.h"


void printLine(string str) {
	cout << str << "\n";
	logData.push_back(str);
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
	}
	else {
		fileName = DEFAULT_DB_NAME;
	}

	return fileName;
}

void printWelcomeMessage(string fileName) {
	printLine("\nWelcome to TextBuddy. " + fileName + " is ready for use");
}

bool execCommand(string fileName, vector<string> commandVector) {
	string command = commandVector[0];
	string argument;
	if (commandVector.size() > 1) {
		argument = commandVector[1];
	}
	else {
		argument = "NULL";
	}
	TextBuddyLibrary::tolowercase(command);

	int index = getCommandIndex(command);

	switch (index) {
	case 0:   // add
	{
		if (argument.compare("NULL") == 0) {
			printLine(command + " needs argument");
			break;
		}
		printLine("added to " + fileName + ": \"" + argument + "\"");
		taskList.push_back(argument);
		break;
	}
	case 1:   // display
	{
		printLine("Task List: ");
		for (int i = 0; i < taskList.size(); i++) {
			printLine(to_string(i + 1) + ": " + taskList[i]);
		}
		break;
	}
	case 2:   // delete
	{
		if (argument.compare("NULL") == 0) {
			printLine(command + " needs argument");
			break;
		}
		int target;
		try {
			target = stoi(argument) - 1;
		}
		catch (invalid_argument e) {
			printLine("Invalid argument \"" + argument + "\"");
			break;
		}

		if (target < taskList.size()) {
			printLine("Deleted from " + fileName + ": \"" + taskList[target] + "\"");
			for (int i = target; i < taskList.size() - 1; i++) {
				taskList[i] = taskList[i + 1];
			}
			taskList.erase(taskList.begin() + taskList.size() - 1);
		}
		else {
			printLine("No task with index " + argument);
		}
		break;
	}
	case 3:   // clear
	{
		taskList = vector<string>();
		printLine("All content deleted from " + fileName);
		break;
	}
	case 4:   // exit
	{
		printLine("Bye!");
		return false;
	}
	default:
	{
		printLine("Command \"" + command + "\" not found");
	}
	}

	TextBuddyLibrary::writeFile(fileName, taskList);
	if (LOG_MODE) {
		TextBuddyLibrary::writeFile(LOG_FILE_NAME, logData);
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (LOG_MODE) {
		TextBuddyLibrary::makeSureFileExist(LOG_FILE_NAME);
	}

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