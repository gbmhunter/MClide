//!
//! @file 			ParamTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/07/04
//! @last-modified 	2014/01/14
//! @brief 			Contains test functions for Clide command parameters.
//! @details
//!					See README.rst in root dir for more info.

#include <stdio.h>

#include "../src/include/IncludeJustMe.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(ParamTests)
	{
		using namespace Clide;

		Cmd *_cmd = NULL;

		bool Callback(Cmd *cmd)
		{
			_cmd = cmd; 
			
			return true;
		}
		
		TEST(BasicRxTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			printf("%s", "Debug\r\n");
			
			if(_cmd != NULL)
				CHECK_EQUAL(true, _cmd->isDetected);
			else
				CHECK(false);
		}

		
		TEST(OneParamRxTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Param cmdTestParam("A test parameter");
			cmdTest.RegisterParam(&cmdTestParam);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test param1";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			if(_cmd != NULL)
				CHECK_EQUAL(true, _cmd->isDetected);
			else
				CHECK(false);
		}
		
		TEST(TwoParamRxTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			
			Param cmdTestParam1("Test parameter 1");
			cmdTest.RegisterParam(&cmdTestParam1);
			
			Param cmdTestParam2("Test parameter 2");
			cmdTest.RegisterParam(&cmdTestParam2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test param1 param2";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			if(_cmd != NULL)
				CHECK_EQUAL(true, _cmd->isDetected);
			else
				CHECK(false);
		}	
	} // SUITE(ParamTests)
} // namespace ClideTest
