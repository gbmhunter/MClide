//!
//! @file 		Clide-Rx.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/03/19
//! @brief 		Clide RX controller. The main logic of the RX (decoding)
//!				part of Clide. Commands can be registered with the controller.
//! @details
//!				See README.rst in root dir for more info.

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
#include <getopt.h>		// getopt()	

// User
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"
#include "Clide-Cmd.hpp"
#include "Clide-Port.hpp"
#include "Clide-GetOpt.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{
	//! @brief		Class deals with receiving of command-line strings and the decoding/processing of them.
	//1 @details	This is one of the most important objects in the Clide library.
	class Rx
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
			
			//! @brief		Initialises the Clide library for use.
			//! @warning	Call before using any other Clide function.
			void Init();
			
			//! @brief		Register a command with Clide. 
			//! @warning	Command must persist in memory while Rx object is used.
			void RegisterCmd(Cmd* cmd);

			//! @brief		Removes a previously registered command.
			//! @details	Uses free().
			//! @param		cmd		The command to de-register.
			//! @warning	Make sure command was previously registered with R!
			void RemoveCmd(Cmd* cmd);

			//! @brief		Runs the algorithm. Call this with the recieved command msg.
			//! @param		cmdMsg	The message to process.
			bool Run(char* cmdMsg);

			//! @brief		Registers the help command.
			//! @details	This is an automatically generated command which prints
			//!				help information about the registered commands to the 
			//!				command-line.
			void RegisterHelpCmd();
			
			//===============================================================================================//
			//================================== PUBLIC VARIABLES/STRUCTURES ================================//
			//===============================================================================================//
			
			//! @brief		Points to an array of pointers to registered commands
			//! @details	This is updated everytime RegisterCmd() is called
			Cmd **cmdA;

			//! @brief		The number of registered commands
			//! @details	Incremented everytime RegisterCmd() is called
			uint8_t numCmds;
			
			//! @brief		Determines whether help commands are automatically availiable
			//! @details	Defaults to TRUE
			bool helpEnabled;
			
		private:
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
