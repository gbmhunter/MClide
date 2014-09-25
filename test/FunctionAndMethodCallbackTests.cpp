//!
//! @file 			FunctionAndMethodCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-03-21
//! @last-modified 	2014-09-14
//! @brief 			Contains test functions for MClide function and method callbacks.
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

	bool _functionCallbackCalled = NULL;

	// Function callback
	static bool Callback(Cmd *cmd)
	{
		_functionCallbackCalled = true;

		return true;
	}

	MTEST(FunctionCallbackTest)
	{
		Rx rxController;
		Tx txController;

		Cmd cmdTest("test", &Callback, "A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test";

		_functionCallbackCalled = false;

		// Run rx controller, this should call the cmd callback
		rxController.Run(rxBuff);

		CHECK_EQUAL(_functionCallbackCalled, true);
	}

	// Method callback
	class CallbackClass
	{
	public:
		void Callback(Cmd *cmd)
		{
			this->_methodCallbackCalled = true;

		}

		bool _methodCallbackCalled;

	};

	MTEST(MethodCallbackTest)
	{
		Rx rxController;
		Tx txController;

		CallbackClass myCallbackClass;

		// Create command, passing in a method as the callback
		Cmd cmdTest(
			"test",
			MCallbacks::CallbackGen<CallbackClass, void, Cmd*>(&myCallbackClass, &CallbackClass::Callback),
			"A test command.");

		// Register command
		rxController.RegisterCmd(&cmdTest);

		// Create fake input buffer
		char rxBuff[50] = "test";

		myCallbackClass._methodCallbackCalled = false;

		// Run rx controller, this should call the cmd callback
		rxController.Run(rxBuff);

		CHECK_EQUAL(myCallbackClass._methodCallbackCalled, true);
	}
		
} // namespace MClideTest
