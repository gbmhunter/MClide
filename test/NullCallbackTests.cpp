//!
//! @file 			NullCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/21
//! @last-modified 	2014/01/21
//! @brief 			Contains test functions for if the command callback function is NULL.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(NullCallbackTests)
	{
		using namespace Clide;

		TEST(NullCmdCallbackTest)
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

			// Create some input start the RX processing
			// If program makes it past this point, then
			// the NULL function pointer was handled correctly
			// Create fake input buffer
			char rxBuff[50] = "test param1 -a";

			// Run rx controller
			rxController.Run(rxBuff);

			// Check that the command was processed successfully
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
	} // SUITE(NullCallbackTests)
} // namespace ClideTest
