//!
//! @file 			Print.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/03/19
//! @last-modified 	2014/01/24
//! @brief 			Contains callbacks for port-specific print operations.
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_PRINT_H
#define CLIDE_PRINT_H

#include "../lib/slotmachine-cpp/api/Slotmachine.hpp"		//!< Callbacks.

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	#define STR_EXPAND(tok) #tok
	#define STR(tok) STR_EXPAND(tok)
	
	#if(defined __linux__)
		#define ClidePort_PF_UINT32_T		u
		#define ClidePort_PF_INT32_T		i
		#define ClidePort_PF_CHAR_T			c
	#elif(CY_PSOC5)
		#define ClidePort_PF_UINT32_T		lu
		#define ClidePort_PF_INT32_T		li
		#define ClidePort_PF_CHAR_T			li
	#else
		#warning No platform defined. Using defaults.
		#define ClidePort_PF_UINT32_T		u
		#define ClidePort_PF_INT32_T		i
		#define ClidePort_PF_CHAR_T			c
	#endif
		
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

	class Print
	{

		public:
		
			//! @brief		Callback for debug messages.
			static SlotMachine::Callback<void, const char*> debugPrintCallback;

			//! @brief		Callback for command-line messages.
			static SlotMachine::Callback<void, const char*> cmdLinePrintCallback;
			
			//! @brief		Callback for error messages.
			static SlotMachine::Callback<void, const char*> errorPrintCallback;
	};

} // namespace Clide

#endif	// #ifndef CLIDE_PRINT_H

// EOF
