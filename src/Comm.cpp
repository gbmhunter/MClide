//!
//! @file 			Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/12/18
//! @last-modified 	2014/01/21
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
#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/MemMang.hpp"
#include "../include/Param.hpp"
#include "../include/Option.hpp"
#include "../include/Cmd.hpp"
#include "../include/Print.hpp"
#include "../include/Rx.hpp"

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
		cmd->parentComm->PrintHelp(cmd);
		return true;
	}

	//===============================================================================================//
	//====================================== PUBLIC METHODS ========================================//
	//===============================================================================================//

	Comm::Comm()
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)
			Print::debugPrintCallback.Execute("CLIDE: Comm constructor called...\r\n");
		#endif

		// Initialise class variables
		this->numCmds = 0;
		this->cmdA = NULL;

		// Create a CmdGroup object that all commands will belong to
		this->cmdGroupAll = new CmdGroup("all", "All commands belong to this group.");

		// Default command group points to "all", so that if this is not reassigned, when "help"
		// is called, all commands will be printed.
		this->defaultCmdGroup = this->cmdGroupAll;

		#if(clideDEBUG_PRINT_GENERAL == 1)
			Print::debugPrintCallback.Execute("CLIDE: Comm constructor finished.\r\n");
		#endif
	}

	void Comm::RegisterCmd(Cmd* cmd)
	{
		// Save this Rx object as the parent object for this command. This is used
		// for the automatically added help command.
		cmd->parentComm = this;

		// Add "all" command group to this command
		cmd->AddToGroup(this->cmdGroupAll);

		// Add new pointer to cmd object at end of array
		cmdA = (Cmd**)MemMang::AppendNewArrayElement(cmdA, numCmds, sizeof(Cmd*));

		// Increment command count
		numCmds++;

		// Store pointer to cmd in array of pointers (Cmd**)
		cmdA[numCmds - 1] = cmd;

	}

	void Comm::RemoveCmd(Cmd* cmd)
	{
		// Remove description
		free(cmd->description);
		// Remove command from memory
		free(cmd);
		// Decrement command count
		numCmds--;
	}

	// Prints out the help info (for all commands)
	void Comm::PrintHelp(Cmd* cmd)
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Print help function called.\r\n");
		#endif

		// Temp buffer for printf() calls in this function
		char tempBuff[100];

		//========== FIND SELECTED GROUP ==========//

		// Points to the selected group
		const char* selectedGroup;

		if(cmd->optionA[1]->isDetected == true)
			// Group option has been provided with help command (help -g groupName)
			selectedGroup = cmd->optionA[1]->value;
		else
		{
			// Default group if none provided (help)
			selectedGroup = this->defaultCmdGroup->name;
		}

		// Title
		Print::cmdLinePrintCallback.Execute("********** LIST OF COMMANDS ***********\r\n");
		Print::cmdLinePrintCallback.Execute("Showing commands for user group: " clide_TERM_TEXT_FORMAT_BOLD);
		Print::cmdLinePrintCallback.Execute(selectedGroup);
		Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_NORMAL "\r\n");

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Print::cmdLinePrintCallback.Execute(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_BOLD);
		#endif

		// Prints command name and description, with padding and truncation if required.
		snprintf(
			tempBuff,
			sizeof(tempBuff),
			"%-" STR(config_PADDING_BEFORE_CMD_IN_HELP) "s%-" STR(config_CMD_PADDING_FOR_HELP) "s%s\r\n",
			"",
			"cmd",
			"description");
		Print::cmdLinePrintCallback.Execute(tempBuff);

		#if(clide_ENABLE_ADV_TEXT_FORMATTING)
			Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_NORMAL);
		#endif


		// Iterate through cmd array and print commands, if they belong to the current command group
		uint32_t x;
		for(x = 0; x < numCmds; x++)
		{
			// Iterate through the command groups for each command
			uint32_t y;
			for(y = 0; y < cmdA[x]->numCmdGroups; y++)
			{
				// Check command belongs to requested group
				if(strcmp(selectedGroup, cmdA[x]->cmdGroupA[y]->name) == 0)
				{
					snprintf(
						tempBuff,
						sizeof(tempBuff),
						"%-" STR(config_PADDING_BEFORE_CMD_IN_HELP) "s",
						"");
					Print::cmdLinePrintCallback.Execute(tempBuff);
					//Print::cmdLinePrintCallback.Execute("\t");
					#if(clide_ENABLE_ADV_TEXT_FORMATTING == 1)
						Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_BOLD);
						snprintf(tempBuff, sizeof(tempBuff), "%-" STR(config_CMD_PADDING_FOR_HELP) "." STR(config_CMD_PADDING_FOR_HELP_MINUS_1) "s", cmdA[x]->name);
						Print::cmdLinePrintCallback.Execute(tempBuff);
						Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_NORMAL);
					#else
						// No special formatting
						Print::cmdLinePrintCallback.Execute(cmdA[x]->name);
					#endif

					// Add tab character
					//Print::cmdLinePrintCallback.Execute("\t");
					// Print description
					Print::cmdLinePrintCallback.Execute(cmdA[x]->description);
					// \r is enough for PuTTy to format onto a newline also
					// (adding \n causes it to add two new lines)
					Print::cmdLinePrintCallback.Execute("\r\n");

					// Quit this for loop, as command has already been printed, don't want to print again
					break;
				}
			}
		}

		// Call callback function
		if(generalHelpRequestedCallback.obj != NULL)
			generalHelpRequestedCallback.Execute((char*)"This argument is not used.");
	}

	// Prints out help for one command
	void Comm::PrintHelpForCmd(Cmd* cmd)
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)
			Print::debugPrintCallback.Execute("CLIDE: Printing help for command.\r\n");
		#endif

		Print::cmdLinePrintCallback.Execute("\r\n**********COMMAND HELP:**********\r\n");

		// CMD NAME AND DESCRIPTION

		// Tabbing in
		Print::cmdLinePrintCallback.Execute("\t");
		#if(clide_ENABLE_ADV_TEXT_FORMATTING == 1)
			Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_BOLD);
			Print::cmdLinePrintCallback.Execute(cmd->name);
			Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_NORMAL);
		#else
			// No advanced text formatting
			Print::cmdLinePrintCallback.Execute(cmd->name);
		#endif

		// Add tab character
		Print::cmdLinePrintCallback.Execute("\t");
		// Print description
		Print::cmdLinePrintCallback.Execute(cmd->description);
		// \r is enough for PuTTy to format onto a newline also
		// (adding \n causes it to add two new lines)
		Print::cmdLinePrintCallback.Execute("\r\n");

		// CMD PARAMETERS

		Print::cmdLinePrintCallback.Execute("Command Parameters:\r\n");


		// Special case if there are no parameters to list
		if(cmd->numParams == 0)
		{
			Print::cmdLinePrintCallback.Execute("\t");
			Print::cmdLinePrintCallback.Execute("NO PARAMS");
			Print::cmdLinePrintCallback.Execute("\r\n");
		}
		else
		{
			// Print top table row 'header'
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Print::cmdLinePrintCallback.Execute(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			#endif
			Print::cmdLinePrintCallback.Execute("\tindex\tdescription\r\n");
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Print::cmdLinePrintCallback.Execute(clide_TERM_TEXT_FORMAT_NORMAL);
			#endif
			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numParams; x++)
			{
				Print::cmdLinePrintCallback.Execute("\t");
				char tempBuff[50];
				snprintf(
					tempBuff,
					sizeof(tempBuff),
					"%" STR(ClidePort_PF_UINT32_T),
					x);
				Print::cmdLinePrintCallback.Execute(tempBuff);
				// Add tab character
				Print::cmdLinePrintCallback.Execute("\t");
				// Print description
				Print::cmdLinePrintCallback.Execute(cmd->paramA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Print::cmdLinePrintCallback.Execute("\r\n");
			}
		}

		// CMD OPTIONS

		Print::cmdLinePrintCallback.Execute("Command Options:\r\n");

		// Special case if there are no parameters to list
		if(cmd->numOptions == 0)
		{
			Print::cmdLinePrintCallback.Execute("\t");
			Print::cmdLinePrintCallback.Execute("NO OPTIONS");
			Print::cmdLinePrintCallback.Execute("\r\n");
		}
		else
		{
			// Print top table row 'header'
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				// gold = Print::cmdLinePrintCallback.Execute("\x1B[33m");
				// Yellow
				Print::cmdLinePrintCallback.Execute(clide_TABLE_HEADER_ROW_COLOUR_CODE);
			#endif
			Print::cmdLinePrintCallback.Execute("\tshort\tlong\tdescription\r\n");
			#if(clide_ENABLE_ADV_TEXT_FORMATTING)
				Print::cmdLinePrintCallback.Execute("\x1B[0m");
			#endif

			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numOptions; x++)
			{
				// Print short option
				Print::cmdLinePrintCallback.Execute("\t");
				char tempShortOption[2];
				tempShortOption[0] = cmd->optionA[x]->shortName;
				tempShortOption[1] = '\0';
				Print::cmdLinePrintCallback.Execute(tempShortOption);

				// Print long option
				Print::cmdLinePrintCallback.Execute("\t");
				Print::cmdLinePrintCallback.Execute(cmd->optionA[x]->longName);
				// Add tab character
				Print::cmdLinePrintCallback.Execute("\t");
				// Print description
				Print::cmdLinePrintCallback.Execute(cmd->optionA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Print::cmdLinePrintCallback.Execute("\r\n");
			}
		}

		// CMD GROUPS

		Print::cmdLinePrintCallback.Execute("Command groups it belongs to:\r\n");

		// Add tab character
		Print::cmdLinePrintCallback.Execute("\t");

		uint32_t x;
		for(x = 0; x < cmd->GetNumCmdGroups(); x++)
		{
			// Print out command group name
			Print::cmdLinePrintCallback.Execute(cmd->cmdGroupA[x]->name);

			// Add space and comma if not last command group name
			if(x != cmd->GetNumCmdGroups() - 1)
				Print::cmdLinePrintCallback.Execute(" ,");
		}

		char tempBuff[50];
			snprintf(
				tempBuff,
				sizeof(tempBuff),
				" (total = %" STR(ClidePort_PF_UINT32_T) ")\r\n",
				cmd->GetNumCmdGroups());
			Print::cmdLinePrintCallback.Execute(tempBuff);

	}

	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//



} // namespace Clide

// EOF
