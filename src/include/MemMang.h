//!
//! @file 		MemMang.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		Memory management functions.
//! @details
//!				See README.rst in root dir.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MEM_MANG_H
#define MEM_MANG_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace MemMang
{

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

	//! @brief		Dynamically appends a new element onto the end of an array.
	//! @details	Uses dynamic memory allocation.
	//! @param		arrayStart 			Pointer to the start of the array
	//! @param		currNumElements 	The number of elements in the array
	//! @param		sizeofElement		The size (in bytes) of the individual elements in the array.
	//!									This can be found by using sizeof(arrayType_t)
	//! @returns	Pointer to new position of array[0]. Remember to cast back to the original type.
	void* AppendNewArrayElement(void* arrayStart, uint32_t currNumElements, uint32_t sizeOfElement);

	//! @brief		Essentially "copies" a string into a new memory location.
	//! @param		string				String to copy.
	//! @returns	Pointer to newly allocated and copied string.
	//! @public
	char* MallocString(const char* string);

} // namespace MemMang

#endif	// #ifndef MEM_MANG_H

// EOF
