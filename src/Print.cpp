//!
//! @file				Print.cpp
//! @author				Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created			2012/03/19
//! @last-modified		2014/03/21
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
	SlotMachine::Callback<void, const char*> Print::errorPrintCallback;

	bool Print::enableDebugInfoPrinting = true;
	bool Print::enableCmdLinePrinting = true;
	bool Print::enableErrorPrinting = true;

	Print::DebugPrintingLevel Print::debugPrintingLevel = Print::DebugPrintingLevel::VERBOSE;

	void Print::PrintDebugInfo(const char* msg, DebugPrintingLevel debugPrintingLevel)
	{
		if(enableDebugInfoPrinting == true)
			debugPrintCallback.Execute(msg);
	}

	void Print::PrintError(const char* msg)
	{
		if(enableErrorPrinting == true)
			errorPrintCallback.Execute(msg);
	}

	void Print::PrintToCmdLine(const char* msg)
	{
		if(enableCmdLinePrinting == true)
			cmdLinePrintCallback.Execute(msg);
	}

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide
