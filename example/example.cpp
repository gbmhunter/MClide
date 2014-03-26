//!
//! @file 			example.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created 		2013/07/04
//! @last-modified 	2014/03/26
//! @brief 			Example Clide program, designed to be run on Linux.
//! @details
//!				See README.rst in root dir for more info.

#include <stdio.h>
#include <iostream>
#include <string>

#include "../api/Clide.hpp"

using namespace Clide;
using namespace std;

// Create two command groups
CmdGroup cmdGroupUser("user", "Commands are suitable for the user.");
CmdGroup cmdGroupDev("dev", "Commands are suitable for the developer.");

bool Callback(Cmd *cmd)
{
	return true;
}

class Printer
{
public:
	void PrintDebug(const char* msg)
	{
		std::cout << msg;
	}

	void PrintCmdLine(const char* msg)
	{
		std::cout << msg;
	}

	void PrintError(const char* msg)
	{
		std::cout << msg;
	}
};

int main()
{
	// Configure clide print outputs
	Printer printer;

	Clide::Print::AssignCallbacks(
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintDebug),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintCmdLine),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintError));

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
	Cmd cmdEx3("thisisasuperlongcmd", &Callback, "Example command 3 (long name).");

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

	//============ EXAMPLE COMMAND 4 ===============//

	try
	{
		// Create command
		Cmd cmdEx4("long-description-cmd", &Callback, "This is a super super super super super long command description! It is very long indeed. And getting longer as we speak!");

		// Create parameters
		Param cmdEx4Param1("Example parameter 1.");
		cmdEx4.RegisterParam(&cmdEx4Param1);

		// Create option
		Option cmdEx4Option1('a', NULL, "Example option 1");
		cmdEx4.RegisterOption(&cmdEx4Option1);

		// Assign to group
		cmdEx4.AddToGroup(&cmdGroupUser);

		// Register command
		rxController.RegisterCmd(&cmdEx4);
	}
	catch(const char* msg)
	{
		std::cout << msg << endl;

	}

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
