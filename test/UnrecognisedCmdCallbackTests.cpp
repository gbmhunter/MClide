//!
//! @file 			UnrecognisedCmdCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/13
//! @last-modified 	2014/01/13
//! @brief			Unit test for checking that the unrecognised command callback function is actually called when a command is not recognised.
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/Clide-IncludeJustMe.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(UnrecognisedCmdCallbackTests)
	{
		using namespace Clide;

		bool unrecogCmdCallbackCalled = false;
		bool cmdsEqual = false;

		void UnrecognisedCmdCallback(char* cmd)
		{
			unrecogCmdCallbackCalled = true;
			if(strcmp(cmd, "blah blah blah") == 0)
				cmdsEqual = true;
		}

		TEST(UnrecognisedCmdCallbackTest)
		{
			Rx rxController;

			// Register callback function
			rxController.cmdUnrecognisedCallback = &UnrecognisedCmdCallback;

			// Create fake input buffer
			char rxBuff[50] = "blah blah blah";
			
			// Run rx controller
			rxController.Run(rxBuff);

			// Now make sure the callback was called
			CHECK_EQUAL(true, unrecogCmdCallbackCalled);
			
			// Make sure the cmds were equal
			CHECK_EQUAL(true, cmdsEqual);

		}
		
	} // SUITE(NotRecognisedCmdCallbackTests)
} // namespace ClideTest
