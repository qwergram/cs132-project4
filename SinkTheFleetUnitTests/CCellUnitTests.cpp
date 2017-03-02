#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Assignment4\CCell.h"
// #define private public IS NOT required for these tests

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SinkTheFleetUnitTests
{		
	TEST_CLASS(CCellUnitTests)
	{
	public:
		
		// Test Construct assigns Row and Col correctly
		TEST_METHOD(TestCCellConstructor)
		{
			STFleet::CCell * temp = new STFleet::CCell(5, 2);
			Assert::AreEqual((unsigned short)5, temp->getRow());
			Assert::AreEqual((unsigned short)2, temp->getCol());
			delete temp;
		}

	};
}