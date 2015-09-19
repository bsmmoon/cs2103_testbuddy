#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>
#include <fstream>
#include "TextBuddyMain.h"
#include "TextBuddyLibrary.h"

#include <algorithm>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TBUnitTest {
	TEST_CLASS(UnitTest) {
private:
	string testFile = "test.txt";

public:
	void writeVectorToFile(ofstream &file, vector<string> list) {
		for (int i = 0; i < (int) list.size(); i++) {
			file << list.at(i) << " ";
		}
		file << "\n";
	}

	string implode(vector<string> vec) {
		string str = "{ ";
		for (int i = 0; i < (int) vec.size(); i++) {
			str += vec.at(i) + ", ";
		}
		str += " }";
		return str;
	}

	void execUnitTest(vector<string> initial, string command, vector<string> arguments, vector<string> expected) {
		TextBuddyMain tm(testFile);

		vector<string> actual;
		try {
			if (arguments.size() == 0) {
				actual = tm.execCommand(testFile, initial, { command, "NULL" });
			} else {
				for (int i = 0; i < (int) arguments.size(); i++) {
					actual = tm.execCommand(testFile, initial, { command, arguments.at(i) });
				}
			}
		} catch (invalid_argument message) {
			actual = { message.what() };
		}

		string expectedStr = implode(expected);
		string actualStr = implode(actual);

		Assert::AreEqual(expectedStr, actualStr);
	}

	TEST_METHOD_INITIALIZE(START) {
	}

	TEST_METHOD_CLEANUP(CLEAN) {
	}

	TEST_METHOD(addTaskTest) {
		execUnitTest( {}, "add", {}, { "'add' command requires argument" } );
		execUnitTest( {}, "add", { "5", "4", "3", "2", "1" }, { "5", "4", "3", "2", "1" } );
		execUnitTest( { "5", "4", "3", "2", "1" }, "add", { "10", "9", "8", "7", "6" }, { "5", "4", "3", "2", "1", "10", "9", "8", "7", "6" } );
	}

	TEST_METHOD(deleteTaskTest) {
		execUnitTest( { "1" }, "delete", {}, { "'delete' command requires argument" } );
		execUnitTest( { "1" }, "delete", { "17" }, { "No task with index 17" } );
		execUnitTest( { "5", "4", "3", "2", "1" }, "delete", { "3", "3" }, { "5", "4", "1" } );
	}

	TEST_METHOD(clearTaskTest) {
		execUnitTest( { "5", "4", "3", "2", "1" }, { "clear" }, {}, {} );
	}

	TEST_METHOD(searchListTest) {
		execUnitTest( { "nice", "nicer", "nasa", "nicest", "nike" }, "search", {}, { "'search' command requires argument" } );
		execUnitTest( { "nice", "nicer", "nasa", "nicest", "nike" }, "search", { "nice" }, { "nice", "nicer", "NULL", "nicest", "NULL" } );
		execUnitTest( { "nice", "nicer", "nasa", "nicest", "nike" }, "search", { "n" }, { "nice", "nicer", "nasa", "nicest", "nike" } );
		execUnitTest( { "nice", "nicer", "nasa", "nicest", "nike" }, "search", { "z" }, { "NULL", "NULL", "NULL", "NULL", "NULL" } );
	}

	TEST_METHOD(sortListTest) {
		execUnitTest( { "5", "4", "3", "2", "1" }, "sort", {}, { "1", "2", "3", "4", "5" } );
		execUnitTest( { "5", "4", "3", "2", "1", "9", "8", "7", "6" }, "sort", {}, { "1", "2", "3", "4", "5", "6", "7", "8", "9" } );
	}
	};
}

