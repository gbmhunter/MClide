//!
//! @file 			UnrecognisedCmdCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-13
//! @last-modified 	2014-03-26
//! @brief			Unit test for checking that the unrecognised command callback function is actually called when a command is not recognised.
//! @details
//!				See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

namespace MClideTest
{
	class ClassWithFunction
	{
	public:
		bool iWasCalled;
		bool cmdsEqual;

		ClassWithFunction()
		{
			iWasCalled = false;
			cmdsEqual = false;
		}


		void TryAndCallMe(char* cmd)
		{
			iWasCalled = true;

			if(strcmp(cmd, "blah") == 0)
				cmdsEqual = true;
		}

	};


	using namespace Clide;

	bool CmdCallback(Cmd *cmd)
	{
		return true;
	}

	MTEST(UnrecognisedCmdCallbackTest)
	{
		Rx rxController;

		ClassWithFunction classWithFunction;

		MCallbacks::CallbackGen<ClassWithFunction, void, char*> callBack(&classWithFunction, &ClassWithFunction::TryAndCallMe);

		// Register callback function
		rxController.cmdUnrecogCallback = callBack;

		// Create fake input buffer
		char rxBuff[50] = "blah blah blah";

		// Run rx controller
		rxController.Run(rxBuff);

		// Now make sure the callback was called
		CHECK_EQUAL(classWithFunction.iWasCalled, true);

		// Make sure the cmds were equal
		CHECK_EQUAL(classWithFunction.cmdsEqual, true);

	}

	MTEST(RecognisedCmdWithCallbackTest)
	{
		Rx rxController;

		ClassWithFunction classWithFunction;

		MCallbacks::CallbackGen<ClassWithFunction, void, char*> callBack(&classWithFunction, &ClassWithFunction::TryAndCallMe);

		// Register callback function
		rxController.cmdUnrecogCallback = callBack;

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

		// Create fake input buffer
		char rxBuff[50] = "test param1 -a";

		// Run rx controller
		rxController.Run(rxBuff);

		// Now the command should of been recognised, and the callback function NOT called,
		// so make sure they are still false
		CHECK_EQUAL(classWithFunction.iWasCalled, false);

	}

} // namespace MClideTest
