#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <vector>
#include "TextBuddyMain.h"
#include "TextBuddyLibrary.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TBUnitTest
{		
	TEST_CLASS(UnitTest)
	{
	private:
		string testFile = "test.txt";
		TextBuddyMain tm;
		vector<string> actual;
		vector<string> expected;
		string command;

	public:
		TEST_METHOD_INITIALIZE(START) {
		}

		TEST_METHOD_CLEANUP(CLEAN) {
		}

		TEST_METHOD(addTaskTest) {
			tm = TextBuddyMain(testFile);
			actual = vector<string>();
			expected = vector<string>();

			command = "add";

			vector<string> input = { "5", "4", "3", "2", "1" };
			for (int i = 0; i < input.size(); i++) {
				tm.execCommand(testFile, actual, { command, input.at(i) });
			}
			expected = { "5", "4", "3", "2", "1" };
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(deleteTaskTest) {
			tm = TextBuddyMain(testFile);
			actual = vector<string>();
			expected = vector<string>();

			command = "delete";

			vector<string> initSet = { "5", "4", "3", "2", "1" };
			for (int i = 0; i < initSet.size(); i++) {
				tm.execCommand(testFile, actual, { "add", initSet.at(i) });
			}

			vector<string> input = { "3", "3" };
			for (int i = 0; i < input.size(); i++) {
				tm.execCommand(testFile, actual, { command, input.at(i) });
			}
			expected = { "5", "4", "1" };

			expected = {};
		}
	};
}

// TEMPLATE:
// tm.execCommand(testFile, actual, { command, input.at(i) });