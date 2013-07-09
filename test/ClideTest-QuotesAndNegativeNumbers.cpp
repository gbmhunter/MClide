//!
//! @file 		ClideTest-QuotesAndNegativeNumbers.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for Clide command options with negative numbers. 
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(QuotesAndNegativeNumberTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{	
			return true;
		}
		
		TEST(QuotesTest)
		{
			Rx rxController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			Option testOption('a', NULL, NULL, "A test option.", true);
			
			// Register option
			cmdTest.RegisterOption(&testOption);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff1[50] = "test -a \"-8\"";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			CHECK_EQUAL(true, testOption.isDetected);
			CHECK_EQUAL("\"-8\"", testOption.value);
			
			// Create fake input buffer
			char rxBuff2[50] = "test";
			
			// Run rx controller
			rxController.Run(rxBuff2);
			
			CHECK_EQUAL(false, testOption.isDetected);
		}
	} // SUITE(QuotesAndNegativeNumberTests)
} // namespace ClideTest