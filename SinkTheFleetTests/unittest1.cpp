#include "stdafx.h"
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
		}
		
		TEST_METHOD(isValidCoordinateTest) {
			BOARD_ROWS = BOARD_ROWS_LARGE;
			BOARD_COLS = BOARD_COLS_LARGE;
			Player testPlayer;
			testPlayer.gameGrid = allocMemory();
			
			Coord testcoord;
			
			for (int xsample = 0; xsample < BOARD_COLS; xsample++) {
				for (int ysample = 0; ysample < BOARD_ROWS; ysample++) {
					testcoord.x = xsample;
					testcoord.y = ysample;
					Assert::IsTrue(isValidCoordinate(testcoord, HORIZONTAL_SHIP, 0, testPlayer, true));
				}
			}
			
		}

		TEST_METHOD(isInvalidCoordinateTest) {
			BOARD_ROWS = BOARD_ROWS_LARGE;
			BOARD_COLS = BOARD_COLS_LARGE;
			Player testPlayer;
			testPlayer.gameGrid = allocMemory();

			Coord testcoord;
			long samples[] = { -1, 36, 9999999, 88888888888, -235, BOARD_COLS };

			for (int xsample = 0; xsample < 10; xsample++) {
				for (int ysample = 0; ysample < 10; ysample++) {
					testcoord.x = samples[xsample];
					testcoord.y = samples[ysample];
					Assert::IsFalse(isValidCoordinate(testcoord, HORIZONTAL_SHIP, 0, testPlayer, true));
				}
			}

		}

		TEST_METHOD(isInvalidCoordinateStackingShipsTest) {
			BOARD_ROWS = BOARD_ROWS_LARGE;
			BOARD_COLS = BOARD_COLS_LARGE;
			Player testPlayer;
			testPlayer.gameGrid = allocMemory();

			testPlayer.gameGrid[0][0] = MINESWEEPER;
			testPlayer.gameGrid[0][1] = MINESWEEPER;
			Coord testcoord;
			testcoord.x = 0;
			testcoord.y = 0;

			Assert::IsFalse(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, false));

			testcoord.y = 1;
			Assert::IsTrue(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, false));

			testcoord.x = 1;
			Assert::IsTrue(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, false));

			testcoord.y = 0;
			Assert::IsFalse(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, false));

		}

		TEST_METHOD(isInvalidCoordinateOffgridShipsTest) {
			BOARD_ROWS = BOARD_ROWS_LARGE;
			BOARD_COLS = BOARD_COLS_LARGE;
			Player testPlayer;
			testPlayer.gameGrid = allocMemory();

			testPlayer.gameGrid[0][0] = MINESWEEPER;
			testPlayer.gameGrid[0][1] = MINESWEEPER;
			Coord testcoord;
			testcoord.x = BOARD_COLS;
			testcoord.y = BOARD_ROWS;

			Assert::IsFalse(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, true));

			testcoord.x -= 2;
			testcoord.y--;
			Assert::IsTrue(isValidCoordinate(testcoord, HORIZONTAL_SHIP, MINESWEEPER, testPlayer, true));
		}



	};
}