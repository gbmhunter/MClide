//!
//! @file 		Clide-Option.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		 
//! @details
//!				See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_OPTION_H
#define CLIDE_OPTION_H

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//! @brief		Holds all option variables
	//! @details	Object of this type is created when RegisterOption() is called.
	class Option
	{
		
		public:
		
			//===============================================================================================//
			//=================================== CONSTRUCTORS/DESTRUCTOR ===================================//
			//===============================================================================================//
		
			//! @brief		Register an option with a command
			//! @param		optionName		The character to look for in the command-line string.
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @details	Overload 1
			Option(
				const char* optionName,
				bool (*callBackFunc)(char *optionVal));

			//! @brief		Register an option with a command.
			//! @details	Overload 2, associatedValue set to true.
			//! @param		optionName		The character to look for in the command-line string.
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @param		description		Used when help is requested.
			Option(
				const char* optionName,
				bool (*callBackFunc)(char *optionVal),
				const char* description);
		
			//! @brief		Register an option with a command.
			//! @details	Overload 2
			//! @param		optionName		The character to look for in the command-line string.
			//! @param		callBackFunc	Call-back function which is called when option is discovered.
			//!								Can be set to NULL.
			//! @param		description		Used when help is requested.
			//! @param		associatedValue	Set to true if option has an associated value
			Option(
				const char* optionName,
				bool (*callBackFunc)(char *optionVal),
				const char* description,
				bool associatedValue);
		
			//! @brief		Destructor.
			//! @details	Deallocates memory.
			~Option();
		
			//===============================================================================================//
			//========================================= PUBLIC METHODS ======================================//
			//===============================================================================================//
			
			// none
			
			//===============================================================================================//
			//======================================= PUBLIC VARIABLES ======================================//
			//===============================================================================================//
		
			//! @brief		Name of option
			char* name;
			
			//! @brief		Description of an option. Used with the "-h", "--help" flags.
			char* description;
			
			//! @brief		The value of the option. Assigned to when receiving commands.
			//! @todo		Change so that dynamically allocated
			char value[clideMAX_STRING_LENGTH];
			
			//! @brief		Optional callback function for when option is discovered.
			//! @details	Function is called before the callback function for the command that it 
			//! 			was sent in is called.
			bool (*callBackFunc)(char* optionVal);
			
			//! @brief		True if option was present the last time the command it is registered to was detected.
			//! @note		This is cleared whenever the command is received again by the RX controller.
			bool isDetected;
			
			//! @brief		Set to true if option has an associated value. Default is false.
			bool associatedValue;
			
		private:
		
			void Init(
				const char* optionName,
				bool (*callBackFunc)(char *optionVal),
				const char* description,
				bool associatedValue);
	};

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	// none			

	//===============================================================================================//
	//=================================== PUBLIC TYPEDEFS ===========================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//================================== PUBLIC VARIABLES/STRUCTURES ================================//
	//===============================================================================================//

	// none

	//===============================================================================================//
	//=================================== PUBLIC FUNCTION PROTOTYPES ================================//
	//===============================================================================================//


} // namespace Clide

#endif	// #ifndef CLIDE_OPTION_H

// EOF
