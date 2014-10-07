//!
//! @file 			Global.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-04-02
//! @last-modified 	2014-10-07
//! @brief 		 	Contains global functions and variables used by many MClide classes.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// User includes
#include "../include/Config.hpp"
#include "../include/Global.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{

		char Global::debugBuff[clide_DEBUG_BUFF_SIZE] = {0};

		//===============================================================================================//
		//====================================== PRIVATE METHODS ========================================//
		//===============================================================================================//

		// none

	} // namespace MClide
} // namespace MbeddedNinja

// EOF
