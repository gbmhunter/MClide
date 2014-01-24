//!
//! @file 			RxBuff.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/09
//! @last-modified 	2014/01/21
//! @brief 			An input buffer for the Rx engine. This can accept a stream of characters and call Rx::Go when the CR character is detected.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

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
#include "../include/Config.hpp"
#include "../include/Global.hpp"
#include "../include/Print.hpp"
#include "../include/Rx.hpp"
#include "../include/RxBuff.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//===============================================================================================//
	//====================================== PUBLIC METHODS ========================================//
	//===============================================================================================//

	// Constructor
	RxBuff::RxBuff(Rx* rxController)
	{
		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			Print::debugPrintCallback.Execute("CLIDE: RxBuff constructor called...\r\n");
		#endif

		// Initialise class variables
		this->rxController = rxController;

		// Set buffer write location to 0
		this->buffWritePos = 0;

		// Clear buffer
		memset(this->buff, '\0', sizeof(this->buff));

		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			Print::debugPrintCallback.Execute("CLIDE: RxBuff constructor finished.\r\n");
		#endif

	}

	bool RxBuff::Write(const char* characters)
	{
		// Variable for remembering where we are up in reading characters
		uint32_t characterReadPos = 0;

		// Made own copy function, rather than strcpy(), because extra functionality is needed
		while(characters[characterReadPos] != '\0')
		{

			// Check for buffer full condition
			if(this->buffWritePos >= sizeof(this->buff) - 1)
			{
				#if(clide_DEBUG_PRINT_ERROR == 1)
					Print::debugPrintCallback.Execute("CLIDE: Error. RxBuff::buff is full, not all characters could be written to it!.\r\n");
				#endif
				// Write null character to end of full buffer
				this->buff[this->buffWritePos] = '\0';
				return false;
			}

			// Now check to see if this was the end-of-command character
			if(characters[characterReadPos] == clide_END_OF_COMMAND_CHAR)
			{
				#if(clide_DEBUG_PRINT_VERBOSE == 1)
					Print::debugPrintCallback.Execute("CLIDE: End of command character detected, calling Rx::Run().\r\n");
				#endif

				// End of command character found! Send this to Rx!
				// Note that the end-of-command character is not part of
				rxController->Run(this->buff);

				// Now clear buffer, doesn't need to be the whole thing, but why not for safety?
				memset(this->buff, '\0', sizeof(this->buff));

				// Reset position
				this->buffWritePos = 0;

				// Increment character read pos
				characterReadPos++;

			}
			else	// Character was not the end-of-command character, write to buffer
			{
				#if(clide_DEBUG_PRINT_VERBOSE == 1)
					Print::debugPrintCallback.Execute("CLIDE: Writing to RxBuff::buff.\r\n");
				#endif

				this->buff[this->buffWritePos] = characters[characterReadPos];

				// Increment buffer write location by 1
				this->buffWritePos++;

				// Increment character read pos
				characterReadPos++;
			}

		}

		#if(clide_DEBUG_PRINT_VERBOSE == 1)
			Print::debugPrintCallback.Execute("CLIDE: RxBuff::Write() has finished writing chars to RxBuff::buff, no end-of-command character found.\r\n");
		#endif

		// Null character in input detected, write null to buff
		this->buff[this->buffWritePos] = '\0';

		// Do not increment write location pointer, so that any more incoming data overwrites this null pointer

		// If code go here, all characters must of been written successfully to buff
		return true;
	}

} // namespace Clide

// EOF
