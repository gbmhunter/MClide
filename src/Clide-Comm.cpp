//!
//! @file 			Clide-Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/12/18
//! @last-modified 	2013/12/18
//! @brief			The base communications class. This is extended by both Clide::Tx and Clide::Rx which are the classes manipulated by the user.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdint.h>		// int8_t, int32_t e.t.c
#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <cstring>		// memset()

// User includes
#include "./include/Clide-Config.hpp"
#include "./include/Clide-Global.hpp"
#include "./include/Clide-MemMang.hpp"
#include "./include/Clide-StringSplit.hpp"
#include "./include/Clide-Param.hpp"
#include "./include/Clide-Option.hpp"
#include "./include/Clide-Cmd.hpp"
#include "./include/Clide-Port.hpp"
#include "./include/Clide-Rx.hpp"
#include "./include/Clide-GetOpt.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	using namespace std;

	bool HelpCmdCallback(Cmd *cmd)
	{
		// Print the help for the parent Comm object that
		// the called help command was assigned to
		cmd->parentComm->PrintHelp();
		return true;
	}

	//===============================================================================================//
	//====================================== PUBLIC METHODS ========================================//
	//===============================================================================================//

	// Constructor
	Comm::Comm()
	{
		// Initialise class variables
		this->numCmds = 0;
		this->cmdA = NULL;
		this->helpEnabled = true;

	}

	// Prints out the help info
	void Comm::PrintHelp()
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)	
			Port::DebugPrint("CLIDE: Print help function called.");
		#endif
		
		// Title
		Port::CmdLinePrint("List of commands:\r\n");

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Port::CmdLinePrint(clide_TABLE_HEADER_ROW_COLOUR_CODE);
		#endif

		Port::CmdLinePrint("\tcmd\tdescription\r\n");

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Port::CmdLinePrint(clide_TERM_TEXT_FORMAT_NORMAL);
		#endif

		// Iterate through cmd array and print commands
		uint32_t x;
		for(x = 0; x < numCmds; x++)
		{
			Port::CmdLinePrint("\t");
			Port::CmdLinePrint(cmdA[x]->name);
			// Add tab character
			Port::CmdLinePrint("\t");
			// Print description
			Port::CmdLinePrint(cmdA[x]->description);
			// \r is enough for PuTTy to format onto a newline also
			// (adding \n causes it to add two new lines)
			Port::CmdLinePrint("\r\n");
		}

	}


	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//



} // namespace Clide

// EOF
