//!
//! @file 			OptionFindByShortNameTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-05-16
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for finding options by their short name.
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

	MTEST(OneOptionFindByShortNameTest)
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
		
		Option* returnedOption = cmdTest.FindOptionByShortName('a');

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);
	}

	MTEST(TwoPosOptionFindByShortNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', "", NULL, "Test option a.", true);

		// Register option
		cmdTest.RegisterOption(&testOption1);

		Option testOption2('b', "", NULL, "Test option b.", true);

		// Register option
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test -a optVal -b optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		Option* returnedOption = cmdTest.FindOptionByShortName('a');

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);

		returnedOption = cmdTest.FindOptionByShortName('b');

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);
	}

	MTEST(OnePosOneNegOptionFindByShortNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', "", NULL, "Test option a.", true);

		// Register option
		cmdTest.RegisterOption(&testOption1);

		Option testOption2('b', "", NULL, "Test option b.", true);

		// Register option
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test -a optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		Option* returnedOption = cmdTest.FindOptionByShortName('a');

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);

		returnedOption = cmdTest.FindOptionByShortName('b');

		if(returnedOption == nullptr)
			CHECK(false);
		else
			// Should of not been detected
			CHECK_EQUAL(false, returnedOption->isDetected);
	}

	MTEST(FindNonexistantOptionByShortNameTest)
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

		// Look for an option that doesn't exist
		Option* returnedOption = cmdTest.FindOptionByShortName('b');

		// Should of returned a null-pointer
		if(returnedOption == nullptr)
			CHECK(true);
		else
			CHECK(false);
	}
		
} // namespace MClideTest
