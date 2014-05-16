//!
//! @file 			Cmd.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2014/05/16
//! @brief 			Command-line style communications protocol
//! @details
//!				See README.rst in repo root dir for more info.

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
#include <string.h>		// strlen()

// User includes
#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/Print.hpp"
#include "../include/Option.hpp"
#include "../include/Param.hpp"
#include "../include/Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//

	// Constructor
	Cmd::Cmd(std::string name, bool (*callBackFunc)(Cmd* foundCmd), std::string description)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			// Description too long, do not save it
			Print::PrintDebugInfo(
				"CLIDE: Cmd constructor called.\r\n",
				Print::DebugPrintingLevel::VERBOSE);
		#endif

		// CALLBACK
		this->functionCallback = callBackFunc;

		// Call init function
		this->Init(name, description);

	}

	// Constructor
	Cmd::Cmd(std::string name, SlotMachine::Callback<void, Cmd*> methodCallback, std::string description)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			// Description too long, do not save it
			Print::PrintDebugInfo("CLIDE: Cmd constructor called.\r\n",
				Print::DebugPrintingLevel::VERBOSE);
		#endif

		this->methodCallback = methodCallback;

		// Must set the function callback to NULL if not given, so that
		// it is not called (would cause segmentation fault)
		this->functionCallback = NULL;

		// Call init function
		this->Init(name, description);
	}

	void Cmd::Init(std::string name, std::string description)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Cmd::Init() called.\r\n",
				Print::DebugPrintingLevel::VERBOSE);
		#endif

		// NAME

		this->name = name;
		
		// DECRIPTION
		
		this->description = description;
		
		// HELP

		#if(clide_ENABLE_AUTO_HELP == 1)
			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo("CLIDE: Registering help option.\r\n", Print::DebugPrintingLevel::GENERAL);
			#endif
			// HELP OPTION
			Option* help = new Option('h', "help", NULL, "Prints help for the command.", false);

			if(help == NULL)
				throw "CLIDE: ERROR: malloc() for help option failed in Clide::Cmd constructor.";

			this->RegisterOption(help);
		#endif
		
		// DETECTED FLAG
		this->isDetected = false;
		
		// PARENT COMM OBJECT

		// Set to null, this gets assigned when the command is registered.
		// Will be either set to a Clide::Tx or Clide::Rx object
		this->parentComm = NULL;

		#if(clide_ENABLE_DEBUG_CODE == 1)
			// Description too long, do not save it
			Print::PrintDebugInfo("CLIDE: Cmd constructor finished.\r\n",
				Print::DebugPrintingLevel::VERBOSE);
		#endif

	}

	Cmd::~Cmd()
	{
		// Destructor
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			Print::PrintDebugInfo("CLIDE: Cmd destructor called.\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		// Free up parameter and option memory
		//free(paramA);
		//free(optionA);
	}
	
	void Cmd::RegisterParam(Param* param)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			// Description too long, do not save it
			Print::PrintDebugInfo("CLIDE: Registering parameter...\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif

		//this->numParams = 0;
			
		// MALLOC
		//this->paramA = (Param**)MemMang::AppendNewArrayElement(this->paramA, this->numParams, sizeof(Param*));
		this->paramA.push_back(param);
		/*
		if(this->paramA == NULL)
		{
			#if(clide_ENABLE_DEBUG_CODE == 1)	
				// Description too long, do not save it
				Print::PrintError("CLIDE: ERROR - Malloc failed while registering parameter.\r\n");
			#endif
			return;	
		}
		*/
		// Increase parameter count
		//this->numParams++;
		
		// Remember the pointer
		//paramA[numParams - 1] = param;
	}

	// Register option
	void Cmd::RegisterOption(Option* option)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			// Description too long, do not save it
			Print::PrintDebugInfo("CLIDE: Registering option...\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif

		// Create option pointer at end of option pointer array.
		//this->optionA = (Option**)MemMang::AppendNewArrayElement(this->optionA, this->numOptions, sizeof(Option*));
		this->optionA.push_back(option);

		/*
		if(this->optionA == NULL)
		{
			#if(clide_ENABLE_DEBUG_CODE == 1)
				// Description too long, do not save it
				Print::PrintError("CLIDE: ERROR - Malloc failed while registering option.\r\n");
			#endif
			return;
		}*/

		// Increase option count
		//this->numOptions++;
		
		// Remember option
		//optionA[this->numOptions - 1] = option;
		
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			if(optionA[this->optionA.size() - 1]->shortName != '\0')
			{
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Option short name = '%c'. Option long name = '%s'.\r\n",
					optionA[this->optionA.size() - 1]->shortName,
					optionA[this->optionA.size() - 1]->longName.c_str());
			}
			else
			{
				snprintf(
					Global::debugBuff,
					sizeof(Global::debugBuff),
					"CLIDE: Option short name = '%s'. Option long name = '%s'.\r\n",
					"none",
					optionA[this->optionA.size() - 1]->longName.c_str());
			}
			
			Print::PrintDebugInfo(Global::debugBuff,
					Print::DebugPrintingLevel::VERBOSE);
			
		#endif
	}

	Option* Cmd::FindOptionByShortName(char shortOptionName)
	{
		for(uint32_t x = 0; x < this->optionA.size(); x++)
		{
			if(this->optionA[x]->shortName == shortOptionName)
				return this->optionA[x];
		}

		// Option must of not been found, so return NULL
		return NULL;
	}

	Option* Cmd::FindOptionByLongName(std::string longOptionName)
	{
		for(uint32_t x = 0; x < this->optionA.size(); x++)
		{
			if(this->optionA[x]->longName == longOptionName)
				return this->optionA[x];
		}

		// Option must of not been found, so return NULL
		return NULL;
	}

	uint32_t Cmd::NumLongOptions()
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			// Description too long, do not save it
			Print::PrintDebugInfo("CLIDE: Calculating num. of long options...\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		uint32_t numLongOptions = 0;
		
		uint32_t x;
		for(x = 0; x < this->optionA.size(); x++)
		{
			if(this->optionA[x]->longName.length() > 0)
				numLongOptions++;
		}
		
		#if(clide_ENABLE_DEBUG_CODE == 1)	
			snprintf(
				Global::debugBuff,
				sizeof(Global::debugBuff),
				"CLIDE: Num. long options = '%" STR(ClidePort_PF_UINT32_T) "'.\r\n",
				numLongOptions);
			Print::PrintDebugInfo(Global::debugBuff,
					Print::DebugPrintingLevel::VERBOSE);
		#endif
		
		return numLongOptions;		
	}

	void Cmd::AddToGroup(CmdGroup *cmdGroup)
	{
		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Adding command to a command group...\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif

		// Create option pointer at end of option pointer array.
		//this->cmdGroupA = (CmdGroup**)MemMang::AppendNewArrayElement(this->cmdGroupA, this->numCmdGroups, sizeof(CmdGroup*));
		this->cmdGroupA.push_back(cmdGroup);

		/*
		if(this->cmdGroupA == NULL)
		{
			#if(clide_ENABLE_DEBUG_CODE == 1)
				// Description too long, do not save it
				Print::PrintError("CLIDE: ERROR - Malloc failed while adding command to command group.\r\n");
			#endif
			return;
		}*/

		// Increase command group count
		//this->numCmdGroups++;

		/*
		// Remember the given command group
		this->cmdGroupA[this->numCmdGroups - 1] = cmdGroup;
		*/

		#if(clide_ENABLE_DEBUG_CODE == 1)
			Print::PrintDebugInfo("CLIDE: Added command to a command group.\r\n",
					Print::DebugPrintingLevel::VERBOSE);
		#endif

	}

	uint32_t Cmd::GetNumCmdGroups()
	{
		return this->cmdGroupA.size();
	}

	CmdGroup* Cmd::GetCmdGroup(uint32_t cmdGroupNum)
	{
		return this->cmdGroupA[cmdGroupNum];
	}

	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide
