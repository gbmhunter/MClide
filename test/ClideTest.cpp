
#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Clide;

bool cmdDetected = false;

bool Callback(Cmd *cmd)
{
	cmdDetected = true;
}

TEST(BasicRxTest)
{

	Rx rxController;
	Tx txController;

	
	Cmd cmdTest("test", &Callback, "A test command.");
	
	// Register command
	rxController.RegisterCmd(&cmdTest);
	
	// Create fake input buffer
	char rxBuff[50] = "test";
	
	cmdDetected = false;
	
	// Run rx controller
	rxController.Run(rxBuff);
	
	CHECK_EQUAL(true, cmdDetected);
}

TEST(OneParamRxTest)
{
	Rx rxController;
	Tx txController;
	
	Cmd cmdTest("test", &Callback, "A test command.");
	Param cmdTestParam("A test parameter");
	cmdTest.RegisterParam(&cmdTestParam);
	
	// Register command
	rxController.RegisterCmd(&cmdTest);
	
	// Create fake input buffer
	char rxBuff[50] = "test param1";
	
	cmdDetected = false;
	
	// Run rx controller
	rxController.Run(rxBuff);
	
	CHECK_EQUAL(true, cmdDetected);
}

TEST(TwoParamRxTest)
{
	Rx rxController;
	Tx txController;
	
	Cmd cmdTest("test", &Callback, "A test command.");
	
	Param cmdTestParam1("Test parameter 1");
	cmdTest.RegisterParam(&cmdTestParam1);
	
	Param cmdTestParam2("Test parameter 2");
	cmdTest.RegisterParam(&cmdTestParam2);
	
	// Register command
	rxController.RegisterCmd(&cmdTest);
	
	// Create fake input buffer
	char rxBuff[50] = "test param1 param2";
	
	cmdDetected = false;
	
	// Run rx controller
	rxController.Run(rxBuff);
	
	CHECK_EQUAL(true, cmdDetected);
}

int main()
{
	return UnitTest::RunAllTests();
}