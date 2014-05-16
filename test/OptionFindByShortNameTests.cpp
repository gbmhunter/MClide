//!
//! @file 			OptionFindByShortNameTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/05/16
//! @last-modified 	2014/05/16
//! @brief 			Contains test functions for finding options by their short name.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(OptionFindByShortNameTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{	
			return true;
		}
		
		TEST(OneOptionFindByShortNameTest)
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
		
		TEST(TwoPosOptionFindByShortNameTest)
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

		TEST(OnePosOneNegOptionFindByShortNameTest)
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

		TEST(FindNonexistantOptionByShortNameTest)
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
		
	} // SUITE(OptionFindByShortNameTests)
} // namespace ClideTest
