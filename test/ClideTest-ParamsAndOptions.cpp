//!
//! @file 		ClideTest-ParamsAndOptions.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for Clide command parameters and options in the same
//!				command.
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
	SUITE(ParamAndOptionTests)
	{
		using namespace Clide;

		Cmd *_cmd = NULL;

		bool Callback(Cmd *cmd)
		{
			_cmd = cmd; 
			
			return true;
		}

		TEST(OneParamThenOneOptionRxTest)
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
			char rxBuff[50] = "test param1 -a";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(OneOptionThenOneParamRxTest)
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
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption.isDetected);
		}
		
		TEST(TwoParamTwoOptionRxTest1)
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
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(TwoParamTwoOptionRxTest2)
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
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
		TEST(TwoParamTwoOptionRxTest3)
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
			char rxBuff[50] = "test -a param1 -b param2";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			CHECK_EQUAL("param1", cmdTestParam1.value);
			CHECK_EQUAL("param2", cmdTestParam2.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
		}
		
	} // SUITE(ParamAndOptionTests)
} // namespace ClideTest