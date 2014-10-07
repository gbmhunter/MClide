//!
//! @file 			SpasticInputTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for stressing the input with spastic characters. The idea here is just to make sure no unexpected characters can cause Rx.Run() to crash.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

using namespace MbeddedNinja::MClideNs;

namespace MClideTest
{

	static Cmd *_cmd = NULL;

	static bool Callback(Cmd *cmd)
	{
		_cmd = cmd;

		return true;
	}

	MTEST(SpasticInputTest1)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test !@#";

		_cmd = NULL;

		// Run rx controller
		rxController.Run(rxBuff);

		// Just check to make sure execution gets to
		// this point
		CHECK(true);
	}

	MTEST(SpasticInputTest2)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "!34 !@#";

		_cmd = NULL;

		// Run rx controller
		rxController.Run(rxBuff);

		// Just check to make sure execution gets to
		// this point
		CHECK(true);
	}

	MTEST(SpasticInputTest3)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "#$^ &*()";

		_cmd = NULL;
		
		// Run rx controller
		rxController.Run(rxBuff);
		
		// Just check to make sure execution gets to
		// this point
		CHECK(true);
	}
		
} // namespace MClideTest
