//!
//! @file 			OptionsWithValueTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for MClide command options.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

using namespace MbeddedNinja::MClideNs;

namespace MClideTest
{

	static bool Callback(Cmd *cmd)
	{
		return true;
	}


	MTEST(OnePosShortOptionWithValuesTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption('a', "", NULL, "A test option.", true);

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test -a optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		CHECK_EQUAL(testOption.isDetected, true);
		CHECK_EQUAL(testOption.value, "optVal");
		
		// Create fake input buffer
		char rxBuff2[50] = "test";

		// Run rx controller
		rxController.Run(rxBuff2);

		CHECK_EQUAL(testOption.isDetected, false);
	}


	MTEST(TwoPosShortOptionWithValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', NULL, "Test option 1.");
		Option testOption2('b', NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);
		
		// Create fake input buffer
		char rxBuff[50] = "test -a -b";
		
		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption2.isDetected, true);

		
	}

	MTEST(OnePosOneNegShortOptionWithValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', NULL, "Test option 1.");
		Option testOption2('b', NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create input buffer
		char rxBuff[50] = "test -a";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(testOption1.isDetected, true);
		CHECK_EQUAL(testOption2.isDetected, false);

		}
		
} // namespace MClideTest
