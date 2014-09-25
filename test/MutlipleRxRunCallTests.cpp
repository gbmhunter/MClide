//!
//! @file 			MultipleRxRunCallTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for mutliple calls to MClide::Rx.Run().
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

	MTEST(RxRun4TimesTest)
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

		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption1.isDetected, true);
		CHECK_EQUAL(cmdTestOption2.isDetected, false);

		// Create fake input buffer
		char rxBuff2[50] = "test param1 --topt";

		// Run rx controller
		rxController.Run(rxBuff2);

		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption1.isDetected, false);
		CHECK_EQUAL(cmdTestOption2.isDetected, true);

		// Create fake input buffer
		char rxBuff3[50] = "test param1";

		// Run rx controller
		rxController.Run(rxBuff3);

		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption1.isDetected, false);
		CHECK_EQUAL(cmdTestOption2.isDetected, false);

		// Create fake input buffer
		char rxBuff4[50] = "test --topt -a param1";

		// Run rx controller
		rxController.Run(rxBuff4);
		
		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption1.isDetected, true);
		CHECK_EQUAL(cmdTestOption2.isDetected, true);
	}

} // namespace MClideTest
