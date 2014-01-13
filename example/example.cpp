//!
//! @file 			example.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created 		2013/07/04
//! @last-modified 	2014/01/14
//! @brief 			Example Clide program, designed to be run on Linux.
//! @details
//!				See README.rst in root dir for more info.

#include <stdio.h>
#include <iostream>
#include <string>

#include "../src/include/IncludeJustMe.hpp"

using namespace Clide;
using namespace std;

// Create two command groups
CmdGroup cmdGroupUser("user", "Commands are suitable for the user.");
CmdGroup cmdGroupDev("dev", "Commands are suitable for the developer.");

bool Callback(Cmd *cmd)
{
	return true;
}

int main()
{
	// Create a receiver engine
	Rx rxController;

	//============ EXAMPLE COMMAND 1 ===============//

	// Create command
	Cmd cmdEx1("ex1", &Callback, "Example command 1.");

	// Create parameters
	Param cmdEx1Param1("Example parameter 1.");
	cmdEx1.RegisterParam(&cmdEx1Param1);

	Param cmdEx1Param2("Example parameter 2.");
	cmdEx1.RegisterParam(&cmdEx1Param2);

	// Create option
	Option cmdEx1Option1('a', NULL, "Example option 1");
	cmdEx1.RegisterOption(&cmdEx1Option1);

	Option cmdEx1Option2('b', NULL, "Example option 2.");
	cmdEx1.RegisterOption(&cmdEx1Option2);

	// Assign to group
	cmdEx1.AddToGroup(&cmdGroupDev);

	// Register command
	rxController.RegisterCmd(&cmdEx1);

	//============ EXAMPLE COMMAND 2 ===============//

	// Create command
	Cmd cmdEx2("ex2", &Callback, "Example command 2.");
			
	// Create parameters
	Param cmdEx2Param1("Example parameter 1.");
	cmdEx2.RegisterParam(&cmdEx2Param1);
	
	// Create option
	Option cmdEx2Option1('a', NULL, "Example option 1");
	cmdEx2.RegisterOption(&cmdEx2Option1);
	
	// Assign to group
	cmdEx2.AddToGroup(&cmdGroupUser);

	// Register command
	rxController.RegisterCmd(&cmdEx2);
	
	//============ EXAMPLE COMMAND 3 ===============//

	// Create command
	Cmd cmdEx3("ex3", &Callback, "Example command 3.");

	// Create parameters
	Param cmdEx3Param1("Example parameter 1.");
	cmdEx3.RegisterParam(&cmdEx3Param1);

	// Create option
	Option cmdEx3Option1('a', NULL, "Example option 1");
	cmdEx3.RegisterOption(&cmdEx3Option1);

	// Assign to group
	cmdEx3.AddToGroup(&cmdGroupUser);

	// Register command
	rxController.RegisterCmd(&cmdEx3);

	//============ SETUP DEFAULT COMMAND GROUP ==========//

	//rxController.defaultCmdGroup = &cmdGroupUser;

	while(1)
	{
		char inputMsg[30];

		cin.get(inputMsg, 30);
		cin.ignore();

		// Run rx controller
		rxController.Run(inputMsg);
	}
}
