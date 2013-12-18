//!
//! @file 			example.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created 		2013/07/04
//! @last-modified 	2013/12/19
//! @brief 			Example Clide program, designed to be run on Linux.
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
	
	// Register command
	rxController.RegisterCmd(&cmdEx2);
	
	//while(1)
	//{
		char inputMsg[30];
		cin.get(inputMsg, 30);
		//cout << inputMsg;
		// Run rx controller
		rxController.Run(inputMsg);
	//}
}
