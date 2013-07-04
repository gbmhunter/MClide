//!
//! @file 		Clide-Param.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Command-line style communications protocol
//! @details
//!				See README.rst in root directory for more information.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
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
	// Register option. 
	Option::Option(
		const char* optionName,
		bool (*callBackFunc)(char *optionVal),
		const char* description)
	{	
		Init(
			optionName,
			callBackFunc,
			description,
			false);
	}
	
	// Base constructor
	Option::Option(
		const char* optionName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		Init(
			optionName,
			callBackFunc,
			description,
			associatedValue);
	}

	Option::~Option()
	{
		// Destructor
		
		// Free memory
		free(this->name);
		free(this->description);
	}
	
	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	void Option::Init(
		const char* optionName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		// NAME
		
		uint32_t stringLen = strlen(optionName);
		
		// Make sure the description isn't to long
		if(stringLen <= clideMAX_NAME_LENGTH)
		{
			// Create memory for name and store
			this->name = MemMang::MallocString(optionName);
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Option name was too long.\r\n");
			#endif
		}

		// DECRIPTION
		
		stringLen = strlen(description);
		
		// Make sure the description isn't to long
		if(stringLen <= clideMAX_DESCRIPTION_LENGTH)
		{
			// Create memory for description and store
			this->description = MemMang::MallocString(description);
		}
		else
		{
			#if(clideDEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Port::DebugPrint("CLIDE: ERROR: Option description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		
		this->callBackFunc = callBackFunc;
		
		// DETECTED?
		
		this->isDetected = false;
		
		// ASSOCIATED VALUE?
		
		this->associatedValue = associatedValue;
	}

} // namespace Clide

// EOF
