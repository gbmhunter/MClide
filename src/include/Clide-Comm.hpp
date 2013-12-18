//!
//! @file 			Clide-Comm.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/12/18
//! @last-modified 	2013/12/18
//! @brief
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


	bool HelpCmdCallback(Cmd *cmd);

	class Comm
	{
		public:
			//===============================================================================================//
			//====================================== PUBLIC METHODS ========================================//
			//===============================================================================================//

			// Constructor
			Comm();

			// Prints out the help info
			void PrintHelp();

			//! @brief		Points to an array of pointers to registered commands
			//! @details	This is updated everytime RegisterCmd() is called
			Cmd **cmdA;

			//! @brief		The number of registered commands
			//! @details	Incremented everytime RegisterCmd() is called
			uint8_t numCmds;

		//===============================================================================================//
		//==================================== PRIVATE FUNCTIONS ========================================//
		//===============================================================================================//

		private:

	};
} // namespace Clide

#endif // #ifndef CLIDE_COMM_H

// EOF
