//!
//! @file 		Clide-Cmd.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/03/19
//! @brief 		Contains the command object, which can be registered with 
//!				the RX or TX controller (or both).
//! @details
//!				See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CMD_H
#define CLIDE_CMD_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//! @brief		Holds all command variables, including parameters and options
	//! @details	Object of this type is created with malloc()
	//!				when RegisterCmd() is called, and removed
	//!				with RemoveCmd(). A command needs to be registered to a controller.
	class Cmd
	{	
		
		public:
			
			//===============================================================================================//
			//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
			//===============================================================================================//
			
			//! @brief		Constructor
			//! @param		name			This is the string that is matched with the first argument in
			//!								a command-line message.
			//! @param		callBackFunc	The function to call when command is received. Any specific option
			//!								or parameter callbacks which are part of this command
			//!								are called before this one.
			//! @param		description		Used when the "help" command or "-h" option is called.
			Cmd(
				const char *name,
				bool (*callBackFunc)(Cmd* foundCmd),
				const char *description);
				
			//! @brief		Destructor. Deallocates memory.
			~Cmd();
			
			//===============================================================================================//
			//========================================= PUBLIC METHODS ======================================//
			//===============================================================================================//
			
		
			//! @brief		Register a parameter with a cmd.
			//! @param		param	Parameter to register.
			void RegisterParam(Param* param);
			
			//! @brief		Register a option with a cmd.
			//! @param		option	Option to register.
			void RegisterOption(Option* option);
			
			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//
			
			//! @brief		The command name. Used for recognising command in command-line input. 
			//! @details	This must be the first word sent on the command-line, followed by a space.
			char* name;
			
			//! @brief		Points to the description. Used when the help command is called.
			char* description;
			
			//! @brief 		Pointer to an array of pointers to command parameters. Parameters are dynamically allocated.
			Param** paramA;
			
			//! @brief		Remembers the number of parameters
			uint32_t numParams;
			
			//! @brief		Pointer to an array of pointers to options. Options are dynamically allocated.
			Option** optionA;
			
			//! @brief		Remembers the number of options
			uint32_t numOptions;
			
			//! @brief		Optional callback function for when command is discovered. 
			//! @details	Called after all callback functions for individual options are executed.
			bool (*callBackFunc)(Cmd* foundCmd);
			
			//! @brief		True if command was detected the last time Rx.Run() was called.
			//! @details	You can use this for basic determination if a command was received,
			//!				without having to use a callback function.
			//! @note		This flag is reset for ALL commands every time Rx.Run() is called.
			bool isDetected;
			
		private:
		
		// none
	};


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_H

// EOF
