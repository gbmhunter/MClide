//!
//! @file 			Clide-Config.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/18
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

	#define clideDEBUG_PRINT_GENERAL		1				//!< Print general debug msgs
	#define clideDEBUG_PRINT_VERBOSE		1				//!< Print verbose debug msgs
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

	//! @brief		Set to 1 to enable advanced output text formatting using special ASCII codes.
	//! @details	Tested with the bash shell.
	#define clide_ENABLE_ADV_TEXT_FORMATTING		(1)

	#if clide_ENABLE_ADV_TEXT_FORMATTING == 1
		#define clide_TERM_TEXT_FORMAT_NORMAL 	"\x1B[0m"		//!< Returns text to normal formatting.
		#define clide_TERM_TEXT_FORMAT_BOLD 	"\x1B[1m"		//!< Bold text.
		#define clide_TERM_COLOUR_YELLOW 		("\x1B[33;1m")	//!< Yellow text.

		//! @brief		Defines the colour to be used for the header rows of help information.
		//! @details	Use one of the colour macros above. Only applicable if #clide_ENABLE_ADV_TEXT_FORMATTING is 1.
		#define clide_TABLE_HEADER_ROW_COLOUR_CODE clide_TERM_COLOUR_YELLOW
	#endif
		
} // namespace Clide

#endif	// #ifndef CLIDE_CONFIG_H

// EOF
