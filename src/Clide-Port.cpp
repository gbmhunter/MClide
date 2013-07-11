//!
//! @file 		Clide-Port.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2012/03/19
//! @brief 		Contains port-specific skeleton functions.
//! @details
//!				See README.rst in root dir for more info.

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

// User includes
#include "./include/Clide-Port.hpp"

void* operator new(size_t size) 
{ 
	return malloc(size); 
} 

void operator delete(void* ptr) 
{ 
	free(ptr); 
} 

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//======================================= PUBLIC METHODS ========================================//
	//===============================================================================================//

	//! @brief 		The function to call to print debug information.
	//! @details	Used by many Clide classes.
	//! @warning	Port specific
	void Port::DebugPrint(const char* msg) 
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
	//!				status messages back to the user.
	//! @warning	Port specific
	void Port::CmdLinePrint(const char* msg)
	{
		#ifdef __linux__
			printf("%s", msg);
		#elif(CY_PSOC5)
			UartDebug::PutString(msg);
		#else
			#warning No command-line output defined.
		#endif
	}

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide