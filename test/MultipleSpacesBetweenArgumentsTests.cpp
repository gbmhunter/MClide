//!
//! @file 			MultipleSpacesBetweenArgumentsTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013/07/12
//! @last-modified 	2014/01/21
//! @brief 			Contains test functions for Clide commands with multiple spaces between arguments.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(MultipleSpacesBetweenArguments)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{
			return true;
		}

		TEST(MultipleSpacesBetweenArgumentsTest1)
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
			char rxBuff[50] = "test  param1  -a";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(MultipleSpacesBetweenArgumentsTest2)
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
			char rxBuff[50] = "test  -a param1";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(MultipleSpacesBetweenArgumentsTest3)
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
			char rxBuff[50] = "test   param1  param2   -a -b";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(MultipleSpacesBetweenArgumentsTest4)
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
			char rxBuff[50] = "test  param1    -a param2    -b";
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(MultipleSpacesBetweenArgumentsTest5)
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
			char rxBuff1[50] = "test   -a   param1  -b   param2";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
			
			// Create fake input buffer
			char rxBuff2[50] = "test    param1 param2";
			
			// Run rx controller
			rxController.Run(rxBuff2);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(false, cmdTestOption1.isDetected);
			CHECK_EQUAL(false, cmdTestOption2.isDetected);
		}
		
	} // SUITE(MultipleSpacesBetweenArguments)
} // namespace ClideTest
