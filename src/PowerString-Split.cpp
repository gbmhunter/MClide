//!
//! @file 		PowerString-Split.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/10
//! @brief 		Powerful string manipulation functions.
//! @details	
//!				See README.rst in root dir for more information.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//========================================= INCLUDES ============================================//
//===============================================================================================//

// System includes
#include <stdio.h>		// snprintf()

// User includes
#include "./include/Clide-Port.hpp"
#include "./include/PowerString-Split.hpp"

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