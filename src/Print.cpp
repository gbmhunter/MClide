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
	SlotMachine::Callback<void, const char*> Print::errorPrintCallback;

	//===============================================================================================//
	//====================================== PRIVATE METHODS ========================================//
	//===============================================================================================//

	// none

} // namespace Clide
