//!
//! @file 			Print.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-03-19
//! @last-modified 	2014-08-31
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

#include "slotmachine-cpp/api/Slotmachine.hpp"		//!< Callbacks.

#include "Preprocessor.hpp"									//!< STR() macro

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//==================================== PUBLIC DEFINES ===========================================//
	//===============================================================================================//

	
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
		
			enum class DebugPrintingLevel
			{
				GENERAL,
				VERBOSE
			};

			static bool enableDebugInfoPrinting;
			static bool enableCmdLinePrinting;
			static bool enableErrorPrinting;

			static void AssignCallbacks(
					SlotMachine::Callback<void, const char*> debugPrintCallback,
					SlotMachine::Callback<void, const char*> cmdLinePrintCallback,
					SlotMachine::Callback<void, const char*> errorPrintCallback)
			{
				Print::debugPrintCallback = debugPrintCallback;
				Print::cmdLinePrintCallback = cmdLinePrintCallback;
				Print::errorPrintCallback = errorPrintCallback;
			}

			static DebugPrintingLevel debugPrintingLevel;

			static void PrintDebugInfo(const char* msg, DebugPrintingLevel debugPrintingLevel);
			static void PrintError(const char* msg);
			static void PrintToCmdLine(const char* msg);

		private:

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
