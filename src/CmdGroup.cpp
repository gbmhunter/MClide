//!
//! @file 			CmdGroup.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-01-06
//! @last-modified 	2014-10-07
//! @brief 			The CmdGroup object is used to create "groups" that commands can belong too, which can be then be utilised to display selective help information.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

//===== SYSTEM LIBRARIES =====//
#include <stdint.h>		// int8_t, int32_t e.t.c
//#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <string.h>		// strlen()

//===== USER SOURCE =====//
#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/Print.hpp"
#include "../include/Option.hpp"
#include "../include/Param.hpp"
#include "../include/Cmd.hpp"


namespace MbeddedNinja
{
	namespace MClideNs
	{

		//===============================================================================================//
		//======================================= PUBLIC METHODS ========================================//
		//===============================================================================================//

		CmdGroup::CmdGroup(std::string name, std::string description)
		{
			this->name = name;
			this->description = description;
		}

		//===============================================================================================//
		//====================================== PRIVATE METHODS ========================================//
		//===============================================================================================//

		// none

	} // namespace MClide
} // namespace Mbedded Ninja

// EOF
