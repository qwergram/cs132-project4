#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Assignment4\CShip.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace STFleet;
namespace SinkTheFleetUnitTests
{
	TEST_CLASS(CShipUnitTests)
	{
	public:

		TEST_METHOD(constructordefault)
		{
			CShip* ShipDefault = new CShip(NOSHIP);

			delete ShipDefault;
		}

		TEST_METHOD(constructorPrint)
		{

		}
	};
}