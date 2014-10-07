//!
//! @file 			ParamsAndOptionTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-10-07
//! @brief 			Contains test functions for MClide command parameters and options in the same command.
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

	MTEST(OneParamThenOneOptionRxTest)
	{
		Rx rxController;
		Tx txController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test param1 -a";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption.isDetected, true);
	}

	MTEST(OneOptionThenOneParamRxTest)
	{
		Rx rxController;
		Tx txController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameter
		Param cmdTestParam("A test parameter.");
		cmdTest.RegisterParam(&cmdTestParam);

		// Create option
		Option cmdTestOption('a', NULL, "A test option.");
		cmdTest.RegisterOption(&cmdTestOption);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test -a param1";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(cmdTestParam.value, "param1");
		CHECK_EQUAL(cmdTestOption.isDetected, true);
	}

	MTEST(TwoParamTwoOptionRxTest1)
	{
		Rx rxController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameters
		Param cmdTestParam1("Test parameter 1.");
		cmdTest.RegisterParam(&cmdTestParam1);

		Param cmdTestParam2("Test parameter 2.");
		cmdTest.RegisterParam(&cmdTestParam2);

		// Create option
		Option cmdTestOption1('a', NULL, "Test option 1");
		cmdTest.RegisterOption(&cmdTestOption1);

		Option cmdTestOption2('b', NULL, "Test option 2.");
		cmdTest.RegisterOption(&cmdTestOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test param1 param2 -a -b";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(cmdTestParam1.value, "param1");
		CHECK_EQUAL(cmdTestParam2.value, "param2");
		CHECK_EQUAL(cmdTestOption1.isDetected, true);
		CHECK_EQUAL(cmdTestOption2.isDetected, true);
	}

	MTEST(TwoParamTwoOptionRxTest2)
	{
		Rx rxController;
		Tx txController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameters
		Param cmdTestParam1("Test parameter 1.");
		cmdTest.RegisterParam(&cmdTestParam1);

		Param cmdTestParam2("Test parameter 2.");
		cmdTest.RegisterParam(&cmdTestParam2);

		// Create option
		Option cmdTestOption1('a', NULL, "Test option 1");
		cmdTest.RegisterOption(&cmdTestOption1);

		Option cmdTestOption2('b', NULL, "Test option 2.");
		cmdTest.RegisterOption(&cmdTestOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test param1 -a param2 -b";

		// Run rx controller
		rxController.Run(rxBuff);

		CHECK_EQUAL(cmdTestParam1.value, "param1");
		CHECK_EQUAL(cmdTestParam2.value, "param2");
		CHECK_EQUAL(cmdTestOption1.isDetected, true);
		CHECK_EQUAL(cmdTestOption2.isDetected, true);
	}

	MTEST(TwoParamTwoOptionRxTest3)
	{
		Rx rxController;
		Tx txController;

		// Create command
		Cmd cmdTest("test", &Callback, "A test command.");

		// Create parameters
		Param cmdTestParam1("Test parameter 1.");
		cmdTest.RegisterParam(&cmdTestParam1);

		Param cmdTestParam2("Test parameter 2.");
		cmdTest.RegisterParam(&cmdTestParam2);

		// Create option
		Option cmdTestOption1('a', NULL, "Test option 1");
		cmdTest.RegisterOption(&cmdTestOption1);

		Option cmdTestOption2('b', NULL, "Test option 2.");
		cmdTest.RegisterOption(&cmdTestOption2);

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff1[50] = "test -a param1 -b param2";
		
		// Run rx controller
		rxController.Run(rxBuff1);
		
		CHECK_EQUAL(cmdTestParam1.value, "param1");
		CHECK_EQUAL(cmdTestParam2.value, "param2");
		CHECK_EQUAL(cmdTestOption1.isDetected, true);
		CHECK_EQUAL(cmdTestOption2.isDetected, true);
		
		// Create fake input buffer
		char rxBuff2[50] = "test param1 param2";
		
		// Run rx controller
		rxController.Run(rxBuff2);
		
		CHECK_EQUAL(cmdTestParam1.value, "param1");
		CHECK_EQUAL(cmdTestParam2.value, "param2");
		CHECK_EQUAL(cmdTestOption1.isDetected, false);
		CHECK_EQUAL(cmdTestOption2.isDetected, false);
	}

} // namespace MClideTest
