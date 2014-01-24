//!
//! @file 			Option.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2014/01/24
//! @brief 		 	The option class enables used of 'optional' parameters in the command-line interface.
//! @details
//!					See README.rst in repo root dir for more info.

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
#include <string.h>		// strlen()

// User includes
#include "../include/MemMang.hpp"
#include "../include/Config.hpp"
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
	//===================================== MEMBER FUNCTIONS ========================================//
	//===============================================================================================//

	Option::Option(
		const char shortName,
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		// Base constructor
		
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Base option constructor called.\r\n");
		#endif
		Init(
			shortName,
			longName,
			callBackFunc,
			description,
			associatedValue);
	}
	
	Option::Option(
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description)
	{	
		// Simplified constructor. No short name.
		
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Simplified option constructor called (no short name).\r\n");
		#endif
		Init(
			'\0',
			longName,
			callBackFunc,
			description,
			false);
	}
	
	Option::Option(
		const char shortName,
		bool (*callBackFunc)(char *optionVal),
		const char* description)
	{	
		// Simplified constructor. No long name.
		
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Simplified option constructor called (no long name).\r\n");
		#endif
		Init(
			shortName,
			NULL,
			callBackFunc,
			description,
			false);
	}
	
	

	Option::~Option()
	{
		// Destructor
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Option destructor called.\r\n");
		#endif
		
		// Free memory
		//free(this->longName);
		//free(this->description);
	}
	
	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	void Option::Init(
		const char shortName,
		const char* longName,
		bool (*callBackFunc)(char *optionVal),
		const char* description,
		bool associatedValue)
	{
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Option constructor called.\r\n");
		#endif		
		
		// Input checks
		uint32_t stringLen = 0;
		
		// Check long name length
		if(longName != NULL)
		{
			stringLen = strlen(longName);
			if(stringLen > clide_MAX_NAME_LENGTH)
			{
				#if(clide_DEBUG_PRINT_ERROR == 1)	
					// Description too long, do not save it
					Print::errorPrintCallback.Execute("CLIDE: ERROR: 'Long' option name was too long.\r\n");
				#endif
				
				return;
			}
		}
		
		// Check too-long description
		if(description != NULL)
		{
			stringLen = strlen(description);
			if(stringLen > clide_MAX_DESCRIPTION_LENGTH)
			{
				#if(clide_DEBUG_PRINT_ERROR == 1)	
					// Description too long, do not save it
					Print::errorPrintCallback.Execute("CLIDE: ERROR: Option description was too long.\r\n");
				#endif
				
				return;
			}
		}
	
		// NAME

		// Store short name directly (only one char, no memory alloc needed)
		this->shortName = shortName;
		
		// Create memory for long name and store
		if(longName != NULL)
		{
			//this->longName = MemMang::MallocString(longName);
			this->longName = longName;
		}
		else
			this->longName = NULL;
		
		// DECRIPTION

		// Create memory for description and store
		if(description != NULL)
		{
			//this->description = MemMang::MallocString(description);
			this->description = description;
		}
		else
			description = NULL;
		
		// CALLBACK
		
		this->callBackFunc = callBackFunc;
		
		// DETECTED?
		
		this->isDetected = false;
		
		// ASSOCIATED VALUE?
		
		this->associatedValue = associatedValue;
		
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Option constructor finished.\r\n");
		#endif
	}

} // namespace Clide

// EOF
