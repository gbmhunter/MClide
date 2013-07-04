//!
//! @file 		ClideTest-Param.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for Clide command parameters.
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
		
		CHECK_EQUAL(true, _cmd->isDetected);
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
		
		CHECK_EQUAL(true, _cmd->isDetected);
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
		
		CHECK_EQUAL(true, _cmd->isDetected);
	}	
	
}