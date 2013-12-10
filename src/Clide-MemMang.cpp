//!
//! @file 			Clide-MemMang.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/04/02
//! @last-modified 	2013/12/10
//! @brief 			Memory management functions for Clide.
//! @details
//!					See README.rst in repo root dir for more information.

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
#include <string.h>		// strlen(), strcpy()

// User includes
#include "./include/Clide-MemMang.hpp"
#include "./include/Clide-Port.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{
	//===============================================================================================//
	//===================================== MEMBER FUNCTIONS ========================================//
	//===============================================================================================//

	char* MemMang::MallocString(const char* string)
	{
		uint32_t stringLen = strlen(string);
		
		// Create memory for description and store
		char* newString = (char*)calloc(1, stringLen + 1);
		
		// This is safe since newString will be of same size
		strcpy(newString, string);
		
		// Return pointer to new string
		return newString;
	}

	void* MemMang::AppendNewArrayElement(void* arrayStart, uint32_t currNumElements, uint32_t sizeOfElement)
	{
		#if(DEBUG_PRINT_VERBOSE)
			char tempBuff[100];
			snprintf(tempBuff, sizeof(tempBuff), "MEM: Curr num elements = %lu", currNumElements);
			UartDebug::PutString(tempBuff);
			snprintf(tempBuff, sizeof(tempBuff), "MEM: Size of element = %lu", sizeOfElement);
			UartDebug::PutString(tempBuff);
		#endif

		// Create a new option at end of option array
		arrayStart = realloc(arrayStart , (currNumElements+1)*sizeOfElement);
		
		// Check if malloc was successful
		if(arrayStart == NULL)
			return NULL;
		
		// Cast to char pointer to get around the "arthimetic on type void* compiler warning)
		char* arrayStartChar = (char*)arrayStart;
		// Set to 0
		memset(arrayStartChar + (currNumElements*sizeOfElement), '\0', sizeOfElement);
		// Return pointer to the start of array (realloc() could of changed this)
		return arrayStart;
	}
} // namespace Clide
