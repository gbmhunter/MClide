//!
//! @file 			Param.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-04-02
//! @last-modified 	2014-10-07
//! @brief 			Contains the Param class, which enables the use of required parameters on the command-line interface.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
//#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <string.h>		// strlen()

//===== USER SOURCE =====//
#include "../include/Config.hpp"
#include "../include/Print.hpp"
#include "../include/Option.hpp"
#include "../include/Param.hpp"
#include "../include/Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{
	
		//===============================================================================================//
		//======================================= PUBLIC METHODS ========================================//
		//===============================================================================================//

		Param::Param(MString description)
		{
			this->Init(NULL, description);
		}

		// Constructor
		Param::Param(bool (*callBackFunc)(char *paramVal), MString description)
		{
			this->Init(callBackFunc, description);
		}
		
		Param::~Param()
		{
			// Destructor
			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo("CLIDE: Parameter destructor called.\r\n",
						Print::DebugPrintingLevel::VERBOSE);
			#endif

			// Deallocate memory
			//free(this->description);
		}

		//===============================================================================================//
		//====================================== PRIVATE METHODS ========================================//
		//===============================================================================================//

		void Param::Init(bool (*callBackFunc)(char *paramVal), MString description)
		{
			#if(clide_ENABLE_DEBUG_CODE == 1)
				Print::PrintDebugInfo("CLIDE: Parameter constructor called.\r\n",
						Print::DebugPrintingLevel::VERBOSE);
			#endif

			// DECRIPTION

			this->description = description;

			// CALLBACK

			// Save call back function
			this->callBackFunc = callBackFunc;
		}

	} // namespace MClide
} // namespace MbeddedNinja

// EOF
