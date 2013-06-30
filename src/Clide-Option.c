//!
//! @file 		Clide-Param.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Command-line style communications protocol
//! @details
//!		<b>Last Modified:			</b> 2013/05/14					\n
//!		<b>File Version:			</b> v1.0.0.0					\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free Code Libraries		\n
//!		<b>Language:				</b> C++						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> GPLv3						\n
//!
//! See Clide-Param.h for more information.
//!

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <getopt.h>		// getopt()	

// User includes
#include "./Comms/include/UartDebug.h"
#include "./Comms/include/UartComms.h"
#include "MemMang.h"
#include "Clide-Config.h"
#include "Clide-Port.h"
#include "Clide-Option.h"
#include "Clide-Param.h"
#include "Clide-Cmd.h"

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
	Option::Option(const char* optionName, bool (*callBackFunc)(char *optionVal), const char* description)
	{	
		Option::Option(const char* optionName, bool (*callBackFunc)(char *optionVal), const char* description, false)
	}

	// Base constructor
	Option::Option(const char* optionName, bool (*callBackFunc)(char *optionVal), const char* description, bool associatedValue)
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
				DebugPrint("CLIDE: ERROR: Option name was too long.\r\n");
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
				DebugPrint("CLIDE: ERROR: Option description was too long.\r\n");
			#endif
		}
		
		// CALLBACK
		
		this->callBackFunc = callBackFunc;
		
		// DETECTED?
		
		this->isDetected = false;
		
		// ASSOCIATED VALUE?
		
		this->associatedValue = associatedValue;
	}




	//===============================================================================================//
	//==================================== PRIVATE FUNCTIONS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide