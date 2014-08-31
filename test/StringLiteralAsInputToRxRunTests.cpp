//!
//! @file 			StringLiteralAsInputToRxRunTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014/01/21
//! @last-modified 	2014/01/21
//! @brief 			Contains test functions for directly inputting a string literal to Rx::Run().
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "unittest-cpp/UnitTest++/UnitTest++.h"

namespace ClideTest
{
	SUITE(StringLiteralAsInputToRxRunTests)
	{
		using namespace Clide;

		TEST(StringLiteralAsInputToRxRunTest)
		{
			Rx rxController;

			// Create command, make the callback NULL
			Cmd cmdTest("test", NULL, "A test command.");

			// Create parameter
			Param cmdTestParam("A test parameter.");
			cmdTest.RegisterParam(&cmdTestParam);

			// Create option
			Option cmdTestOption('a', NULL, "A test option.");
			cmdTest.RegisterOption(&cmdTestOption);

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Run rx controller, passing in a string literal rather than a char* pointer to a modifiable buffer
			rxController.Run("test param1 -a");

			// Check that the command was processed successfully
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
	} // SUITE(StringLiteralAsInputToRxRunTests)
} // namespace ClideTest
