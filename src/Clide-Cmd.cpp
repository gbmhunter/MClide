//!
//! @file 		Clide-Cmd.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Command-line style communications protocol
//! @details
//!				See README.rst in root folder.

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
#include <string.h>		// strlen()

// User includes
#include "include/Clide-MemMang.hpp"
#include "include/Clide-Config.hpp"
#include "include/Clide-Port.hpp"
#include "include/Clide-Option.hpp"
#include "include/Clide-Param.hpp"
#include "include/Clide-Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{


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

	// none

	//===============================================================================================//
	//================================== PRIVATE FUNCTION PROTOTYPES ================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//===================================== PUBLIC FUNCTIONS ========================================//
	//===============================================================================================//



	// Constructor
	Cmd::Cmd(const char *name, bool (*callBackFunc)(Cmd* foundCmd), const char *description)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Cmd constructor called.\r\n");
		#endif
		
		// INITIALISATION
		
		this->numParams = 0;
		this->numOptions = 0;
		
		// Set pointers to null. If not NULL, this causes realloc() is exhibit undefined behaviour,
		// since it expects a previously defined location or NULL
		this->paramA = NULL;
		this->optionA = NULL;

		// NAME
		
		uint32_t descLen = strlen(name);
		
		// Make sure the description isn't to long
		if(descLen <= clideMAX_NAME_LENGTH)
		{
			// Create memory for description and store
			this->name = (char*)MemMang::MallocString(name);
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Command name was too long.\r\n");
			#endif
		}
		
		// DECRIPTION
		
		descLen = strlen(description);
		
		// Make sure the description isn't to long
		if(descLen <= clideMAX_DESCRIPTION_LENGTH)
		{
			// Create memory for description and store
			this->description = MemMang::MallocString(description);
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Command description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		this->callBackFunc = callBackFunc;
		
		#if(clide_ENABLE_AUTO_HELP == 1)
			// HELP OPTION
			Option* help = new Option("h", NULL, "Prints help for the command.");
			this->RegisterOption(help);
		#endif
		
		// DETECTED FLAG
		this->isDetected = false;
		
	}

	Cmd::~Cmd()
	{
		// Destructor
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Cmd destructor called.\r\n");
		#endif
		
		// Free up memory
		free(paramA);
		free(optionA);
	}
	
	void Cmd::RegisterParam(Param* param)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Registering parameter...\r\n");
		#endif

		//this->numParams = 0;
			
		// MALLOC
		this->paramA = (Param**)MemMang::AppendNewArrayElement(this->paramA, this->numParams, sizeof(Param*));
		
		if(this->paramA == NULL)
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR - Malloc failed while registering parameter.\r\n");
			#endif
			return;	
		}
		
		// Increase parameter count
		this->numParams++;
		
		// Remember the pointer
		paramA[numParams - 1] = param;
	}


	// Register option
	void Cmd::RegisterOption(Option* option)
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			// Description too long, do not save it
			Port::DebugPrint("CLIDE: Registering option...\r\n");
		#endif

		// Create option pointer at end of option pointer array.
		this->optionA = (Option**)MemMang::AppendNewArrayElement(this->optionA, this->numOptions, sizeof(Option*));
		
		// Increase option count
		this->numOptions++;
		
		// Remember option
		optionA[this->numOptions - 1] = option;
		
		#if(clideDEBUG_PRINT_VERBOSE == 1)	
			Port::DebugPrint("CLIDE: Option name = ");
			Port::DebugPrint(optionA[this->numOptions - 1]->name);
			Port::DebugPrint("\r\n");
		#endif
	}


	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide