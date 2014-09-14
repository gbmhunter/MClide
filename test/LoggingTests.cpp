//!
//! @file 			LoggingTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-13
//! @last-modified 	2014-09-14
//! @brief			Unit tests for checking the logging functionality of the clide-cpp library.
//! @details
//!				See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

namespace MClideTest
{
/*
	SUITE(LoggingTests)
	{
		using namespace Clide;

		static bool Callback(Cmd *cmd)
		{
			return true;
		}


		MTEST(BasicLoggingTest)
		{
			Rx rxController;
			Tx txController;
			
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
			char rxBuff[50] = "blah blah blah";
			
			// Run rx controller
			CHECK_EQUAL(false, rxController.Run(rxBuff));

			// Now make sure this was logged
			CHECK_EQUAL((int)Rx::LogIds::CMD_NOT_RECOGNISED, (int)rxController.log.logId);
			
		}*/
		/*
		MTEST(OneOptionThenOneParamRxTest)
		{
			Rx rxController;
			Tx txController;
			
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
			char rxBuff[50] = "test -a param1";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		MTEST(TwoParamTwoOptionRxTest1)
		{
			Rx rxController;
			Tx txController;
			
			// Create command
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Create parameters
			Param cmdTestParam1("Test parameter 1.");
			cmdTest.RegisterParam(&cmdTestParam1);
			
			Param cmdTestParam2("Test parameter 2.");
			cmdTest.RegisterParam(&cmdTestParam2);
			
			// Create option
			Option cmdTestOption1('a', NULL, "Test option 1");
			cmdTest.RegisterOption(&cmdTestOption1);
			
			Option cmdTestOption2('b', NULL, "Test option 2.");
			cmdTest.RegisterOption(&cmdTestOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test param1 param2 -a -b";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		MTEST(TwoParamTwoOptionRxTest2)
		{
			Rx rxController;
			Tx txController;
			
			// Create command
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Create parameters
			Param cmdTestParam1("Test parameter 1.");
			cmdTest.RegisterParam(&cmdTestParam1);
			
			Param cmdTestParam2("Test parameter 2.");
			cmdTest.RegisterParam(&cmdTestParam2);
			
			// Create option
			Option cmdTestOption1('a', NULL, "Test option 1");
			cmdTest.RegisterOption(&cmdTestOption1);
			
			Option cmdTestOption2('b', NULL, "Test option 2.");
			cmdTest.RegisterOption(&cmdTestOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test param1 -a param2 -b";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		MTEST(TwoParamTwoOptionRxTest3)
		{
			Rx rxController;
			Tx txController;
			
			// Create command
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Create parameters
			Param cmdTestParam1("Test parameter 1.");
			cmdTest.RegisterParam(&cmdTestParam1);
			
			Param cmdTestParam2("Test parameter 2.");
			cmdTest.RegisterParam(&cmdTestParam2);
			
			// Create option
			Option cmdTestOption1('a', NULL, "Test option 1");
			cmdTest.RegisterOption(&cmdTestOption1);
			
			Option cmdTestOption2('b', NULL, "Test option 2.");
			cmdTest.RegisterOption(&cmdTestOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff1[50] = "test -a param1 -b param2";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
			
			// Create fake input buffer
			char rxBuff2[50] = "test param1 param2";
			
			// Run rx controller
			rxController.Run(rxBuff2);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(false, cmdTestOption1.isDetected);
			CHECK_EQUAL(false, cmdTestOption2.isDetected);
		}
		
	} // SUITE(ParamAndOptionTests)*/
} // namespace MClideTest
