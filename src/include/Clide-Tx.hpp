//!
//! @file 		Clide-Tx.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/10
//! @brief 		Clide TX controller. The main logic of the TX (sending)
//!				part of Clide.
//! @details
//!				See README.rst in root folder.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_TX_H
#define CLIDE_TX_H

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

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	class Tx
	{
		
		public:
		
			//===============================================================================================//
			//======================================== CONSTRUCTOR ==========================================//
			//===============================================================================================//
			
			//! @brief		Constructor
			Tx();
			
			//===============================================================================================//
			//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
			//===============================================================================================//
			
			//! @brief		Prints help information.
			//! @private
			void PrintHelp();
			
			void RegisterCmd(Cmd* cmd);		

			//! @brief		Removes a previously registered command
			//! @details	Uses free()
			//! @public
			void RemoveCmd(Cmd* cmd);

			//! @brief		Registers the help command.
			//! @details	This is an automatically generated command which prints
			//!				help information about the registered commands to the 
			//!				command-line.
			void RegisterHelpCmd();
			
			//===============================================================================================//
			//================================== PUBLIC VARIABLES/STRUCTURES ================================//
			//===============================================================================================//
			
			//! @brief		Points to an array of registered commands
			//! @details	This is updated everytime RegisterCmd() is called
			Cmd **cmdA;

			//! @brief		The number of registered commands
			//! @details	Incremented everytime RegisterCmd() is called
			uint8_t numCmds;
			
			//! @brief		Determines whether help commands are automatically availiable
			//! @details	Defaults to TRUE
			//! @public
			bool helpEnabled;
			
		private:		
			void PrintHelpForCmd(Cmd* cmd);
	};

} // namespace Clide

#endif	// #ifndef CLIDE_TX_H

// EOF
