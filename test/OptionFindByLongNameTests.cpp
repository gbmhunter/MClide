//!
//! @file 			OptionFindByLongNameTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-05-16
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for finding options by their long name.
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

	MTEST(OneOptionFindByLongNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption('a', "opta", NULL, "A test option.", true);

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test --opta optVal";

		// Run rx controller
		rxController.Run(rxBuff1);
		
		Option* returnedOption = cmdTest.FindOptionByLongName("opta");

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);
	}

	MTEST(TwoPosOptionFindByLongNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', "opta", NULL, "Test option a.", true);

		// Register option
		cmdTest.RegisterOption(&testOption1);

		Option testOption2('b', "optb", NULL, "Test option b.", true);

		// Register option
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test --opta optVal -optb optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		Option* returnedOption = cmdTest.FindOptionByLongName("opta");

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);

		returnedOption = cmdTest.FindOptionByLongName("optb");

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);
	}

	MTEST(OnePosOneNegOptionFindByNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption1('a', "opta", NULL, "Test option a.", true);

		// Register option
		cmdTest.RegisterOption(&testOption1);

		Option testOption2('b', "optb", NULL, "Test option b.", true);

		// Register option
		cmdTest.RegisterOption(&testOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test --opta optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		Option* returnedOption = cmdTest.FindOptionByLongName("opta");

		if(returnedOption == nullptr)
			CHECK(false);
		else
			CHECK_EQUAL(true, returnedOption->isDetected);

		returnedOption = cmdTest.FindOptionByLongName("optb");

		if(returnedOption == nullptr)
			CHECK(false);
		else
			// Should of not been detected
			CHECK_EQUAL(false, returnedOption->isDetected);
	}

	MTEST(FindNonexistantOptionByLongNameTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");
		Option testOption('a', "opta", NULL, "A test option.", true);

		// Register option
		cmdTest.RegisterOption(&testOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test --opta optVal";

		// Run rx controller
		rxController.Run(rxBuff1);

		// Look for an option that doesn't exist
		Option* returnedOption = cmdTest.FindOptionByLongName("optb");

		// Should of returned a null-pointer
		if(returnedOption == nullptr)
			CHECK(true);
		else
			CHECK(false);
	}
		
} // namespace MClideTest
