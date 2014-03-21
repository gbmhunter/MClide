//!
//! @file 			Config.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2014/03/20
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


//=============== DEBUG SWITCHES ============//

#define clide_DEBUG_PRINT_GENERAL		1				//!< Print general debug msgs
#define clide_DEBUG_PRINT_VERBOSE		1				//!< Print verbose debug msgs
#define clide_DEBUG_PRINT_ERROR			1				//!< Print error debug msgs

//! @brief		This is true if any individual debug print macros are 1.
#define clideDEBUG_PRINT_ANY	(clide_DEBUG_PRINT_GENERAL | clide_DEBUG_PRINT_VERBOSE | clide_DEBUG_PRINT_ERROR)

//=============== CALLBACK SWITCHES ============//

//! @brief		Set to 1 to enable callbacks that can call methods (member functions).
//! @details	Non-member functions are supported also by
#define clide_ENABLE_METHOD_CALLBACKS	1

//====================== HELP-RELATED SWITCHES =================//

//! @brief		Set to 1 to enable automatic help generation.
#define clide_ENABLE_AUTO_HELP			0

//! @brief		(char*) The amount of padding before the cmd column when printing help.
#define config_PADDING_BEFORE_CMD_IN_HELP 		5

//! @brief		(char*) The amount of padding given to the command name column when printing help.
#define config_CMD_PADDING_FOR_HELP				15
#define config_CMD_PADDING_FOR_HELP_MINUS_1		14			//!< Make sure this is always (config_CMD_PADDING_FOR_HELP - 1)

//! @brief		Sets the maximum string length for a single command, parameter, or option name/option value
//! @todo 		Use dynamic allocation, so not required.
#define clide_MAX_STRING_LENGTH			(20u)

//! @brief		Maximum length for the cmd name
#define clide_MAX_NAME_LENGTH			(20u)

//! @brief		Maximum length for the cmd description
#define clide_MAX_DESCRIPTION_LENGTH		(100u)

//! @brief		The size of the debug buffer.
//! @details	All writes use snprintf() so should be safe if too small.
#define clide_DEBUG_BUFF_SIZE				(200u)

//! @brief		Set to 1 to enable advanced output text formatting using special ASCII codes.
//! @details	Tested with the bash shell.
#define clide_ENABLE_ADV_TEXT_FORMATTING		(1u)

#if clide_ENABLE_ADV_TEXT_FORMATTING == 1
	#define clide_TERM_TEXT_FORMAT_NORMAL 	"\x1B[0m"		//!< Returns text to normal formatting. Widely supported.
	#define clide_TERM_TEXT_FORMAT_BOLD 	"\x1B[1m"		//!< Bold text. Widely supported.
	#define clide_TERM_TEXT_FORMAT_ITALIC	"\x1B[3m"		//!< Italic text. Not supported by many terminals.
	#define clide_TERM_COLOUR_YELLOW 		("\x1B[33;1m")	//!< Yellow text. Widely supported.

	//! @brief		Defines the colour to be used for the header rows of help information.
	//! @details	Use one of the colour macros above. Only applicable if #clide_ENABLE_ADV_TEXT_FORMATTING is 1.
	#define clide_TABLE_HEADER_ROW_COLOUR_CODE clide_TERM_COLOUR_YELLOW
#endif

//=================== RxBuff Config =================//

//! @brief		(uint32_t) Size of the fixed-width buffer that the RxBuff class uses to store characters when RxBuff::Write() is called.
#define clide_RX_BUFF_SIZE					(256u)
		

#endif	// #ifndef CLIDE_CONFIG_H

// EOF
