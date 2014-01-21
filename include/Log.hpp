//!
//! @file 			Log.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/13
//! @last-modified 	2014/01/14
//! @brief 			A class to create an error object, used for reporting Clide errors.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_LOG_H
#define CLIDE_LOG_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System
#include <stdint.h>

// User
#include "Config.hpp"
#include "Port.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	enum class Severity
	{
		NOTIFICATION,
		WARNING,
		ERROR
	};

	//! @brief		An input buffer for the Rx engine. It can accept a stream of characters and call Rx::Go() when the clide_END_OF_COMMAND_CHAR character is detected.
	template <class logIdType> class Log
	{
	
		public:
		
			//===============================================================================================//
			//=================================== PUBLIC VARIABLES/STRUCTURES ===============================//
			//===============================================================================================//
			
			logIdType logId;

			//! @brief		Holds the log message
			char* msg;

			//! @brief		Tells the user the severity of the log.
			Severity severity;

			
			//===============================================================================================//
			//======================================= PUBLIC METHODS ========================================//
			//===============================================================================================//

			//! @brief		Constructor
			Log();

		private:
			
			//===============================================================================================//
			//================================== PRIVATE VARIABLES/STRUCTURES ===============================//
			//===============================================================================================//



			//===============================================================================================//
			//======================================= PRIVATE METHODS =======================================//
			//===============================================================================================//

			// none

	};

	// Constructor
	template <class logIdType>
	Log<logIdType>::Log()
	{
		#if(clideDEBUG_PRINT_VERBOSE == 1)
			Port::DebugPrint("CLIDE: ErrorObj constructor called...\r\n");
		#endif



		#if(clideDEBUG_PRINT_VERBOSE == 1)
			Port::DebugPrint("CLIDE: ErrorObj constructor finished.\r\n");
		#endif

	}

	// none

} // namespace Clide

#endif	// #ifndef CLIDE_LOG_H

// EOF
