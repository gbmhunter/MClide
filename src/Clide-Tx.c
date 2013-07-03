//!
//! @file 		Clide-Tx.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2012/03/19
//! @brief 		Clide TX controller. The main logic of the TX (sending)
//!				part of Clide.
//! @details
//!				See README.rst in root dir.

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
#include <getopt.h>		// getopt()	
#include <cstring>		// memset()

// User includes
#include "./include/MemMang.h"
#include "./include/PowerString-Split.h"
#include "./include/Clide-Config.h"
#include "./include/Clide-Param.h"
#include "./include/Clide-Option.h"
#include "./include/Clide-Cmd.h"
#include "./include/Clide-Port.h"
#include "./include/Clide-Tx.h"


//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	using namespace std;

	//===============================================================================================//
	//==================================== PRIVATE DEFINES ==========================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//=================================== PRIVATE TYPEDEF's =========================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//============================= PRIVATE VARIABLES/STRUCTURES ====================================//
	//===============================================================================================//




	//! @brief		Holds the split arguments from the command line
	//! @todo 		Replace with malloc() calls, remove magic numbers
	static char _args[10][clideMAX_STRING_LENGTH];

	static char _paramA[10][10];

	static uint8_t _paramAIndex = 0;

	//! @brief		Array of pointers to the arguments
	static char *(_argsPtr[10]);

	//! @todo Remove
	//Cmd _cmdTest;

	//===============================================================================================//
	//================================== PRIVATE FUNCTION PROTOTYPES ================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//===================================== PUBLIC FUNCTIONS ========================================//
	//===============================================================================================//

	// Constructor
	Tx::Tx()
	{
		this->numCmds = 0;
		this->cmdA = NULL;
	}

	void Tx::Init()
	{
		ResetArgsPointer();
			 
		  
	}

	// Reset args pointer (to undo what getopt does)
	void Tx::ResetArgsPointer()
	{
		// Maps args pointer to second element (first is command name),
		// and not used by getopt
		_argsPtr[0] = _args[0];
		_argsPtr[1] = _args[1];
		_argsPtr[2] = _args[2];
		_argsPtr[3] = _args[3];
		_argsPtr[4] = _args[4];
		_argsPtr[5] = _args[5];
		_argsPtr[6] = _args[6];
		_argsPtr[7] = _args[7];
		_argsPtr[8] = _args[8];
		_argsPtr[9] = _args[9];
	}

	bool Tx::Run(char* cmdMsg)
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)
			DebugPrint("CLIDE: Received msg: \"");
			DebugPrint(cmdMsg);
			DebugPrint("\"\r\n");
		#endif
		
		
		#if(clideDEBUG_PRINT_ANY == 1)
			// Used for various snprintf() function calls
			char tempBuff[50];
		#endif
		
		//=========== RESET PARAMETERS ==============//
		
		// Reset paramter index
		_paramAIndex = 0;
		
		// Clear parameters
		memset(_paramA, '\0', sizeof(_paramA));
		
		// Clear args
		memset(_args, '\0', sizeof(_args));
		
		// Reset getopt() for next call of Run()
		// getopt() was only ever designed to be run once
		optind = 1;
		
		// Reset args pointers (getopt() rearranges the pointers)
		ResetArgsPointer();
		
		// Strip all non-alphanumeric characters from the start of the packet
		while(!isalnum(cmdMsg[0]) || cmdMsg[0] == '\0')
		{
			// Increment message pointer forward over non-alphanumeric char
			cmdMsg++;
		}

		// Split packet. First element is command.
		int numArgs = SplitPacket(cmdMsg, _args);
		
		//=============== CHECK COMMAND IS VALID ==================//
		
		Cmd* foundCmd = ValidateCmd(_args[0], cmdA, numCmds);
		
		// Check for registered command
		if(foundCmd == NULL)
		{
			Port::CmdLinePrint("ERROR! Command not recognised.\r\n");
			return false;
		}
		
		#if(clideDEBUG_PRINT_GENERAL == 1)
			snprintf(tempBuff, sizeof(tempBuff), "CLIDE: Num args = %i\r\n", numArgs); 
			DebugPrint(tempBuff);
		#endif
		
		// Holds pointers to parameters
		//char *parameters[5];
		
		// Holds the index of the last found option
		//uint8 indexLastOption = 0;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Printing arguments pointer...\r\n");
			// Print re-arranged arguments
			uint8 count = 0;
			while(*_argsPtr[count] != '\0')
			{
				DebugPrint(_argsPtr[count]);
				DebugPrint(", ");
				count++;
			}
			DebugPrint("\r\n");
			
			snprintf(tempBuff, sizeof(tempBuff), "CLIDE: Num registered options = %lu\r\n", foundCmd->numOptions); 
			DebugPrint(tempBuff);
			
			DebugPrint("CLIDE: Printing found options...\r\n");
		
		#endif
		
		//==================== BUILD OPTION STRING ===================//
		
		// Size to hold all chars plus one for null char
		char optionString[foundCmd->numOptions + 1];
		
		this->BuildOptionString(optionString, foundCmd);
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Option string = ");
			DebugPrint(optionString);
			DebugPrint("\r\n");
		#endif
		
		//============== USE THE GETOPT FUNCTION =================//
		
		// Find options
		int x;
		
		// getopt() returns -1 when complete
		while((x = getopt(numArgs, _argsPtr, optionString)) != -1)
		{
			// Hack because getopt() only support single char options
			//! @todo use getopt_long version instead
			char optionName[2];
			optionName[0] = x;
			optionName[1] = '\0';
			
			// Only try and validate options if there are registered options for this command,
			// else skip
			if(foundCmd->numOptions > 0)
			{
				
				// Check for option
				Option* foundOption = ValidateOption(foundCmd, optionName);
				// If option found, call assigned call-back function
				//! @todo Implement properly
				if(foundOption != NULL)
				{
					// Special help case
					if(foundOption->name[0] == 'h')
					{
						this->PrintHelpForCmd(foundCmd);
						// No further processing required, exit
						return true;
						
					}
					// Only run callback if it has been assigned, and not the help case
					else if(foundOption->callBackFunc != NULL)
						foundOption->callBackFunc((char*)"20");	
				}
					
			}

			#if(clideDEBUG_PRINT_VERBOSE == 1)
				// Debug stuff
				UartDebug::PutChar(x);
				DebugPrint(optarg);
				snprintf(tempBuff, sizeof(tempBuff), " Index=%i\r\n", optind); 
				DebugPrint(tempBuff);
			#endif
		}
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			// Insert new line
			DebugPrint("\r\n");
		#endif
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Printing arguments...\r\n");
			// Print arguments
			count = 0;
			while(_args[count][0] != '\0')
			{
				DebugPrint(_args[count]);
				DebugPrint(", ");
				count++;
			}
			DebugPrint("\r\n");
			
			DebugPrint("CLIDE: Printing re-arranged arguments...\r\n");
			// Print re-arranged arguments
			count = 0;
			while(*_argsPtr[count] != '\0')
			{
				DebugPrint(_argsPtr[count]);
				DebugPrint(", ");
				count++;
			}
			DebugPrint("\r\n");
		#endif
		
		//============= VALIDATE/PROCESS PARAMETERS =============//
		
		// Validate that there are the correct number of parameters
		if((uint32_t)(numArgs - optind) != foundCmd->numParams)
		{
			Port::CmdLinePrint("CLIDE: Error: Num. of received parameters does not match num. registered for cmd.\r\n");
			#if(clideDEBUG_PRINT_ERROR == 1)
				Port::DebugPrint("CLIDE: Error: Num. of received parameters does not match num. registered for cmd.\r\n");
			#endif
			return false;
		}
		
		// Copy parameters into cmd string
		for(x = 0; x < foundCmd->numParams; x++)
		{
			strcpy(foundCmd->paramA[x]->value, _argsPtr[optind + x]);
		}
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Printing parameters...\r\n");
			// Get parameters
			for(count = optind; count < numArgs; count++)
			{
				DebugPrint(_argsPtr[count]);
				DebugPrint(", ");
			}
			DebugPrint("\r\n");
		#endif
		
		// Execute command callback function
		// Make sure this is the last thing to do in Run()
		foundCmd->callBackFunc(foundCmd);

		return true;
	}


	void Tx::RegisterCmd(Cmd* cmd)
	{
		// Add new pointer to cmd object at end of array
		cmdA = (Cmd**)MemMang::AppendNewArrayElement(cmdA, numCmds, sizeof(Cmd*));
		
		numCmds++;
		
		// Store pointer to cmd in array of pointers (Cmd**)
		cmdA[numCmds - 1] = cmd;
		
	}

	void Tx::RemoveCmd(Cmd* cmd)
	{
		// Remove description
		free(cmd->description);
		// Remove command from memory
		free(cmd);
		// Decrement command count
		numCmds--;
	}

	// Prints out the help info
	void Tx::PrintHelp()
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)	
			DebugPrint("CLIDE: Print help function called.");
		#endif
		
		// Title
		Port::CmdLinePrint("List of commands:\r\n");
		
		// Iterate through cmd array and print commands
		uint32_t x;
		for(x = 0; x < numCmds; x++)
		{
			Port::CmdLinePrint(cmdA[x]->name);
			// Add tab character
			Port::CmdLinePrint("\t- ");
			// Print description
			Port::CmdLinePrint(cmdA[x]->description);
			// \r is enough for PuTTy to format onto a newline also
			// (adding \n causes it to add two new lines)
			Port::CmdLinePrint("\r");
		}
	}


	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//


	int Tx::SplitPacket(char* packet, char(*args)[clideMAX_STRING_LENGTH])
	{

		// Split string into arguments using white space as the seperator
		char* ptrToArgument = PowerString::Split::Run(packet, " ");
		
		uint8_t argCount = 0;
		while(ptrToArgument != 0)
		{
			// Copy argument into argument array
			strcpy(args[argCount], ptrToArgument);
			
			// Repeat. Pass in null as first parameter after first call
			ptrToArgument = PowerString::Split::Run(0, " ");
			argCount++;
		}
		
		// Write 0 to last args element
		args[argCount][0] = '\0';
		
		return argCount;
	}


	Cmd* Tx::ValidateCmd(char* cmdName, Cmd** cmdA, uint8_t numCmds)
	{
		uint8_t x = 0;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			char tempBuff[50];
			DebugPrint("CLIDE: Validating command...\r\n");
			DebugPrint("CLIDE: Input = ");
			DebugPrint(cmdName);
			DebugPrint("\r\n");
			snprintf(tempBuff, sizeof(tempBuff), "CLIDE: Num. registered cmds = %u\r\n", numCmds);
			DebugPrint(tempBuff);
		#endif
		
		for(x = 0; x < numCmds; x++)
		{
			uint8_t val = strcmp(cmdName, cmdA[x]->name);
			#if(clideDEBUG_PRINT_VERBOSE == 1)
				DebugPrint("CLIDE: Compared Name = ");
				DebugPrint(cmdA[x]->name);
				DebugPrint("\r\n");
				snprintf(tempBuff, sizeof(tempBuff), "CLIDE: Compared value = %u\r\n", val);
				DebugPrint(tempBuff);
			#endif
			if(val == 0)
			{
				// Match found, return pointer to the discovered cmd structure
				#if(clideDEBUG_PRINT_VERBOSE == 1)	
					DebugPrint("CLIDE: Command recognised.\r\n");
				#endif
				return cmdA[x];
			}
		}
		// No match found, return NULL
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			DebugPrint("CLIDE: Command not recognised.\r\n");
		#endif
		
		return NULL;
	}


	Option* Tx::ValidateOption(Cmd *detectedCmd, char* optionName)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Validating option.\r\n");
		#endif
		
		uint8_t x = 0;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			char tempBuff[50];
			
			DebugPrint("CLIDE: Received option = ");
			DebugPrint(optionName);
			DebugPrint("\r\n");
			
			DebugPrint("CLIDE: Registered option = ");
			DebugPrint(detectedCmd->optionA[0]->name);
			DebugPrint("\r\n");
		#endif
		// Iterate through all registered options for detected command
		for(x = 0; x < detectedCmd->numOptions; x++)
		{
			// Compare received option name with all the registered option names in the detected command
			uint8_t val = strcmp(optionName, detectedCmd->optionA[x]->name);
			#if(clideDEBUG_PRINT_VERBOSE == 1)
				snprintf(tempBuff, sizeof(tempBuff), "CLIDE: Value = %u\r\n", val);
				DebugPrint(tempBuff);
			#endif
			if(val == 0)
			{
				// Match found, return found option
				#if(clideDEBUG_PRINT_VERBOSE == 1)
					DebugPrint("CLIDE: Option recognised.\r\n");
				#endif
				return detectedCmd->optionA[x];
			}
		}
		// No match found, return NULL
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Option not recognised.\r\n");
		#endif
		return NULL;
	}

	void Tx::BuildOptionString(char* optionString, Cmd* cmd)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			DebugPrint("CLIDE: Building option string...\r\n");
		#endif
		
		uint32_t x;
		for(x = 0; x < cmd->numOptions; x++)
		{
			// Get character from each name
			optionString[x] = cmd->optionA[x]->name[0];
		}
		// Add null character to terminate string
		optionString[x] = '\0';
	}

	void Tx::PrintHelpForCmd(Cmd* cmd)
	{
		#if(clideDEBUG_PRINT_GENERAL == 1)	
			DebugPrint("CLIDE: Printing help for command.\r\n");
		#endif
		
		Port::CmdLinePrint("COMMAND HELP:\r\r");
		
		// CMD NAME AND DESCRIPTION
		
		Port::CmdLinePrint(cmd->name);
		// Add tab character
		Port::CmdLinePrint("\t- ");
		// Print description
		Port::CmdLinePrint(cmd->description);
		// \r is enough for PuTTy to format onto a newline also
		// (adding \n causes it to add two new lines)
		Port::CmdLinePrint("\r\r");
		
		// CMD PARAMETERS
		
		Port::CmdLinePrint("Command Parameters:\r");
		
		// Special case if there are no parameters to list
		if(cmd->numParams == 0)
		{
			Port::CmdLinePrint("\t");
			Port::CmdLinePrint("NO PARAMS");
			Port::CmdLinePrint("\r");
		}
		else
		{
			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numParams; x++)
			{
				Port::CmdLinePrint("\t");
				char tempBuff[50];
				snprintf(tempBuff, sizeof(tempBuff), "%" STR(ClidePort_PF_UINT32_T), x);
				Port::CmdLinePrint(tempBuff);
				// Add tab character
				Port::CmdLinePrint("\t- ");
				// Print description
				Port::CmdLinePrint(cmd->paramA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Port::CmdLinePrint("\r");
			}
		}
		
		// CMD OPTIONS
		
		Port::CmdLinePrint("Command Options:\r");
		
		// Special case if there are no parameters to list
		if(cmd->numOptions == 0)
		{
			Port::CmdLinePrint("\t");
			Port::CmdLinePrint("NO OPTIONS");
			Port::CmdLinePrint("\r");
		}
		else
		{
			// Iterate through cmd array and print commands
			uint32_t x;
			for(x = 0; x < cmd->numOptions; x++)
			{
				Port::CmdLinePrint("\t");
				Port::CmdLinePrint(cmd->optionA[x]->name);
				// Add tab character
				Port::CmdLinePrint("\t- ");
				// Print description
				Port::CmdLinePrint(cmd->optionA[x]->description);
				// \r is enough for PuTTy to format onto a newline also
				// (adding \n causes it to add two new lines)
				Port::CmdLinePrint("\r");
			}
		}
		
	}

} // namespace Clide