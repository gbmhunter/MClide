//!
//! @file 			StandardMainVariablesAsInputTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014/03/26
//! @last-modified 	2014/04/02
//! @brief 			Contains test functions when standard main variables argc and argv variables are used an input.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(StandardMainVariablesAsInputTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{
			return true;
		}

		TEST(EmptyArgvRxTest)
		{
			Rx rxController;

			//Clide::Print::enableCmdLinePrinting = true;
			//Clide::Print::enableErrorPrinting = true;
			//Clide::Print::enableDebugInfoPrinting = true;

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

			// Create empty main variables
			char* argv[1];
			argv[0] = NULL;
			int argc = 0;

			// Run rx controller
			rxController.Run(argc, argv);

			// Make sure the command WAS NOT detected
			CHECK_EQUAL(false, cmdTestOption.isDetected);

			//Clide::Print::enableCmdLinePrinting = false;
			//Clide::Print::enableErrorPrinting = false;
			//Clide::Print::enableDebugInfoPrinting = false;
		}

		TEST(OneParamThenOneOptionArgvRxTest)
		{
			Rx rxController;
			
			rxController.ignoreFirstArgvElement = false;

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
			
			// Create standard main variables
			char* argv[4];

			argv[0] = (char*)"test";
			argv[1] = (char*)"param1";
			argv[2] = (char*)"-a";
			argv[3] = NULL;

			int argc = 3;
			
			// Run rx controller
			rxController.Run(argc, argv);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		

		TEST(OneOptionThenOneParamArgvRxTest)
		{
			Rx rxController;
			
			rxController.ignoreFirstArgvElement = false;

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
			
			// Create standard main variables
			char* argv[4];
			argv[0] = (char*)"test";
			argv[1] = (char*)"-a";
			argv[2] = (char*)"param1";
			argv[3] = NULL;

			int argc = 3;
			
			// Run rx controller
			rxController.Run(argc, argv);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(TwoParamTwoOptionArgvRxTest1)
		{
			Rx rxController;
			
			rxController.ignoreFirstArgvElement = false;

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
			
			// Create standard main variables
			char* argv[6];
			argv[0] = (char*)"test";
			argv[1] = (char*)"param1";
			argv[2] = (char*)"param2";
			argv[3] = (char*)"-a";
			argv[4] = (char*)"-b";
			argv[5] = NULL;

			int argc = 5;

			// Run rx controller
			rxController.Run(argc, argv);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(TwoParamTwoOptionArgvRxTest2)
		{
			Rx rxController;
			
			rxController.ignoreFirstArgvElement = false;

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
			
			// Create standard main variables
			char* argv[6];
			argv[0] = (char*)"test";
			argv[1] = (char*)"param1";
			argv[2] = (char*)"-a";
			argv[3] = (char*)"param2";
			argv[4] = (char*)"-b";
			argv[5] = NULL;

			int argc = 5;

			// Run rx controller
			rxController.Run(argc, argv);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(TwoParamTwoOptionArgvRxTest3)
		{
			Rx rxController;
			
			rxController.ignoreFirstArgvElement = false;

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
			
			// Create standard main variables
			char* argv[6];
			argv[0] = (char*)"test";
			argv[1] = (char*)"-a";
			argv[2] = (char*)"param1";
			argv[3] = (char*)"-b";
			argv[4] = (char*)"param2";
			argv[5] = NULL;

			int argc = 5;

			// Run rx controller
			rxController.Run(argc, argv);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
			
			// Create standard main variables
			argv[0] = (char*)"test";
			argv[1] = (char*)"param1";
			argv[2] = (char*)"param2";
			argv[3] = NULL;

			argc = 3;

			// Run rx controller
			rxController.Run(argc, argv);

			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(false, cmdTestOption1.isDetected);
			CHECK_EQUAL(false, cmdTestOption2.isDetected);
		}

		TEST(IgnoreFirstElementOfArgvRxTest)
		{
			Rx rxController;

			// Rx::ignoreFirstArgvElement should default to true, so don't set it here

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

			// Create standard main variables
			char* argv[5];

			argv[0] = (char*)"thisShouldbeIgnored";
			argv[1] = (char*)"test";
			argv[2] = (char*)"param1";
			argv[3] = (char*)"-a";
			argv[4] = NULL;

			int argc = 4;

			// Run rx controller
			rxController.Run(argc, argv);

			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}

	} // SUITE(ParamAndOptionTests)
} // namespace ClideTest
