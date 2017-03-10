#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Assignment4\CCell.h"
// DO NOT USE #define private public as it IS NOT required for these tests

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SinkTheFleetUnitTests
{		
	TEST_CLASS(CCellUnitTests)
	{
	public:

		// Test Constructor assigns Row and Col correctly
		TEST_METHOD(TestCCellConstructor)
		{
			STFleet::CCell * temp = new STFleet::CCell(5, 2);
			unsigned short result = temp->getRow();
			Assert::AreEqual((unsigned short)5, result);
			// Assert::AreEqual((unsigned short)2, temp->getCol());
			delete temp;
		}

		// Test Constructor throws error on invalid data
		TEST_METHOD(TestCCellConstructorInvalidInput)
		{
			//STFleet::CCell * temp = new STFleet::CCell(5, -2);
			//Assert::AreEqual((unsigned short)5, temp->getRow());
			//Assert::AreEqual((unsigned short)2, temp->getCol());
			//delete temp;
		}
	};
}