//!
//! @file 			NullCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-21
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for if the command callback function is NULL.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

namespace MClideTest
{

	using namespace Clide;

	MTEST(NullCmdCallbackTest)
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
		
} // namespace MClideTest
