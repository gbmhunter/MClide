//!
//! @file 		PowerString-Split.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/10
//! @brief 		Powerful string manipulation functions.
//! @details
//!		<b>Last Modified:			</b> 2013/05/14					\n
//!		<b>File Version:			</b> v1.0.0.0					\n
//!		<b>Company:					</b> CladLabs					\n
//!		<b>Project:					</b> Free Code Libraries		\n
//!		<b>Language:				</b> C++						\n
//!		<b>Compiler:				</b> GCC						\n
//! 	<b>uC Model:				</b> PSoC5						\n
//!		<b>Computer Architecture:	</b> ARM						\n
//! 	<b>Operating System:		</b> FreeRTOS v7.2.0			\n
//!		<b>Documentation Format:	</b> Doxygen					\n
//!		<b>License:					</b> GPLv3						\n
//!
//! See PowerString-Split.h for more information.
//!

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

#ifdef __cplusplus
extern "C" {
#endif

// PSoC includes
#include <device.h>

// System includes
#include <stdio.h>		// snprintf()

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "./FreeRTOS/FreeRTOS-Plus-CLI/FreeRTOS_CLI.h"

#ifdef __cplusplus
}
#endif

// User includes
#include "./Comms/include/UartDebug.h"
#include "./Comms/include/UartComms.h"
#include "PowerString-Split.h"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace PowerString
{

//===============================================================================================//
//==================================== PRIVATE DEFINES ==========================================//
//===============================================================================================//

// none

//===============================================================================================//
//=================================== PRIVATE TYPEDEF's =========================================//
//===============================================================================================//

// none

//===============================================================================================//
//============================= PRIVATE VARIABLES/STRUCTURES ====================================//
//===============================================================================================//

// none

//===============================================================================================//
//================================== PRIVATE FUNCTION PROTOTYPES ================================//
//===============================================================================================//

// none

//===============================================================================================//
//===================================== PUBLIC FUNCTIONS ========================================//
//===============================================================================================//


char* Split::Run(char *s, const char *delim)
{
	static char *last;

	return Int(s, delim, &last, '\"');
}


char* Split::Int(char *s, const char *delim, char **last, char delimiterNull)
{
	char *spanp;
	char c, sc;
	char *tok;
	bool delimitersNulled = false;

	// Return if null
	if (s == NULL && (s = *last) == NULL)
		return (NULL);

	
	 // Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 
	RESTART:
	
	// Get character
	c = *s++;
	
	// Iterates through delimiters
	// spanp initially = first delim
	// Goes until delim string = null
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) 
	{
		// Compare with delimiters
		if (c == sc)
			goto RESTART;
		else if (c == delimiterNull)
			delimitersNulled = !delimitersNulled;
	}

	// Leading delimiters removed, see if next character is null
	if (c == 0)
	{		
		// No non-delimiter characters
		*last = NULL;
		return (NULL);
	}
	
	// Remember string position - 1 since s has already been incremented
	tok = s - 1;
	
	
	// Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	//Note that delim must have one NUL; we stop if we see that, too.
	for (;;)
	{
		// Go to next character in string
		c = *s++;
		
		if(c == delimiterNull)
			delimitersNulled = !delimitersNulled;
		
		if(!delimitersNulled)
		{
			// Check each delimiter
			spanp = (char *)delim;
			do 
			{
				// Assign sc as first delimiter to check for,
				// and then compare with the character
				if ((sc = *spanp++) == c) 
				{
					if (c == 0)
						s = NULL;
					else
						s[-1] = 0;
					*last = s;
					return (tok);
				}
			} while (sc != 0);
		}
	}
	// NOTREACHED 
}

//===============================================================================================//
//==================================== PRIVATE FUNCTIONS ========================================//
//===============================================================================================//

// none

} // namespace PowerString