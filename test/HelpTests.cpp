//!
//! @file 			HelpTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-07
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for MClide help.
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

	static bool Callback(Cmd *cmd)
	{
		return true;
	}

	MTEST(HelpNoDefaultTest)
	{
		Rx rxController;
		Tx txController;

		CmdGroup cmdGroupUser("user", "Commands are suitable for the user.");
		CmdGroup cmdGroupDev("dev", "Commands are suitable for the developer.");

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "help";

		// Run rx controller
		rxController.Run(rxBuff);
		
	}

	MTEST(HelpNoGroupsAtAllTest)
	{
		Rx rxController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "help";

		// Run rx controller
		rxController.Run(rxBuff);

	}

	MTEST(HelpGroupsTest)
	{
		Rx rxController;
		Tx txController;

		CmdGroup cmdGroupUser("user", "Commands are suitable for the user.");
		CmdGroup cmdGroupDev("dev", "Commands are suitable for the developer.");

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Setup default command group
		rxController.defaultCmdGroup = &cmdGroupUser;

		// Create fake input buffer
		char rxBuff[50] = "help";

		// Run rx controller
		rxController.Run(rxBuff);
		
		//CHECK_EQUAL(cmdTestParam.value, "param1");
		//CHECK_EQUAL(cmdTestOption.isDetected, true);
	}

	MTEST(HelpGroupsWithSelectionTest)
	{
		Rx rxController;
		Tx txController;

		CmdGroup cmdGroupUser("user", "Commands are suitable for the user.");
		CmdGroup cmdGroupDev("dev", "Commands are suitable for the developer.");

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Setup default command group
		rxController.defaultCmdGroup = &cmdGroupUser;

		// Request for help, with specified group "user"
		char rxBuff[50] = "help -g user";

		// Run rx controller
		rxController.Run(rxBuff);

	}

} // namespace MClideTest
