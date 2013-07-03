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

// User
#include "Clide-Config.h"
#include "Clide-Param.h"
#include "Clide-Option.h"
#include "Clide-Cmd.h"
#include "Clide-Port.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	class Rx
	{
		private:
			//! @brief		Validates command.
			//! @details	Makes sure cmd is in the registered command list
			//! @private
			Cmd* ValidateCmd(char* cmdName, Cmd** cmdA, uint8_t numCmds);
			
			//! @brief		Checks for option in registered command
			Option* ValidateOption(Clide::Cmd *detectedCmd, char *optionName);
			
			//! @brief		Splits packet into arguments, which can be options and/or parameters.
			//! @returns	Number of arguments found
			int SplitPacket(char* packet, char(*args)[clideMAX_STRING_LENGTH]);
			
			//! @brief		Sets all of the char* pointers back to the original order
			//! @details	Order is changed by getopt(). Make sure to call everytime before
			//!				using getopt()
			//! @private
			void ResetArgsPointer();
			
			//! @brief		Builds the option string for the getopt() function from the list
			//!				of the registered commands.
			void BuildOptionString(char* optionString, Cmd* cmd);
			
			void PrintHelpForCmd(Cmd* cmd);
		
		public:
		
			//===============================================================================================//
			//======================================== CONSTRUCTOR ==========================================//
			//===============================================================================================//
			
			Rx();
			
			//===============================================================================================//
			//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
			//===============================================================================================//
			
			//! @brief		Prints help information.
			//! @private
			void PrintHelp();
			
			//! @brief		Initialises the Clide library for use.
			//! @warning	Call before using any other Clide function.
			//! @public
			void Init();
			
			void RegisterCmd(Cmd* cmd);
			
			//! @brief		Register a command with Clide
			//! @public
			//Cmd* RegisterCmd(const char *name, bool (*callBackFunc)(Cmd* foundCmd));

			//! @brief		Register a command with Clide
			//! @public
			//Cmd* RegisterCmd(const char *name, bool (*callBackFunc)(Cmd* foundCmd), const char *description);

			//! @brief		Removes a previously registered command
			//! @details	Uses free()
			//! @public
			void RemoveCmd(Cmd* cmd);

			//! @brief		Runs the algorithm
			//! @public
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
			//! @public
			bool helpEnabled;
		
	};


	// none

} // namespace Clide

#endif	// #ifndef CLIDE_RX_H

// EOF
