//!
//! @file 			Print.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-03-19
//! @last-modified 	2014-10-07
//! @brief 			Contains callbacks for port-specific print operations.
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MCLIDE_PRINT_H
#define MCLIDE_PRINT_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{
		class Print;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include "MCallbacks/api/MCallbacksApi.hpp"		//!< Callbacks.

#include "Preprocessor.hpp"									//!< STR() macro

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

namespace MbeddedNinja
{
	namespace MClideNs
	{

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
						MCallbacks::Callback<void, const char*> debugPrintCallback,
						MCallbacks::Callback<void, const char*> cmdLinePrintCallback,
						MCallbacks::Callback<void, const char*> errorPrintCallback)
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
				static MCallbacks::Callback<void, const char*> debugPrintCallback;

				//! @brief		Callback for command-line messages.
				static MCallbacks::Callback<void, const char*> cmdLinePrintCallback;

				//! @brief		Callback for error messages.
				static MCallbacks::Callback<void, const char*> errorPrintCallback;

		};

	} // namespace MClide
} // namespace MbeddedNinja

#endif	// #ifndef MCLIDE_PRINT_H

// EOF
