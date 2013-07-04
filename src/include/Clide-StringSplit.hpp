//!
//! @file 		PowerString-Split.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/10
//! @brief 		Features a string split function which ignores delimiters inside quotation marks.
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

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_STRING_SPLIT_H
#define CLIDE_STRING_SPLIT_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	class StringSplit 
	{
		public:
			//! @brief		Based of strtok() function
			//! @details	Calls Int();
			static char* Run(char* s, const char* delim);
		private:
			//! @brief		Internal function called by Run();
			//! @details	Replaces "end of token" with null character and returns "start of token". Returns NULL
			//!				when it has finished processing string (e.g. reached NULL character).
			//! @param		s 		Input string
			//! @param 		*delim 	Delimiters
			static char* Int(char *s, const char *delim, char **last, char delimiterNull);
	};

} // namespace Clide

#endif	// #ifndef CLIDE_STRING_SPLIT_H

// EOF
