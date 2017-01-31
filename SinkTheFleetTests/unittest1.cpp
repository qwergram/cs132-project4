#include "stdafx.h"
// #include "CppUnitTest.h"
#include "..\SinkTheFleet\SinkTheFleet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SinkTheFleetTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(sanityCheck) {
			Assert::AreEqual(1, 1);
			Assert::AreNotEqual(true, false);
		}

		TEST_METHOD(indexOfTest) {
			const char testArray[] = { 'a', 'b' };
			Assert::AreEqual(0, indexOf(testArray, 'a'));
			Assert::AreEqual(1, indexOf(testArray, 'b'));
			//Assert::AreEqual(-1, indexOf(testArray, 'c'));
		}
		
		TEST_METHOD(isValidPlayer) {
			Player testPlayer = initPlayer(0);
			
		}

		TEST_METHOD(isValidCoordinateTest) {
			BOARD_ROWS = BOARD_ROWS_LARGE;
			BOARD_COLS = BOARD_COLS_LARGE;
			Coord testcoord;
			testcoord.x = 0;
			testcoord.y = 0;
			Player testPlayer;
			Assert::AreEqual(true, isValidCoordinate(testcoord, HORIZONTAL_SHIP, 0, testPlayer, true));
		}

	};
}