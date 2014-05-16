//!
//! @file 			Cmd.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/03/19
//! @last-modified 	2014/05/16
//! @brief 			Contains the command object, which can be registered with the RX or TX controller (or both).
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CMD_H
#define CLIDE_CMD_H

// Added this to prevent circular references
namespace Clide
{
	class Cmd;
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System headers
#include <stdint.h>
#include <vector>
#include <string>

// User libraries
#include "../lib/slotmachine-cpp/api/Slotmachine.hpp"

// User headers
#include "Config.hpp"		//!< Config options
#include "Param.hpp"		//!< For the Param() object
#include "Option.hpp"		//!< For the Option() object
#include "Comm.hpp"    		//!< Used for save a reference to the parent comm object in each cmd object.
#include "CmdGroup.hpp"

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
			
			//! @brief		Constructor with function callback
			//! @param		name			This is the string that is matched with the first argument in
			//!								a command-line message.
			//! @param		callBackFunc	The function to call when command is received.
			//! @param		description		Used when the "help" command or "-h" option is called.
			Cmd(
				std::string name,
				bool (*callBackFunc)(Cmd* foundCmd),
				std::string description);
/*
			//! @brief		Constructor with function callback
			//! @param		name			This is the string that is matched with the first argument in
			//!								a command-line message.
			//! @param		callBackFunc	The function to call when command is received.
			//! @param		description		Used when the "help" command or "-h" option is called.
			Cmd(
				const char* name,
				bool (*callBackFunc)(Cmd* foundCmd),
				const char *description);*/

			//! @brief		Constructor with method callback.
			//! @param		name			This is the string that is matched with the first argument in
			//!								a command-line message.
			//! @param		methodCallback	The method to call when command is received.
			//! @param		description		Used when the "help" command or "-h" option is called.
			Cmd(
				std::string name,
				SlotMachine::Callback<void, Cmd*> methodCallback,
				std::string description);
				
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
			
			//! @brief		Use to find a particular option which has been registered with the command.
			//! @param		shortOptionName		The short option name to look for.
			//! @returns	A pointer to the option if it finds a match, otherwise nullptr.
			//! @sa			FindOptionByLongName
			Option* FindOptionByShortName(char shortOptionName);

			//! @brief		Use to find a particular option which has been registered with the command.
			//! @param		longOptionName		The long option name to look for.
			//! @returns	A pointer to the option if it finds a match, otherwise nullptr.
			//! @sa			FindOptionByShortName
			Option* FindOptionByLongName(std::string longOptionName);

			//! @brief		Returns the number of options registered to the command which have long option names.
			//! @returns	Number of options with long options names (i.e. longName != NULL).
			uint32_t NumLongOptions();
			
			//! @brief		Adds the command to the provided command group.
			//! @param		cmdGroup	Pointer to the command group you want the command added to.
			void AddToGroup(CmdGroup *cmdGroup);

			//! @brief		Returns the number of command groups that the command belongs to.
			uint32_t GetNumCmdGroups();

			//! @brief		Returns a specific command group that the command belongs to, based of an index.
			CmdGroup* GetCmdGroup(uint32_t cmdGroupNum);

			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//
			
			//! @brief		The command name. Used for recognising command in command-line input. 
			//! @details	This must be the first word sent on the command-line, followed by a space.
			std::string name;
			
			//! @brief		Points to the description. Used when the help command is called.
			std::string description;
			
			//! @brief 		Vector of pointers to command parameters. Parameters are created external to Clide.
			std::vector<Param*> paramA;
			
			//! @brief		Remembers the number of parameters
			//uint32_t numParams;
			
			//! @brief		Vector of pointers to options. Options are created external to Clide.
			std::vector<Option*> optionA;
			
			//! @brief		Remembers the number of options
			//uint32_t numOptions;
			
			//! @brief		Optional callback function for when command is discovered. 
			//! @details	Called after all callback functions for individual options are executed.
			bool (*functionCallback)(Cmd* foundCmd);
			
			//! @brief		Method (member function) callback for when the command is detected.
			SlotMachine::Callback<void, Cmd*> methodCallback;

			//! @brief		True if command was detected the last time Rx.Run() was called.
			//! @details	You can use this for basic determination if a command was received,
			//!				without having to use a callback function.
			//! @note		This flag is reset for ALL commands every time Rx.Run() is called.
			bool isDetected;
			
			//! @brief		The parent Comm object that this command is registered to. Could either be a
			//!				Tx or Rx object.
			Comm* parentComm;

			//! @brief		A pointer to an array of pointers to CmdGroup objects, which signify which command groups this command belongs to.
			std::vector<CmdGroup*> cmdGroupA;

			//uint32_t numCmdGroups;

		protected:

			//===============================================================================================//
			//====================================== PROTECTED METHODS ======================================//
			//===============================================================================================//

			//! @brief		Used for constructor shared-code (called by all constructors).
			//! @details	Initialises everything except the callback, which is done in the calling constructor,
			//!				depending on whether it is a function or a method.
			void Init(std::string name, std::string description);
		
	};


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_H

// EOF
