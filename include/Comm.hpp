//!
//! @file 			Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013/12/18
//! @last-modified 	2014/05/16
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
#include <vector>

// User library ("lib/") headers
#include "../lib/slotmachine-cpp/api/Slotmachine.hpp"		//!< Callbacks.

// Forward declaration
class Comm;

// User "include/" headers
#include "Config.hpp"
#include "Cmd.hpp"
#include "CmdGroup.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	using namespace std;

	//! @brief		Callback function for help command.
	//! @details	This does not belong to a class, so that it can be passed as a generic callback function, just like any other command.
	//! @note		Threadsafe, re-entrant
	bool HelpCmdCallback(Cmd *cmd);

	//! @brief The base communications class. This is extended by both Clide::Tx and Clide::Rx which are the classes manipulated by the user.
	class Comm
	{
		public:

			//===============================================================================================//
			//====================================== PUBLIC VARIABLES =======================================//
			//===============================================================================================//

			//! @brief		Points to an array of pointers to registered commands
			//! @details	This is updated everytime RegisterCmd() is called
			std::vector<Cmd*> cmdA;

			//! @brief		The number of registered commands
			//! @details	Incremented everytime RegisterCmd() is called
			//uint8_t numCmds;

			//! @brief		The default command group that will be applied to help requests, if no command group is given.
			//! @details	Assign this to a command group that you create. When "help" is called with no "-g groupName" option, this will the help group that is printed.
			CmdGroup *defaultCmdGroup;

			//! @brief		All commands, when registered to a Comm object, will become part of the command group "all".
			CmdGroup *cmdGroupAll;

			//! @brief		This gives you the ability to provide a callback function that is called when a command is not recognised.
			//! @details	This is essentially an event handler. All callback functions associated with recognised commands are part of the command objects themselves. The callbacks one and only input parameter is the null-terminated command string that it did not recognise.
			SlotMachine::Callback<void, char*> cmdUnrecogCallback;

			//! @brief		This callback gives you the ability to perform an action if the help command is requested.
			//! @details
			SlotMachine::Callback<void, char*> generalHelpRequestedCallback;

			//===============================================================================================//
			//======================================= PUBLIC METHODS ========================================//
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


		//===============================================================================================//
		//==================================== PROTECTED METHODS ========================================//
		//===============================================================================================//

		protected:



	};
} // namespace Clide

#endif // #ifndef CLIDE_COMM_H

// EOF
