//!
//! @file 			QuotesAndNegativeNumberTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for Clide command options with negative numbers.
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

	static bool Callback(Cmd *cmd)
	{
		return true;
	}

	MTEST(QuotesTest)
	{
		Rx rxController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption('a', "", NULL, "A test option.", true);

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test -a \"-8\"";

		// Run rx controller
		rxController.Run(rxBuff1);

		CHECK_EQUAL(testOption.isDetected, true);
		CHECK_EQUAL(testOption.value, "\"-8\"");

		// Create fake input buffer
		char rxBuff2[50] = "test";

		// Run rx controller
		rxController.Run(rxBuff2);
		
		CHECK_EQUAL(testOption.isDetected, false);
	}

} // namespace MClideTest
