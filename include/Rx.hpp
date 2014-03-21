//!
//! @file 			Rx.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2012/03/19
//! @last-modified 	2014/01/21
//! @brief 			Clide RX controller. The main logic of the RX (decoding) part of Clide. Commands can be registered with the controller.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_RX_H
#define CLIDE_RX_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System
#include <stdint.h>

// Clide
#include "Config.hpp"
#include "Param.hpp"
#include "Option.hpp"
#include "Cmd.hpp"
#include "GetOpt.hpp"
#include "Comm.hpp"
#include "Log.hpp"				//!< Used for logging warnings and errors

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{



	//! @brief		Class deals with receiving of command-line strings and the decoding/processing of them.
	//! @details	This is one of the most important objects in the Clide library. Inherits from the Comm class.
	class Rx : public Comm
	{
	
		public:
		
			//! @brief		Log IDs for Rx relevant warnings/errors.
			enum class LogIds : uint32_t
			{
				NONE,
				CMD_NOT_RECOGNISED
			};

			//===============================================================================================//
			//=================================== PUBLIC VARIABLES/STRUCTURES ===============================//
			//===============================================================================================//

			//! @brief		Holds warning/error information.
			//! @details	Investigate this if you wish to find out more about why a function returned false.
			//Log<LogIds> log;

			//! @brief		Set to true to silence (not print) an error when a received message is not recognised as a valid command.
			//! @details	Default is false, as it is usually helpful to show this error.
			bool silenceCmdNotRecognisedError;

			//===============================================================================================//
			//======================================= PUBLIC METHODS ========================================//
			//===============================================================================================//

			//! @brief		Default constructor
			Rx();

			//! @brief		Runs the algorithm. Call this with the received command msg (array of characters).
			//! @details	In a Linux environment, cmdMsg could be equal to a read line of cin.
			//! @param		cmdMsg	The message to process.
			//! @returns	true is the command processing of cmdMsg was successful, otherwise false.
			bool Run(char* cmdMsg);

		private:
			
			//===============================================================================================//
			//================================== PRIVATE VARIABLES/STRUCTURES ===============================//
			//===============================================================================================//


			Cmd *cmdHelp;

			//===============================================================================================//
			//======================================= PRIVATE METHODS =======================================//
			//===============================================================================================//

			//! @brief		Validates command.
			//! @details	Makes sure cmd is in the registered command list
			Cmd* ValidateCmd(char* cmdName, Cmd** cmdA, uint8_t numCmds);
			
			//! @brief		Checks for option in registered command
			Option* ValidateOption(Clide::Cmd *detectedCmd, char *optionName);
			
			//! @brief		Splits packet into arguments, which can be options and/or parameters.
			//! @returns	Number of arguments found
			int SplitPacket(char* packet, char(*args)[clide_MAX_STRING_LENGTH]);
			
			//! @brief		Builds the short option string for the getopt_long() function from the list
			//!				of the registered commands.
			void BuildShortOptionString(char* optionString, Cmd* cmd);
			
			//! @brief		Builds the structure of long options that is required by getopt_long().
			void BuildLongOptionStruct(GetOpt::option* longOptStructA, Cmd* cmd);


	};

} // namespace Clide

#endif	// #ifndef CLIDE_RX_H

// EOF
