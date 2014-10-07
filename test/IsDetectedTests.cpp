//!
//! @file 			IsDetectedTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for MClide command isDetected flag.
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

	bool Callback1(Cmd *cmd)
	{

		return true;
	}

	MTEST(BasicIsDetectedTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest1("test1", &Callback1, "Test command 1.");

		// Register commands
		rxController.RegisterCmd(&cmdTest1);

		// Create fake input buffer
		char rxBuff1[50] = "test1";

		// Run rx controller
		rxController.Run(rxBuff1);

		// Make sure cmd1 is true, cmd2 is false
		CHECK_EQUAL(cmdTest1.isDetected, true);
	}

	MTEST(IsDetectedGetsResetTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest1("test1", &Callback1, "Test command 1.");
		Cmd cmdTest2("test2", &Callback1, "Test command 2.");

		// Register commands
		rxController.RegisterCmd(&cmdTest1);
		rxController.RegisterCmd(&cmdTest2);

		// Create fake input buffer
		char rxBuff1[50] = "test1";

		// Run rx controller
		rxController.Run(rxBuff1);

		// Make sure cmd1 is true, cmd2 is false
		CHECK_EQUAL(cmdTest1.isDetected, true);
		CHECK_EQUAL(cmdTest2.isDetected, false);

		// Create input buffer
		char rxBuff2[50] = "test2";

		// Run rx controller
		rxController.Run(rxBuff2);

		// Make sure cmd1 is false, cmd2 is true
		CHECK_EQUAL(cmdTest1.isDetected, false);
		CHECK_EQUAL(cmdTest2.isDetected, true);

		// TEST ALL CMDS ARE CLEARED

		// Create bogus input buffer
		char rxBuff3[50] = "test3";

		// Run rx controller
		rxController.Run(rxBuff3);

		// Make sure cmd1 is false, cmd2 is true
		CHECK_EQUAL(cmdTest1.isDetected, false);
		CHECK_EQUAL(cmdTest2.isDetected, false);
	}

} // namespace MClideTest

