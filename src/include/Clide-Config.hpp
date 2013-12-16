//!
//! @file 			Clide-Config.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/10
//! @brief 			Configuration file for Clide.
//! @details
//!				See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CONFIG_H
#define CLIDE_CONFIG_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// none

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	//=============== DEBUG SWITCHES ============//

	#define clideDEBUG_PRINT_GENERAL		0				//!< Print general debug msgs
	#define clideDEBUG_PRINT_VERBOSE		0				//!< Print verbose debug msgs
	#define clideDEBUG_PRINT_ERROR			1				//!< Print error debug msgs

	//! @brief		This is true if any individual debug print macros are 1.
	#define clideDEBUG_PRINT_ANY	(clideDEBUG_PRINT_GENERAL | clideDEBUG_PRINT_VERBOSE | clideDEBUG_PRINT_ERROR)

	//! @brief		Set to 1 to enable automatic help generation.
	#define clide_ENABLE_AUTO_HELP			1
	
	//! @brief		Sets the maximum string length for a single command, parameter, or option name/option value
	//! @todo 		Use dynamic allocation, so not required.
	#define clideMAX_STRING_LENGTH			(20)	

	//! Maximum length for the cmd name
	#define clideMAX_NAME_LENGTH				(20)

	//! Maximum length for the cmd description
	#define clideMAX_DESCRIPTION_LENGTH		(100)	
	
	//! @brief		The size of the debug buffer.
	//! @details	All writes use snprintf() so should be safe if too small.
	#define clide_DEBUG_BUFF_SIZE				(200)
		
} // namespace Clide

#endif	// #ifndef CLIDE_CONFIG_H

// EOF
