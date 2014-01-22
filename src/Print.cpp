//!
//! @file				Print.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created			2012/03/19
//! @last-modified		2014/01/22
//! @brief 				Contains callbacks for port-specific print operations.
//! @details
//!						See README.rst in repo root dir for more info.

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

// User includes
#include "../include/Print.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//

	SlotMachine::Callback<void, const char*> Print::debugPrintCallback;
	SlotMachine::Callback<void, const char*> Print::cmdLinePrintCallback;
	/*
	//! @brief 		The function to call to print debug information. The level of debug information is determined by the macros in Clide-Config.hpp.
	//! @details	Used by many Clide classes.
	//! @warning	Port specific
	void Print::debugPrintCallback.Execute(const char* msg) 
	{
		#ifdef __linux__
			printf("%s", msg);
		#elif(CY_PSOC5)
			UartDebug::PutString(msg);
		#else
			#warning No debug output defined.
		#endif
	}

	//! @brief 		The function to call to print to the command-line.
	//! @details	Used primarily by Clide::Tx, but also by Clide::Rx for printing
	//!				status messages and help requests back to the user.
	//! @warning	Port specific
	void Print::cmdLinePrintCallback.Execute(const char* msg)
	{
		#ifdef __linux__
			printf("%s", msg);
		#elif(CY_PSOC5)
			UartComms::PutString(msg);
		#else
			#warning No command-line output defined.
		#endif
	}*/

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide
