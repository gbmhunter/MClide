//!
//! @file 			Tx.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2012-03-19
//! @last-modified 	2014-10-07
//! @brief 			Clide TX controller. The main logic of the TX (sending)	part of Clide.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdint.h>		// int8_t, int32_t e.t.c
//#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <cstring>		// memset()

// User includes
#include "../include/StringSplit.hpp"
#include "../include/Config.hpp"
#include "../include/Param.hpp"
#include "../include/Option.hpp"
#include "../include/Cmd.hpp"
#include "../include/Print.hpp"
#include "../include/Tx.hpp"


namespace MbeddedNinja
{
	namespace MClideNs
	{
	
		using namespace std;

		//===============================================================================================//
		//=================================== METHOD DEFINITIONS ========================================//
		//===============================================================================================//

		// Constructor
		Tx::Tx()
		{
			// Nothing to initialise, all done in Clide::Comm (base class) initialiser.
		}


	} // namespace MClide
} // namespace MbeddedNinja
