//!
//! @file 		ClideTest-LongOptionsNoValues.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/08
//! @brief 		Contains test functions for Clide command long options with no values.
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
	SUITE(LongOptionsNoValuesTests)
	{
		using namespace Clide;
		
		bool Callback(Cmd* cmd)
		{
			return true;
		}
		
		TEST(OnePosLongOptionTest)
		{			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption("long", NULL, "A test long option.");
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test --long";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption.isDetected);
		}
		
		TEST(TwoPosLongOptionTest)
		{		
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1("long1", NULL, "Test option 1.");
			Option testOption2("long2", NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test --long1 --long2";
			
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
			Option testOption1("long1", NULL, "Test option 1.");
			Option testOption2("long2", NULL, "Test option 2.");
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create input buffer
			char rxBuff[50] = "test --long1";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL(false, testOption2.isDetected);
		}
	} // SUITE(LongOptionsNoValuesTests)
} // namespace ClideTest