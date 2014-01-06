//!
//! @file 			Clide-Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/12/18
//! @last-modified 	2013/12/19
//! @brief			The base communications class. This is extended by both Clide::Tx and Clide::Rx which are the classes manipulated by the user.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_COMM_H
#define CLIDE_COMM_H

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdint.h>		// int8_t, int32_t e.t.c
#include <stdio.h>		// snprintf()
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 
#include <cstring>		// memset()

// User includes
#include "Clide-Config.hpp"
#include "Clide-Cmd.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{


	using namespace std;

	//! @brief		Callback function for help command.
	//! @details	This does not belong to a class, so that it can be passed as a generic callback function, just like any other command.
	bool HelpCmdCallback(Cmd *cmd);

	//! @brief The base communications class. This is extended by both Clide::Tx and Clide::Rx which are the classes manipulated by the user.
	class Comm
	{
		public:
			//===============================================================================================//
			//====================================== PUBLIC METHODS ========================================//
			//===============================================================================================//

			//! @brief 		Constructor
			Comm();

			//! @brief 		Prints out the help info.
			void PrintHelp(Cmd* cmd);

			void PrintHelpForCmd(Cmd* cmd);

			//! @brief		Register a command with Clide.
			//! @warning	Command must persist in memory while Rx object is used.
			void RegisterCmd(Cmd* cmd);

			//! @brief		Removes a previously registered command.
			//! @details	Uses free().
			//! @param		cmd		The command to de-register.
			//! @warning	Make sure command was previously registered with Clide::Rx
			void RemoveCmd(Cmd* cmd);

			//! @brief		Points to an array of pointers to registered commands
			//! @details	This is updated everytime RegisterCmd() is called
			Cmd **cmdA;

			//! @brief		The number of registered commands
			//! @details	Incremented everytime RegisterCmd() is called
			uint8_t numCmds;

		//===============================================================================================//
		//==================================== PROTECTED METHODS ========================================//
		//===============================================================================================//

		protected:



	};
} // namespace Clide

#endif // #ifndef CLIDE_COMM_H

// EOF
