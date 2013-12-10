//!
//! @file 			Clide-MemMang.hpp
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
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_MEM_MANG_H
#define CLIDE_MEM_MANG_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	class MemMang
	{
		public:
			//! @brief		Dynamically appends a new element onto the end of an array.
			//! @details	Uses dynamic memory allocation.
			//! @param		arrayStart 			Pointer to the start of the array
			//! @param		currNumElements 	The number of elements in the array
			//! @param		sizeofElement		The size (in bytes) of the individual elements in the array.
			//!									This can be found by using sizeof(arrayType_t)
			//! @returns	Pointer to new position of array[0]. Remember to cast back to the original type.
			static void* AppendNewArrayElement(void* arrayStart, uint32_t currNumElements, uint32_t sizeOfElement);

			//! @brief		Essentially "copies" a string into a new memory location.
			//! @param		string				String to copy.
			//! @returns	Pointer to newly allocated and copied string.
			//! @public
			static char* MallocString(const char* string);
	};

} // namespace Clide

#endif	// #ifndef CLIDE_MEM_MANG_H

// EOF
