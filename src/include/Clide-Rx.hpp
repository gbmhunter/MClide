//!
//! @file 			Clide-Rx.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2012/03/19
//! @last-modified 	2013/12/18
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

// User
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"
#include "Clide-Cmd.hpp"
#include "Clide-Port.hpp"
#include "Clide-GetOpt.hpp"
#include "Clide-Comm.hpp"

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
		
			//===============================================================================================//
			//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
			//===============================================================================================//
			
			//! @brief		Constructor
			Rx();
			
			//===============================================================================================//
			//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
			//===============================================================================================//
			
			//! @brief		Prints help information.
			void PrintHelp();
			
			//! @brief		Register a command with Clide. 
			//! @warning	Command must persist in memory while Rx object is used.
			void RegisterCmd(Cmd* cmd);

			//! @brief		Removes a previously registered command.
			//! @details	Uses free().
			//! @param		cmd		The command to de-register.
			//! @warning	Make sure command was previously registered with R!
			void RemoveCmd(Cmd* cmd);

			//! @brief		Runs the algorithm. Call this with the received command msg (array of characters). In a Linux environment, cmdMsg could be equal to a read line of cin.
			//! @param		cmdMsg	The message to process.
			bool Run(char* cmdMsg);

		private:
			
			//===============================================================================================//
			//================================== PUBLIC VARIABLES/STRUCTURES ================================//
			//===============================================================================================//
			
			//! @brief		Validates command.
			//! @details	Makes sure cmd is in the registered command list
			Cmd* ValidateCmd(char* cmdName, Cmd** cmdA, uint8_t numCmds);
			
			//! @brief		Checks for option in registered command
			Option* ValidateOption(Clide::Cmd *detectedCmd, char *optionName);
			
			//! @brief		Splits packet into arguments, which can be options and/or parameters.
			//! @returns	Number of arguments found
			int SplitPacket(char* packet, char(*args)[clideMAX_STRING_LENGTH]);
			
			//! @brief		Builds the short option string for the getopt_long() function from the list
			//!				of the registered commands.
			void BuildShortOptionString(char* optionString, Cmd* cmd);
			
			//! @brief		Prints help for the given command.
			void PrintHelpForCmd(Cmd* cmd);
			
			//! @brief		Builds the structure of long options that is required by getopt_long().
			void BuildLongOptionStruct(GetOpt::option* longOptStructA, Cmd* cmd);
		
	};


	// none

} // namespace Clide

#endif	// #ifndef CLIDE_RX_H

// EOF
