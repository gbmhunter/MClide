//!
//! @file 			WorksInAClassTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-04-02
//! @last-modified 	2014-09-14
//! @brief 			Contains tests to make sure MClide works when used as part of a class.
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
						MCallbacks::CallbackGen<MyTestClass, void, Clide::Cmd*>(this, &MyTestClass::Callback),
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

		CHECK_EQUAL("param1", myTestClass.cmdTestParam.value);
		CHECK_EQUAL(true, myTestClass.cmdTestOption.isDetected);
		CHECK_EQUAL(true, myTestClass.callbackCalled);
	}
		
} // namespace MClideTest
