//!
//! @file 		example.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Example clide program, designed to be run on Linux.
//! @details
//!				See README.rst in root dir for more info.

#include <stdio.h>
#include <iostream>
#include <string>

#include "../src/include/Clide-IncludeJustMe.hpp"

using namespace Clide;
using namespace std;

bool Callback(Cmd *cmd)
{
	return true;
}

int main()
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
	
	// Enable help
	rxController.helpEnabled = true;
	

	char inputMsg[30];
	cin.get(inputMsg, 30);
	//cout << inputMsg;
	// Run rx controller
	rxController.Run(inputMsg);
	

	
}
