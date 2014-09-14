//!
//! @file 			OptionsWithValueTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for MClide command options.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
// none

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

		CHECK_EQUAL(true, testOption.isDetected);
		CHECK_EQUAL("optVal", testOption.value);
		
		// Create fake input buffer
		char rxBuff2[50] = "test";

		// Run rx controller
		rxController.Run(rxBuff2);

		CHECK_EQUAL(false, testOption.isDetected);
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

		CHECK_EQUAL(true, testOption1.isDetected);
		CHECK_EQUAL(true, testOption2.isDetected);

		
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

		CHECK_EQUAL(true, testOption1.isDetected);
		CHECK_EQUAL(false, testOption2.isDetected);

		}
		
} // namespace MClideTest
