#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>
#include <fstream>
#include "TextBuddyMain.h"
#include "TextBuddyLibrary.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TBUnitTest
{
	TEST_CLASS(UnitTest) {
private:
	string testFile = "test.txt";

public:
	void execUnitTest(vector<vector<string>> input) {
		TextBuddyMain tm(testFile);
		vector<string> initial = input.at(0);
		string command = input.at(1).at(0);
		vector<string> arguments = input.at(2);
		vector<string> expected = input.at(3);

		vector<string> actual;
		for (int i = 0; i < arguments.size(); i++) {
			actual = tm.execCommand(testFile, initial, { command, arguments.at(i) });
		}

		if (actual == expected) {
			Assert::IsTrue(true);
		} else {
			ofstream file("UnitTestLog.txt", std::ios_base::app);
			
			file << "----------\n";
			for (int i = 0; i < initial.size(); i++) {
				file << initial.at(i) << " ";
			}
			file << "\n";

			file << command;
			file << "\n";

			for (int i = 0; i < arguments.size(); i++) {
				file << arguments.at(i) << " ";
			}
			file << "\n";

			for (int i = 0; i < actual.size(); i++) {
				file << actual.at(i) << " ";
			}
			file << "\n";

			for (int i = 0; i < expected.size(); i++) {
				file << expected.at(i) << " ";
			}
			file << "\n";

			file << "----------\n";
			file.close();

			Assert::IsTrue(false);
		}
	}

	TEST_METHOD_INITIALIZE(START) {
	}

	TEST_METHOD_CLEANUP(CLEAN) {
	}

	TEST_METHOD(addTaskTest) {
		execUnitTest({ {}, { "add" }, { "5", "4", "3", "2", "1" }, { "5", "4", "3", "2", "1" } });
		execUnitTest({ { "5", "4", "3", "2", "1" }, { "add" }, { "10", "9", "8", "7", "6" }, { "5", "4", "3", "2", "1", "10", "9", "8", "7", "6" } });
	}

	TEST_METHOD(deleteTaskTest) {
		execUnitTest({ { "5", "4", "3", "2", "1" }, { "delete" }, { "3", "3" }, { "5", "4", "1" } });
	}

	TEST_METHOD(clearTaskTest) {
		execUnitTest({ { "5", "4", "3", "2", "1" }, { "clear" }, { "5", "4", "3", "2", "1" }, {} });
	}

	TEST_METHOD(searchListTest) {
		execUnitTest({ { "nice", "nicer", "nasa", "nicest", "nike" }, { "search" }, { "nice" }, { "nice", "nicer", "NULL", "nicest", "NULL" } });
		execUnitTest({ { "nice", "nicer", "nasa", "nicest", "nike" }, { "search" }, { "n" }, { "nice", "nicer", "nasa", "nicest", "nike" } });
		execUnitTest({ { "nice", "nicer", "nasa", "nicest", "nike" }, { "search" }, { "" }, { "nice", "nicer", "nasa", "nicest", "nike" } });
	}
	};
}

// TEMPLATE:
// tm.execCommand(testFile, actual, { command, argument.at(i) });