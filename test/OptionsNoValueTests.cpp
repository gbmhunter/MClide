//!
//! @file 			OptionsNoValueTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09014
//! @brief 			Contains test functions for Clide command options.
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

	static Cmd *_cmd = NULL;

	bool Callback2(Cmd *cmd)
	{
		_cmd = cmd;

		return true;
	}

	MTEST(OnePosShortOptionNoValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback2, "A test command.");
		Option testOption('z', NULL, "A test option.");

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test -z";

		_cmd = NULL;

		// Run rx controller
		rxController.Run(rxBuff);

		if(_cmd != NULL)
			CHECK_EQUAL(true, testOption.isDetected);
		else
			CHECK(false);
			
	}

	MTEST(TwoPosShortOptionNoValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback2, "A test command.");
		Option testOption1('a', NULL, "Test option 1.");
		Option testOption2('b', NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test -a -b";

		_cmd = NULL;

		// Run rx controller
		rxController.Run(rxBuff);
		
		if(_cmd != NULL)
		{
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL(true, testOption2.isDetected);
		}
		else
			CHECK(false);

	}

	MTEST(OnePosOneNegShortOptionNoValuesTest)
	{

		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback2, "A test command.");
		Option testOption1('a', NULL, "Test option 1.");
		Option testOption2('b', NULL, "Test option 2.");

		// Register options
		cmdTest.RegisterOption(&testOption1);
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create input buffer
		char rxBuff[50] = "test -a";

		_cmd = NULL;
		
		// Run rx controller
		rxController.Run(rxBuff);

		if(_cmd != NULL)
		{
			CHECK_EQUAL(true, testOption1.isDetected);
			CHECK_EQUAL(false, testOption2.isDetected);
		}
		else
			CHECK(false);

	}
		
} // namespace MClideTest
