//!
//! @file 			RxBuffEndOfCmdCharTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-03-21
//! @last-modified 	2014-09-14
//! @brief 			Contains functions which test that the end-of-command char variable in the RxBuff object works.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

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

	MTEST(CarriageReturnTest)
	{
		Rx rxController;

		// Create RxBuff object for taking the characters
		RxBuff rxBuff(&rxController, '\r');

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

		// Create some input and write it to RxBuff
		rxBuff.WriteString((char*)"test param1 -a\r");

		// Check that the command was processed successfully
		CHECK_EQUAL("param1", cmdTestParam.value);
		CHECK_EQUAL(true, cmdTestOption.isDetected);
	}

	MTEST(NewLineTest)
	{
		Rx rxController;

		// Create RxBuff object for taking the characters
		RxBuff rxBuff(&rxController, '\n');

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

		// Create some input and write it to RxBuff
		rxBuff.WriteString((char*)"hghgjkghg\ntest param1 -a\njfjjjhfhg\n");
		
		// Check that the command was processed successfully
		CHECK_EQUAL("param1", cmdTestParam.value);
		CHECK_EQUAL(true, cmdTestOption.isDetected);
	}

	MTEST(ZCharTest)
	{
		Rx rxController;

		// Create RxBuff object for taking the characters
		RxBuff rxBuff(&rxController, 'z');

		// Create command
		Cmd cmd1("test1", &Callback, "A test command.");

		// Create parameter
		Param cmd1Param("A test parameter.");
		cmd1.RegisterParam(&cmd1Param);

		// Create option
		Option cmd1Option('a', NULL, "A test option.");
		cmd1.RegisterOption(&cmd1Option);

		// Register command
		rxController.RegisterCmd(&cmd1);

		// Create command
		Cmd cmd2("test2", &Callback, "A test command.");

		// Create parameter
		Param cmd2Param("A test parameter.");
		cmd2.RegisterParam(&cmd2Param);

		// Create option
		Option cmd2Option('a', NULL, "A test option.");
		cmd2.RegisterOption(&cmd2Option);

		// Register command
		rxController.RegisterCmd(&cmd2);

		// Create input for both commands and write it to RxBuff
		rxBuff.WriteString((char*)"test1 param1 -aztest2 param1 -az");

		// Check that the command was processed successfully
		CHECK_EQUAL("param1", cmd1Param.value);
		CHECK_EQUAL(true, cmd1Option.isDetected);

		CHECK_EQUAL("param1", cmd2Param.value);
		CHECK_EQUAL(true, cmd2Option.isDetected);

	}
		
} // namespace MClideTest
