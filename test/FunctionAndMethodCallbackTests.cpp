//!
//! @file 			FunctionAndMethodCallbackTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014/03/21
//! @last-modified 	2014/03/21
//! @brief 			Contains test functions for Clide function and method callbacks.
//! @details
//!					See README.rst in root dir for more info.

#include <stdio.h>

#include "../api/Clide.hpp"

#include "unittest-cpp/UnitTest++/UnitTest++.h"

namespace ClideTest
{
	SUITE(FunctionAndMethodCallbackTests)
	{
		using namespace Clide;

		bool _functionCallbackCalled = NULL;

		// Function callback
		bool Callback(Cmd *cmd)
		{
			_functionCallbackCalled = true;
			
			return true;
		}

		TEST(FunctionCallbackTest)
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
			
			CHECK_EQUAL(true, _functionCallbackCalled);
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

		TEST(MethodCallbackTest)
		{
			Rx rxController;
			Tx txController;

			CallbackClass myCallbackClass;

			// Create command, passing in a method as the callback
			Cmd cmdTest(
				"test",
				SlotMachine::CallbackGen<CallbackClass, void, Cmd*>(&myCallbackClass, &CallbackClass::Callback),
				"A test command.");

			// Register command
			rxController.RegisterCmd(&cmdTest);

			// Create fake input buffer
			char rxBuff[50] = "test";

			myCallbackClass._methodCallbackCalled = false;

			// Run rx controller, this should call the cmd callback
			rxController.Run(rxBuff);

			CHECK_EQUAL(true, myCallbackClass._methodCallbackCalled);
		}
		
		
	} // SUITE(ParamTests)
} // namespace ClideTest
