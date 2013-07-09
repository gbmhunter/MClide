//!
//! @file 		ClideTest-MultipleRxRunCalls.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for mutliple calls to Clide::Rx.Run().
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
	SUITE(MultipleRxRunCallsTests)
	{
		using namespace Clide;

		bool Callback(Cmd *cmd)
		{
			return true;
		}
		
		TEST(RxRun4TimesTest)
		{
			Rx rxController;
			
			// Create command
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Create parameter
			Param cmdTestParam("A test parameter.");
			cmdTest.RegisterParam(&cmdTestParam);
			
			// Create option
			Option cmdTestOption1('a', NULL, "Test option 1.");
			cmdTest.RegisterOption(&cmdTestOption1);
			
			Option cmdTestOption2("topt", NULL, "Test option 2.");
			cmdTest.RegisterOption(&cmdTestOption2);
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff1[50] = "test param1 -a";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(false, cmdTestOption2.isDetected);
			
			// Create fake input buffer
			char rxBuff2[50] = "test param1 --topt";
			
			// Run rx controller
			rxController.Run(rxBuff2);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(false, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);
			
			// Create fake input buffer
			char rxBuff3[50] = "test param1";
			
			// Run rx controller
			rxController.Run(rxBuff3);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(false, cmdTestOption1.isDetected);
			CHECK_EQUAL(false, cmdTestOption2.isDetected);		

			// Create fake input buffer
			char rxBuff4[50] = "test --topt -a param1";
			
			// Run rx controller
			rxController.Run(rxBuff4);
			
			CHECK_EQUAL("param1", cmdTestParam.value);
			CHECK_EQUAL(true, cmdTestOption1.isDetected);
			CHECK_EQUAL(true, cmdTestOption2.isDetected);	
		}	
	} // SUITE(MultipleRxRunCallsTests)
} // namespace ClideTest