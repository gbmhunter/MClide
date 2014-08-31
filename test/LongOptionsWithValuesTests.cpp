//!
//! @file 			LongOptionsWithValuesTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013/07/08
//! @last-modified 	2014/01/21
//! @brief 			Contains test functions for Clide command long options with no values.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "UnitTest++/UnitTest++/UnitTest++.h"

namespace ClideTest
{
	SUITE(LongOptionsWithValuesTests)
	{
		using namespace Clide;
		
		bool Callback(Cmd* cmd)
		{
			return true;
		}
		
		TEST(OnePosLongOptionWithValueTest)
		{			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption('\0', "long1", NULL, "A test long option.", true);
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test --long=optVal";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption.isDetected);
			CHECK_EQUAL("optVal", testOption.value);
		}
		
		TEST(TwoPosLongOptionTest)
		{		
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('\0', "long1", NULL, "Test option 1.", true);
			Option testOption2('\0', "long2", NULL, "Test option 2.", true);
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test --long1=optVal1 --long2=optVal2";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL("optVal1", testOption1.value);
			CHECK_EQUAL(true, testOption2.isDetected);	
			CHECK_EQUAL("optVal2", testOption2.value);
		}
				
		TEST(OnePosOneNegOptionTest)
		{			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption1('\0', "long1", NULL, "Test option 1.", true);
			Option testOption2('\0', "long2", NULL, "Test option 2.", true);
			
			// Register options
			cmdTest.RegisterOption(&testOption1);
			cmdTest.RegisterOption(&testOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create input buffer
			char rxBuff[50] = "test --long1=optVal1";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL("optVal1", testOption1.value);
			CHECK_EQUAL(false, testOption2.isDetected);
		}
		
	} // SUITE(LongOptionsNoValuesTests)
} // namespace ClideTest
