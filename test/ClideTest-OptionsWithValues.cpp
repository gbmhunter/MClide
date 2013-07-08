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
	SUITE(OptionsWithValuesTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{	
			return true;
		}

		
		TEST(OnePosOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption('a', NULL, NULL, "A test option.", true);
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test -a optVal";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			//CHECK_EQUAL(true, testOption.isDetected);
			//CHECK_EQUAL("opyVal", testOption.value);
		}
		
		
		TEST(TwoPosOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('a', NULL, "Test option 1.");
			Option testOption2('b', NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test -a -b";
			
			// Run rx controller
			rxController.Run(rxBuff);

			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL(true, testOption2.isDetected);

			
		}
		
		TEST(OnePosOneNegOptionTest)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('a', NULL, "Test option 1.");
			Option testOption2('b', NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create input buffer
			char rxBuff[50] = "test -a";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL(false, testOption2.isDetected);
			
		}
		
	} // SUITE(OptionTests)
} // namespace ClideTest