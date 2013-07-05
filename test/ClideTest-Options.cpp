//!
//! @file 		ClideTest-Options.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for Clide command options.
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(OptionTests)
	{
		using namespace Clide;

		static Cmd *_cmd = NULL;

		bool Callback2(Cmd *cmd)
		{
			_cmd = cmd; 
			
			return true;
		}

		TEST(BasicOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback2, "A test command.");
			Option testOption("z", NULL, "A test option.");
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test -z";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			if(_cmd != NULL)
				CHECK_EQUAL(true, testOption.isDetected);
			else
				CHECK(false);
		}
		
		TEST(TwoPosOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback2, "A test command.");
			Option testOption1("a", NULL, "Test option 1.");
			Option testOption2("b", NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test -a -b";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			if(_cmd != NULL)
			{
				CHECK_EQUAL(true, testOption1.isDetected);
				CHECK_EQUAL(true, testOption2.isDetected);
			}
			else
				CHECK(false);
			
		}
		
		TEST(OnePosOneNegOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback2, "A test command.");
			Option testOption1("a", NULL, "Test option 1.");
			Option testOption2("b", NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create input buffer
			char rxBuff[50] = "test -a";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			if(_cmd != NULL)
			{
				CHECK_EQUAL(true, testOption1.isDetected);
				CHECK_EQUAL(false, testOption2.isDetected);
			}
			else
				CHECK(false);
			
		}
	} // SUITE(OptionTests)
} // namespace ClideTest