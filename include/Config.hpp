//!
//! @file 			Config.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-04-02
//! @last-modified 	2014-10-07
//! @brief 			Configuration file for MClide.
//! @details
//!				See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MCLIDE_CONFIG_H
#define MCLIDE_CONFIG_H


//=============== DEBUG SWITCHES ============//

//! @brief		Set to 1 to enable debug code (including debug message printing) through-out the Clide library. Set to 0 to disable all debug code, which will save memory.
#define clide_ENABLE_DEBUG_CODE			1

//=============== CALLBACK SWITCHES ============//

//! @brief		Set to 1 to enable callbacks that can call methods (member functions).
//! @details	Non-member functions are supported also by
#define clide_ENABLE_METHOD_CALLBACKS	1

//====================== HELP-RELATED SWITCHES =================//

//! @brief		Set to 1 to enable automatic help generation.
#define clide_ENABLE_AUTO_HELP					1

//! @brief		(char*) The amount of padding before the cmd column when printing help.
#define config_PADDING_BEFORE_CMD_IN_HELP 		5

//! @brief		(char*) The amount of padding given to the command name column when printing help.
#define config_CMD_PADDING_FOR_HELP				15
#define config_CMD_PADDING_FOR_HELP_MINUS_1		14			//!< Make sure this is always (config_CMD_PADDING_FOR_HELP - 1)

//! @brief		(char*) The name of the option which prevents the help header from being printed when the help command is called.
#define config_NO_HELP_HEADER_OPTION_NAME		"no-header"

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
		

#endif	// #ifndef MCLIDE_CONFIG_H

// EOF
