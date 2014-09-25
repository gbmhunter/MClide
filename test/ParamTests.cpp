//!
//! @file 			ParamTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for Clide command parameters.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

namespace MClideTest
{

	using namespace Clide;

	Cmd *_cmd = NULL;

	static bool Callback(Cmd *cmd)
	{
		_cmd = cmd;

		return true;
	}

	MTEST(BasicRxTest)
	{

		Rx rxController;

		Cmd cmdTest("test", &Callback, "A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test";

		_cmd = NULL;

		// Run rx controller
		rxController.Run(rxBuff);

		if(_cmd != NULL)
			CHECK_EQUAL(_cmd->isDetected, true);
		else
			CHECK(false);
	}


	MTEST(OneParamRxTest)
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
			CHECK_EQUAL(_cmd->isDetected, true);
		else
			CHECK(false);
	}

	MTEST(TwoParamRxTest)
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
			CHECK_EQUAL(_cmd->isDetected, true);
		else
			CHECK(false);
	}

} // namespace MClideTest
