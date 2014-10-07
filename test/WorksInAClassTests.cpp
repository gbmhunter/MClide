//!
//! @file 			WorksInAClassTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-04-02
//! @last-modified 	2014-10-07
//! @brief 			Contains tests to make sure MClide works when used as part of a class.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

using namespace MbeddedNinja::MClideNs;

namespace MClideTest
{

	class MyTestClass
	{
		public:
		Rx rxController;
		Cmd cmdTest;
		Param cmdTestParam;
		Option cmdTestOption;

		bool callbackCalled;

		MyTestClass() :
			rxController(),
			cmdTest(
					(const char*)"test",
					MCallbacks::CallbackGen<MyTestClass, void, Cmd*>(this, &MyTestClass::Callback),
					"A test command."),
			cmdTestParam("A test parameter."),
			cmdTestOption('a', NULL, "A test option."),
			callbackCalled(false)
		{
			// Create parameter
			this->cmdTest.RegisterParam(&this->cmdTestParam);

			// Create option
			this->cmdTest.RegisterOption(&this->cmdTestOption);

			// Register command
			this->rxController.RegisterCmd(&this->cmdTest);
		}

		void Run()
		{
			// Create fake input buffer
			char rxBuff[50] = "test param1 -a";

			// Run rx controller
			this->rxController.Run(rxBuff);
		}

		void Callback(Cmd *cmd)
		{
			this->callbackCalled = true;
		}
	};

	MTEST(WorksInAClassTest)
	{
		MyTestClass myTestClass;

		myTestClass.Run();

		CHECK_EQUAL(myTestClass.cmdTestParam.value, "param1");
		CHECK_EQUAL(myTestClass.cmdTestOption.isDetected, true);
		CHECK_EQUAL(myTestClass.callbackCalled, true);
	}
		
} // namespace MClideTest
