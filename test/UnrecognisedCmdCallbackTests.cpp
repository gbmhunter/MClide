//!
//! @file 			UnrecognisedCmdCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/13
//! @last-modified 	2014/01/14
//! @brief			Unit test for checking that the unrecognised command callback function is actually called when a command is not recognised.
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/IncludeJustMe.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(UnrecognisedCmdCallbackTests)
	{
		using namespace Clide;

		bool unrecogCmdCallbackCalled = false;
		bool cmdsEqual = false;

		bool CmdCallback(Cmd *cmd)
		{
			return true;
		}

		void UnrecognisedCmdCallback1(char* cmd)
		{
			unrecogCmdCallbackCalled = true;
			if(strcmp(cmd, "blah blah blah") == 0)
				cmdsEqual = true;
		}

		TEST(UnrecognisedCmdCallbackTest)
		{
			Rx rxController;

			// Register callback function
			rxController.cmdUnrecognisedCallback = &UnrecognisedCmdCallback1;

			// Create fake input buffer
			char rxBuff[50] = "blah blah blah";
			
			// Reset globals
			unrecogCmdCallbackCalled = false;
			cmdsEqual = false;

			// Run rx controller
			rxController.Run(rxBuff);

			// Now make sure the callback was called
			CHECK_EQUAL(true, unrecogCmdCallbackCalled);
			
			// Make sure the cmds were equal
			CHECK_EQUAL(true, cmdsEqual);

		}
		
		TEST(RecognisedCmdWithCallbackTest)
		{
			Rx rxController;

			// Create command
			Cmd cmdTest("test", &CmdCallback, "A test command.");

			// Create parameter
			Param cmdTestParam("A test parameter.");
			cmdTest.RegisterParam(&cmdTestParam);

			// Create option
			Option cmdTestOption('a', NULL, "A test option.");
			cmdTest.RegisterOption(&cmdTestOption);

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Register callback function
			rxController.cmdUnrecognisedCallback = &UnrecognisedCmdCallback1;

			// Create fake input buffer
			char rxBuff[50] = "test param1 -a";

			// Reset globals
			unrecogCmdCallbackCalled = false;
			cmdsEqual = false;

			// Run rx controller
			rxController.Run(rxBuff);

			// Now the command should of been recognised, and the callback function NOT called,
			// so make sure they are still false
			CHECK_EQUAL(false, unrecogCmdCallbackCalled);

		}

	} // SUITE(NotRecognisedCmdCallbackTests)
} // namespace ClideTest
