//!
//! @file 			Param.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2014/01/24
//! @brief 			Contains the Param class, which enables the use of required parameters on the command-line interface.
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
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//

	Param::Param(const char* description)
	{
		this->Init(NULL, description);
	}

	// Constructor
	Param::Param(bool (*callBackFunc)(char *paramVal), const char* description)
	{
		this->Init(callBackFunc, description);
	}
	
	Param::~Param()
	{
		// Destructor
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Parameter destructor called.\r\n");
		#endif
		
		// Deallocate memory
		//free(this->description);
	}

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	void Param::Init(bool (*callBackFunc)(char *paramVal), const char* description)
	{
		#if(clide_DEBUG_PRINT_VERBOSE == 1)	
			Print::debugPrintCallback.Execute("CLIDE: Parameter constructor called.\r\n");
		#endif

		// DECRIPTION
		
		uint32_t stringLen = strlen(description);
		
		// Make sure the description isn't to long
		if(stringLen <= clide_MAX_DESCRIPTION_LENGTH)
		{
			// Create memory for description and store
			this->description = MemMang::MallocString(description);
		}
		else
		{
			#if(clide_DEBUG_PRINT_ERROR == 1)	
				// Description too long, do not save it
				Print::errorPrintCallback.Execute("CLIDE: ERROR: Parameter description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		
		// Save call back function
		this->callBackFunc = callBackFunc;
	}

} // namespace Clide
