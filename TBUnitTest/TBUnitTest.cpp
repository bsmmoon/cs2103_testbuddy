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
	public:
		TEST_METHOD(addTaskTest)
		{
			string testFile = "test.txt";
			TextBuddyMain tm(testFile);
			vector<string> actual;
			vector<string> expected;

			tm.execCommand(testFile, actual, { "add", "one" });
			expected = { "one" };
			if (actual == expected) {
				Assert::IsTrue(true);
			} else {
				Assert::IsFalse(true);
			}
		}
	};
}