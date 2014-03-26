//!
//! @file 			Rx.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2012/03/19
//! @last-modified 	2014/01/26
//! @brief 			Clide RX controller. The main logic of the RX (decoding) part of Clide. Commands can be registered with the controller.
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

// User library includes
#include "../lib/slotmachine-cpp/api/Slotmachine.hpp"

// Clide includes
#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/MemMang.hpp"
#include "../include/StringSplit.hpp"
#include "../include/Param.hpp"
#include "../include/Option.hpp"
#include "../include/Cmd.hpp"
#include "../include/Print.hpp"
#include "../include/Comm.hpp"			//!< So the help command can call the HelpCmdCallback() function
#include "../include/Rx.hpp"
#include "../include/GetOpt.hpp"
#include "../include/Log.hpp"




//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{


	using namespace std;

	//===============================================================================================//
	//====================================== PUBLIC METHODS ========================================//
	//===============================================================================================//

	// Constructor
	Rx::Rx()
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Rx constructor called...\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif

		// Initialise class variables
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			// Enable getopt() to print error messages
			GetOpt::opterr = 1;
		#endif

		// Create command for help command (which is currently just a pointer)
		this->cmdHelp = new Cmd("help", &HelpCmdCallback, "Returns information about all registered commands.");

		this->cmdHelp->RegisterOption(new Option('g', NULL, NULL, "Specifies which group to print help with.", true));

		// Default is to show this error (helpful to user)
		this->silenceCmdNotRecognisedError = false;

		// Create help function if enabled
		#if(clide_ENABLE_AUTO_HELP == 1)
			this->RegisterCmd(this->cmdHelp);
		#endif

		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Rx constructor finished.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
	}

	bool Rx::Run(int argc, char* argv[])
	{
		// No need for any pre-processing, pass straight onto Rx::Run2().
		return Rx::Run2(argc, argv);
	}

	bool Rx::Run(char* cmdMsg)
	{
		// Used for various snprintf() function calls
		//char tempBuff[200];

		// Copy the cmd message to a new location in where Rx::Run() can modify the contents
		// (and leave the provided msg untouched)
		char cmdMsgCpyA[strlen(cmdMsg)];
		strcpy(cmdMsgCpyA, cmdMsg);
		// Create
		char* cmdMsgCpyPtr = &cmdMsgCpyA[0];

		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo(
					"CLIDE: Rx.Run() called.\r\n",
					Print::DebugPrintingLevel::GENERAL);
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Received msg = '%s'.\r\n",
				cmdMsg);
			Print::PrintDebugInfo(
					Global::debugBuff,
					Print::DebugPrintingLevel::GENERAL);
		#endif
		
		//=========== RESET PARAMETERS ==============//
		
		//! @brief		Holds the split arguments from the command line
		//! @todo 		Replace with malloc() calls, remove magic numbers
		char* _args[10] = {0};
		
		// Clear args
		memset(_args, '\0', sizeof(_args));
		
		// Reset cmdDetected flag for all commands
		int32_t x;
		for(x = 0; x < numCmds; x++)
		{
			cmdA[x]->isDetected = false;
		}
		
		// Strip all non-alphanumeric characters from the start of the packet
		while(!isalnum(cmdMsgCpyPtr[0]))
		{
			// Check for null string terminator
			if(cmdMsgCpyPtr[0] == '\0')
			{
				Print::PrintToCmdLine("error \"Received command contained no alpha-numeric characters.\"\r\n");
				#if(clide_ENABLE_DEBUG_CODE == 1)
					Print::PrintDebugInfo(
						"CLIDE: WARNING: Received command contained no alpha-numeric characters.\r\n",
						Print::DebugPrintingLevel::GENERAL);
				#endif
				#if(clide_ENABLE_DEBUG_CODE == 1)
					Print::PrintDebugInfo(
						"CLIDE: Rx::Run() finished. Returning false.\r\n",
						Print::DebugPrintingLevel::VERBOSE);
				#endif
				return false;
			} 
			
			#if(clide_ENABLE_DEBUG_CODE == 1)
				snprintf(
					Global::debugBuff, 
					sizeof(Global::debugBuff),
					"CLIDE: Removing char '%c' from rx buffer.\r\n",
					cmdMsg[0]); 
				Print::PrintDebugInfo(
					Global::debugBuff,
					Print::DebugPrintingLevel::VERBOSE);
			#endif
			// Increment message pointer forward over non-alphanumeric char
			cmdMsgCpyPtr++;
		}

		// Split packet. First element is command.
		int numArgs = SplitPacket(cmdMsgCpyPtr, _args);
		
		// Call 2nd part of Run()
		return this->Run2(numArgs, _args);

	}

	int Rx::Run2(uint8_t numArgs, char* _args[])
	{

		int32_t x;

		//! @brief		Array of pointers to the arguments
		char *(_argsPtr[10]);

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

		//=============== CHECK COMMAND IS VALID ==================//
		
		Cmd* foundCmd = this->ValidateCmd(_args[0], cmdA, numCmds);
		
		// Check for registered command
		if(foundCmd == NULL)
		{
			// Only print this error is user has not silenced it
			if(silenceCmdNotRecognisedError == false)
			{
				char tempBuff[100];
				// Received command is not registered (aka invalid/unrecognised)
				#if(clide_ENABLE_AUTO_HELP == 1)
					// Help exists, so tell user that they could type help to get a list of available commands.
					#if(clide_ENABLE_ADV_TEXT_FORMATTING == 1)
						// Special formatting
						snprintf(
							tempBuff,
							sizeof(tempBuff),
							"error \"Command '%s' not recognised. Type %shelp%s to see a list of all the commands.\"\r\n",
							cmdMsg,
							clide_TERM_TEXT_FORMAT_BOLD,
							clide_TERM_TEXT_FORMAT_NORMAL);
						Print::PrintToCmdLine(tempBuff);
					#else
						// No special formatting
						snprintf(
							tempBuff,
							sizeof(tempBuff),
							"error \"Command '%s' not recognised. Type help to see a list of all the commands.\"\r\n",
							cmdMsg);
						Print::PrintToCmdLine(tempBuff);
					#endif
				#else
					// No automatic help, so don't tell the user about something that doesn't exist
					snprintf(
						tempBuff,
						sizeof(tempBuff),
						"error \"Command '%s' not recognised.\"\r\n",
						_args[0]);
					Print::PrintToCmdLine(tempBuff);
				#endif // #if(clide_ENABLE_AUTO_HELP == 1)
			}

			// Log error
			//this->log.logId = LogIds::CMD_NOT_RECOGNISED;
			//this->log.msg = (char*)"Command not recognised.";
			//this->log.severity = Severity::ERROR;

			// Call callback if assigned
			if(this->cmdUnrecogCallback.obj != NULL)
			{
				#if(clide_ENABLE_DEBUG_CODE == 1)
					Print::PrintDebugInfo(
						"CLIDE: .\r\n",
						Print::DebugPrintingLevel::VERBOSE);
				#endif
				this->cmdUnrecogCallback.Execute(_args[0]);
			}

			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo(
					"CLIDE: Rx::Run() finished. Returning false.\r\n",
					Print::DebugPrintingLevel::VERBOSE);
			#endif
			return false;
		}
		
		// Valid command found, set detected flag to true.
		foundCmd->isDetected = true;
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			snprintf(
				Global::debugBuff, 
				sizeof(Global::debugBuff),
				"CLIDE: Num arguments = %i\r\n",
				numArgs); 
			Print::PrintDebugInfo(
				Global::debugBuff,
				Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		// Holds pointers to parameters
		//char *parameters[5];
		
		// Holds the index of the last found option
		//uint8 indexLastOption = 0;
		
		// Clear the isDetected for all options registered with incoming cmd
		// Set true later in function if the option is detected
		for(x = 0; (uint32_t)x < foundCmd->numOptions; x++)
		{
			foundCmd->optionA[x]->isDetected = false;
			foundCmd->optionA[x]->longOptionDetected = 0;
		}
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo(
				"CLIDE: Re-arranged arguments = ",
				Print::DebugPrintingLevel::VERBOSE);

			// Print re-arranged arguments
			uint8_t count = 0;
			while(count < numArgs)
			{
				Print::PrintDebugInfo(_argsPtr[count], Print::DebugPrintingLevel::VERBOSE);
				Print::PrintDebugInfo(", ", Print::DebugPrintingLevel::VERBOSE);
				count++;
			}
			Print::PrintDebugInfo(
				"\r\n",
				Print::DebugPrintingLevel::VERBOSE);
			
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Num registered options = %" STR(ClidePort_PF_UINT32_T) "\r\n",
				foundCmd->numOptions); 
			Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		//==================== BUILD OPTION STRING ===================//
		
		// Size to hold all chars plus one for null char
		char optionString[50] = {0};
		
		this->BuildShortOptionString(optionString, foundCmd);
		
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Option string = '%s'.\r\n",
				optionString);
			Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		//============== USE THE GETOPT FUNCTION =================//
		
		// Reset getopt() for next call of Run()
		// getopt() was only ever designed to be run once
		GetOpt::optind = 0;
		x = 0;
		GetOpt::optarg = NULL;
		GetOpt::optopt = 0;
		
		// Find number of long options in cmd and create struct var
		// for them
		struct GetOpt::option longOptionsA[20];
		
		// Build the struct for getopt_long
		BuildLongOptionStruct(longOptionsA, foundCmd);
		
		// getopt_long stores the option index here.
        int option_index = 0;		
		
		#if(clide_ENABLE_DEBUG_CODE == 1)				
			Print::PrintDebugInfo("CLIDE: Entering getopt_long() loop.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		// getopt() returns -1 when complete
		while((x = GetOpt::getopt_long(numArgs, _argsPtr, optionString, longOptionsA, &option_index)) != -1)
		{
		
			#if(clide_ENABLE_DEBUG_CODE == 1)				
				Print::PrintDebugInfo(
					"CLIDE: getopt_long() has returned with a number that is not -1.\r\n",
					Print::DebugPrintingLevel::VERBOSE);
			#endif
		
			//! @todo Remove magic number
			char optionName[20];
		
			// Store option name
			if(x == 0)
			{
				// Long option received
				//if (long_options[option_index].flag != 0)
                 //break;
				
				#if(clide_ENABLE_DEBUG_CODE == 1)				
					Print::PrintDebugInfo(
						"CLIDE: Searching for set long option flag.\r\n",
						Print::DebugPrintingLevel::VERBOSE);
				#endif
				
				// Search for set flag
				for(x = 0; x < (int32_t)foundCmd->numOptions; x++)
				{
					if(foundCmd->optionA[x]->longOptionDetected == 1)
					{
						// Make sure it hasn't already been detected, if it has,
						// ignore and continue searching for one that hasn't. getopt_long()
						// sets all previously discovered flags high everytime it is run,
						// so this gets around this problem!
						if(foundCmd->optionA[x]->isDetected == false)
						{
							#if(clide_ENABLE_DEBUG_CODE == 1)
								snprintf (
									Global::debugBuff,
									sizeof(Global::debugBuff),
									"CLIDE: Long option '%s' found with optarg '%s'.\r\n",
									foundCmd->optionA[x]->longName,
									GetOpt::optarg);
								Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
							#endif
						
							// Copy option name
							strcpy(optionName, foundCmd->optionA[x]->longName);
							
							break;
						}
						
						// Only one longOptionDetected in optionA should be set, so can safely break loop here.
						//break;
					}
					
					// Set flag back to false, so that this code works next time through for
					// a different option.
					foundCmd->optionA[x]->longOptionDetected = 0;
					
				}
				
			}
			else if(x == '?')
			{
				#if(clide_ENABLE_DEBUG_CODE == 1)
					snprintf (
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: ERROR: getopt_long() returned '?'. Did not recognise received option '%s' or missing option value. Num args = '%u'. Option string = '%s'.\r\n",
						_argsPtr[GetOpt::optind - 1],
						numArgs,
						optionString);
					Print::PrintError(Global::debugBuff);
					snprintf (
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: _argsPtr[0] = '%s'. _argsPtr[1] = '%s'. _argsPtr[2] = '%s'. _argsPtr[3] = '%s'.\r\n",
						_argsPtr[0],
						_argsPtr[1],
						_argsPtr[2],
						_argsPtr[3]);
					Print::PrintError(Global::debugBuff);
				#endif
				
				continue;
			}
			else
			{
				#if(clide_ENABLE_DEBUG_CODE == 1)
					snprintf (
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: Short option '%" STR(ClidePort_PF_CHAR_T) "' found with optarg '%s'.\r\n",
						x,
						GetOpt::optarg);
					Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
				#endif
				// Short option received
				optionName[0] = x;
				optionName[1] = '\0';
			}
			
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
					#if(clide_ENABLE_DEBUG_CODE == 1)		
						if(foundOption->shortName != '\0')
						{
							snprintf (
									Global::debugBuff,
									sizeof(Global::debugBuff),
									"CLIDE: Setting isDetected for option (shortName = '%c', longName = '%s') to 'true'.\r\n",
									foundOption->shortName,
									foundOption->longName);							
							Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
						}
						else
						{
							snprintf (
									Global::debugBuff,
									sizeof(Global::debugBuff),
									"CLIDE: Setting isDetected for option (shortName = 'null', longName = '%s') to 'true'.\r\n",
									foundOption->longName);							
							Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
						}
					#endif
					foundOption->isDetected = true;
				
					// Special help case
					if(foundOption->shortName == 'h')
					{
						#if(clide_ENABLE_DEBUG_CODE == 1)
							Print::PrintDebugInfo(
								"CLIDE: Help option detected. Printing help...\r\n",
								Print::DebugPrintingLevel::VERBOSE);
						#endif

						// Print help
						this->PrintHelpForCmd(foundCmd);

						// Help is a special option. Once it is discovered in the command, no further processing is done, so exit
						return true;
						
					}
					// Only run callback if it has been assigned, and not the help case
					//! @todo Get rid of 20
					else
					{
					
						// Save option value if one
						if(foundOption->associatedValue == true)
						{
							#if(clide_ENABLE_DEBUG_CODE == 1)	
								snprintf (
									Global::debugBuff,
									sizeof(Global::debugBuff),
									"CLIDE: Option should have associated value. Found value = '%s'.\r\n",
									GetOpt::optarg);							
								Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
							#endif
							if(GetOpt::optarg != NULL)
							{
								#if(clide_ENABLE_DEBUG_CODE == 1)
									snprintf (
										Global::debugBuff,
										sizeof(Global::debugBuff),
										"CLIDE: Copying '%s' into Option->value.\r\n",
										GetOpt::optarg);
									Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
								#endif
								strcpy(foundOption->value, GetOpt::optarg);
							}
							else
							{
								// Error, option should have has a value associated with it.
								#if(clide_ENABLE_DEBUG_CODE == 1)	
									snprintf (
										Global::debugBuff,
										sizeof(Global::debugBuff),
										"%s",
										"CLIDE: ERROR: Option had no associated value but associatedValue was set to 'true'.\r\n");							
									Print::PrintError(Global::debugBuff);
								#endif
							}	
						}
					
						//! @todo Remove this callback stuff for options
						if(foundOption->callBackFunc != NULL)
						{
							foundOption->callBackFunc((char*)"20");	
						}
					}	
				}
				else
				{
					// Error message
					#if(clide_ENABLE_DEBUG_CODE == 1)
						Print::PrintError("CLIDE: ERROR - Option '");
						Print::PrintError(_argsPtr[GetOpt::optind-1]);
						Print::PrintError("' not registered with command.\"\r\n");
					#endif
					Print::PrintToCmdLine("error \"Option '");
					Print::PrintToCmdLine(_argsPtr[GetOpt::optind-1]);
					Print::PrintToCmdLine("' not registered with command.\"\r\n");
				}
					
			}

			/*
			#if(clide_ENABLE_DEBUG_CODE == 1)
				snprintf(
					tempBuff,
					sizeof(tempBuff),
					"CLIDE: Found option: Name = '%c'. Option Argument = '%s'. Index = '%i'\r\n",
					x,
					optarg,
					optind); 
				Print::PrintDebugInfo(tempBuff);
			#endif
			*/
		}
		
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			snprintf (
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: GetOpt() finished (returned with -1). optind = '%i'.\r\n",
				GetOpt::optind);							
			Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Arguments = ", Print::DebugPrintingLevel::VERBOSE);
			// Print arguments
			count = 0;
			while(count < numArgs)
			{
				Print::PrintDebugInfo(_args[count], Print::DebugPrintingLevel::VERBOSE);
				Print::PrintDebugInfo(", ", Print::DebugPrintingLevel::VERBOSE);
				count++;
			}
			Print::PrintDebugInfo("\r\n", Print::DebugPrintingLevel::VERBOSE);
			
			Print::PrintDebugInfo("CLIDE: Re-arranged arguments = ", Print::DebugPrintingLevel::VERBOSE);
			// Print re-arranged arguments
			count = 0;
			while(count < numArgs)
			{
				Print::PrintDebugInfo(_argsPtr[count], Print::DebugPrintingLevel::VERBOSE);
				Print::PrintDebugInfo(", ", Print::DebugPrintingLevel::VERBOSE);
				count++;
			}
			Print::PrintDebugInfo("\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		//============= VALIDATE/PROCESS PARAMETERS =============//
		
		// Validate that there are the correct number of parameters
		if((uint32_t)(numArgs - GetOpt::optind) != foundCmd->numParams)
		{
			Print::PrintToCmdLine("error \"Num. of received parameters does not match num. registered for cmd.\"\r\n");
			#if(clide_ENABLE_DEBUG_CODE == 1)
				snprintf (
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: ERROR: Num. of received parameters ('%" STR(ClidePort_PF_UINT32_T)
					"') for cmd '%s' does not match num. registered ('%" STR(ClidePort_PF_UINT32_T) "'). numArgs = '%u'. optind = '%i'.\r\n",
					(uint32_t)(numArgs - GetOpt::optind),
					foundCmd->name,
					foundCmd->numParams,
					numArgs,
					GetOpt::optind);							
				Print::PrintError(Global::debugBuff);
			#endif
			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo("CLIDE: Rx::Run() finished. Returning false.\r\n", Print::DebugPrintingLevel::VERBOSE);
			#endif
			return false;
		}
		
		// Copy parameters into cmd string
		for(x = 0; (uint32_t)x < foundCmd->numParams; x++)
		{
			strcpy(foundCmd->paramA[x]->value, _argsPtr[GetOpt::optind + x]);
		}
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Parameters = ", Print::DebugPrintingLevel::VERBOSE);
			// Get parameters
			if(GetOpt::optind == numArgs)
				Print::PrintDebugInfo("(none)", Print::DebugPrintingLevel::VERBOSE);
			else
			{
				for(count = GetOpt::optind; count < numArgs; count++)
				{
					Print::PrintDebugInfo(_argsPtr[count], Print::DebugPrintingLevel::VERBOSE);
					Print::PrintDebugInfo(", ", Print::DebugPrintingLevel::VERBOSE);
				}
			}
			Print::PrintDebugInfo("\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		// Make sure callbacks are the last thing to do in Run()
		if((foundCmd->functionCallback != NULL) || foundCmd->methodCallback.IsValid())
		{
			// Check to see if a call-back function has been assigned
			if(foundCmd->functionCallback != NULL)
			{
				// Execute command callback function
				foundCmd->functionCallback(foundCmd);
			}

			if(foundCmd->methodCallback.IsValid() == true)
			{
				// Call method callback
				foundCmd->methodCallback.Execute(foundCmd);
			}

		}
		else
		{
			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo("CLIDE: Command callback(s) were NULL, so no function/method called.\r\n", Print::DebugPrintingLevel::VERBOSE);
			#endif
		}

		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Rx::Run() finished. Returning true.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		return true;
	}

	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	int Rx::SplitPacket(char* packet, char* argv[])
	{

		// Split string into arguments using white space as the seperator
		char* ptrToArgument = StringSplit::Run(packet, " ");
		
		// Keep track of the number of arguments found
		uint8_t argCount = 0;

		while(ptrToArgument != 0)
		{
			// Save pointer to start of string
			argv[argCount] = ptrToArgument;
			
			// Repeat. Pass in null as first parameter after first call
			ptrToArgument = StringSplit::Run(0, " ");
			argCount++;
		}
		
		// Write 0 to last args element
		//args[argCount][0] = '\0';
		
		return argCount;
	}

	Cmd* Rx::ValidateCmd(char* cmdName, Cmd** cmdA, uint8_t numCmds)
	{
		uint8_t x = 0;
		
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			Print::PrintDebugInfo("CLIDE: Validating command...\r\n", Print::DebugPrintingLevel::VERBOSE);
			Print::PrintDebugInfo("CLIDE: Input = ", Print::DebugPrintingLevel::VERBOSE);
			Print::PrintDebugInfo(cmdName, Print::DebugPrintingLevel::VERBOSE);
			Print::PrintDebugInfo("\r\n", Print::DebugPrintingLevel::VERBOSE);
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Num. registered cmds = %u\r\n",
				numCmds);
			Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		for(x = 0; x < numCmds; x++)
		{
			uint32_t val = strcmp(cmdName, cmdA[x]->name);
			#if(clide_ENABLE_DEBUG_CODE == 1)
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Compared name = '%s', compared value = '%" STR(ClidePort_PF_UINT32_T) "'.\r\n",
					cmdA[x]->name,
					(uint32_t)val);
				Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
			#endif
			if(val == 0)
			{
				// Match found, return pointer to the discovered cmd structure
				#if(clide_ENABLE_DEBUG_CODE == 1)	
					Print::PrintDebugInfo("CLIDE: Command recognised.\r\n", Print::DebugPrintingLevel::VERBOSE);
				#endif
				return cmdA[x];
			}
		}
		// No match found, return NULL
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			Print::PrintDebugInfo("CLIDE: Command not recognised.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		return NULL;
	}

	Option* Rx::ValidateOption(Cmd *detectedCmd, char* optionName)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Validating option.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		uint8_t x = 0;
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Received option = '%s'.\r\n",
				optionName);
			Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
		#endif
		// Iterate through all registered options for detected command
		for(x = 0; x < detectedCmd->numOptions; x++)
		{
			// Do not initialise as 0!
			uint8_t val = 1;
			// Compare received option name with all the registered option names in the detected command
			if(optionName[1] == '\0')
			{
				// Option is short
				if(optionName[0] == detectedCmd->optionA[x]->shortName)
					val = 0;
				else
					val = 1;
					
				#if(clide_ENABLE_DEBUG_CODE == 1)
					snprintf(
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: Compared received option '%s' with short name '%c'.\r\n",
						optionName,
						detectedCmd->optionA[x]->shortName);									
					Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
				#endif
			}	
			else if(detectedCmd->optionA[x]->longName != NULL)
			{
				// Option is long
				val = strcmp(optionName, detectedCmd->optionA[x]->longName);
				#if(clide_ENABLE_DEBUG_CODE == 1)
					snprintf(
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: Compared received option '%s' with long name '%s'.\r\n",
						optionName,
						detectedCmd->optionA[x]->longName);									
					Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
				#endif
			}
					
			if(val == 0)
			{
				// Match found, return found option
				#if(clide_ENABLE_DEBUG_CODE == 1)
					Print::PrintDebugInfo("CLIDE: Option recognised.\r\n", Print::DebugPrintingLevel::VERBOSE);
				#endif
				return detectedCmd->optionA[x];
			}
		}
		// No match found, return NULL
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Option not recognised.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		return NULL;
	}

	void Rx::BuildShortOptionString(char* optionString, Cmd* cmd)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Building short option string...\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		uint32_t x;
		uint32_t optionStringPos = 0;
		for(x = 0; x < cmd->numOptions; x++)
		{
			// Make sure short name exists
			if(cmd->optionA[x]->shortName != '\0')
			{
				// Get character from each name
				optionString[optionStringPos++] = cmd->optionA[x]->shortName;
				// Add ':' if option is expected with associated value
				if(cmd->optionA[x]->associatedValue == true)
				{
					#if(clide_ENABLE_DEBUG_CODE == 1)
						Print::PrintDebugInfo(
							"CLIDE: associatedValue = 'true'. Adding ':' char to option string.\r\n",
							Print::DebugPrintingLevel::VERBOSE);
					#endif
					optionString[optionStringPos++] = ':';
				}
			}
		}
		// Add null character to terminate string
		optionString[optionStringPos++] = '\0';
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo(
				"CLIDE: Finished building short option string...\r\n",
				Print::DebugPrintingLevel::VERBOSE);
		#endif
	}
	
	void Rx::BuildLongOptionStruct(GetOpt::option* longOptStructA, Cmd* cmd)
	{
		// Build the structure required for long option processing
		
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Building long option structure...\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		uint32_t x;
		uint32_t longOptionIndex = 0;
		// Iterate through all long-options registered with command
		for(x = 0; x < cmd->numOptions; x++)
		{
			// If no long name in option, skip to next one
			if(cmd->optionA[x]->longName == NULL)
			{
				#if(clide_ENABLE_DEBUG_CODE == 1)
					snprintf(
						Global::debugBuff,
						sizeof(Global::debugBuff),
						"CLIDE: Option '%c' is not a long-option. Skipping.\r\n",
						cmd->optionA[x]->shortName);
					Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
				#endif
				continue;
			}
			
			#if(clide_ENABLE_DEBUG_CODE == 1)
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Option '%s' is a long-option.\r\n",
					cmd->optionA[x]->longName);
				Print::PrintDebugInfo(Global::debugBuff, Print::DebugPrintingLevel::VERBOSE);
			#endif
		
			// Copy all variables to structure.
			
			// 1) Name
			longOptStructA[longOptionIndex].name = cmd->optionA[x]->longName;
			//longOptStructA[0].name = "long1";
			
			// 2) Has Argument?
			// Optional argument not supported
			if(cmd->optionA[x]->associatedValue)
				longOptStructA[longOptionIndex].has_arg = required_argument;
			else
				longOptStructA[longOptionIndex].has_arg = no_argument;
			
			// 3) Detected flag 
			longOptStructA[longOptionIndex].flag = &cmd->optionA[x]->longOptionDetected;
			
			// 4) Detected flag value
			longOptStructA[longOptionIndex].val = 1;
			
			longOptionIndex++;
		}
	
		// Zero-element at end of array
		longOptStructA[longOptionIndex].name = 0;
		longOptStructA[longOptionIndex].has_arg = 0;
		longOptStructA[longOptionIndex].flag = 0;
		longOptStructA[longOptionIndex].val = 0;
	
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Finished building long option structure.\r\n", Print::DebugPrintingLevel::VERBOSE);
		#endif
	
	}

} // namespace Clide

// EOF
