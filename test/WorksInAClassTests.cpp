//!
//! @file 			WorksInAClassTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014/04/02
//! @last-modified 	2014/04/02
//! @brief 			Contains tests to make sure Clide works when used as part of a class.
//! @details
//!					See README.rst in root dir for more info.

#include "../api/Clide.hpp"

#include "UnitTest++/UnitTest++/UnitTest++.h"

namespace ClideTest
{

	SUITE(WorksInAClassTests)
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
							SlotMachine::CallbackGen<MyTestClass, void, Clide::Cmd*>(this, &MyTestClass::Callback),
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

		TEST(WorksInAClassTest)
		{
			MyTestClass myTestClass;
			
			myTestClass.Run();
			
			CHECK_EQUAL("param1", myTestClass.cmdTestParam.value);
			CHECK_EQUAL(true, myTestClass.cmdTestOption.isDetected);
			CHECK_EQUAL(true, myTestClass.callbackCalled);
		}
		
	} // SUITE(WorksInAClassTests)
} // namespace ClideTest
