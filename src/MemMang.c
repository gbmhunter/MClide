//!
//! @file 		MemMang.c
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Memory management functions.
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
//! See MemMang.h for more information.
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
#include <stdlib.h>		// realloc(), malloc(), free()
#include <cctype>		// isalnum() 

#include <getopt.h>		// getopt()	

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

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MemMang
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

char* MallocString(const char* string)
{
	uint32 stringLen = strlen(string);
	
	// Create memory for description and store
	char* newString = (char*)calloc(1, stringLen + 1);
	
	// This is safe since newString will be of same size
	strcpy(newString, string);
	
	// Return pointer to new string
	return newString;
}


void* AppendNewArrayElement(void* arrayStart, uint32 currNumElements, uint32 sizeOfElement)
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

//===============================================================================================//
//==================================== PRIVATE FUNCTIONS ========================================//
//===============================================================================================//

// none

} // namespace Clide