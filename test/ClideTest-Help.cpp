//!
//! @file 			ClideTest-Help.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/07
//! @last-modified 	2014/01/07
//! @brief 			Contains test functions for Clide help.
//! @details
//!					See README.rst in root dir for more info.

#include "../src/include/Clide-IncludeJustMe.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(HelpTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{
			return true;
		}

		TEST(HelpNoDefaultTest)
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
		
		TEST(HelpNoGroupsAtAllTest)
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

		TEST(HelpGroupsTest)
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
			
			//CHECK_EQUAL("param1", cmdTestParam.value);
			//CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(HelpGroupsWithSelectionTest)
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

	} // SUITE(HelpTests)
} // namespace ClideTest
