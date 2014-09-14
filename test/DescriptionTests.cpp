//!
//! @file 			DscriptionTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-24
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for Clide command, parameter and option descriptions.
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

	bool callbackCalled = false;

	static bool Callback(Cmd *cmd)
	{
		callbackCalled = true;
		return true;
	}

	MTEST(EmptyCmdDescriptionTest)
	{
		Rx rxController;

		// Create command with empty description
		Cmd cmdTest("test", &Callback, "");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test";

		callbackCalled = false;

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(true, callbackCalled);
	}

	MTEST(LongCmdDescriptionTest)
	{
		try
		{
			Rx rxController;

			// Create command with empty description
			Cmd cmdTest("test", &Callback, "This is a super super super super super long command description! It is very long indeed. And getting longer as we speak!");

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Create fake input buffer
			char rxBuff[50] = "test";

			callbackCalled = false;

			// Run rx controller
			rxController.Run(rxBuff);
		}
		catch(const char* msg)
		{
			// Since this is a unit test, don't print to stdout
			//std::cout << msg << endl;
		}

		CHECK_EQUAL(true, callbackCalled);
	}

	MTEST(EmptyParamDescriptionTest)
	{
		Rx rxController;

		// Create command to hold parameter
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter with an empty description
		Param cmdTestParam("");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		//Option cmdTestOption('a', NULL, "A test option.");
		//cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test param1";

		callbackCalled = false;

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(true, callbackCalled);
		CHECK_EQUAL("param1", cmdTestParam.value);
	}

	MTEST(LongParamDescriptionTest)
	{
		Rx rxController;

		// Create command to hold parameter
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter with an empty description
		Param cmdTestParam("This is a super super super super super long parameter description! It is very long indeed. And getting longer as we speak!");
		cmdTest.RegisterParam(&cmdTestParam);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test param1";

		callbackCalled = false;

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(true, callbackCalled);
		CHECK_EQUAL("param1", cmdTestParam.value);
	}

	MTEST(EmptyOptionDescriptionTest)
	{
		Rx rxController;

		// Create command to hold option
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create option with an empty description
		Option cmdTestOption('a', NULL, "");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test -a";

		callbackCalled = false;

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(true, callbackCalled);
		// Even though description is empty, option should still be recognised
		CHECK_EQUAL(true, cmdTestOption.isDetected);
	}

} // namespace MClideTest
