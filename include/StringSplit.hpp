//!
//! @file 			StringSplit.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-04-10
//! @last-modified 	2014-10-07
//! @brief 			Features a string split function which ignores delimiters inside quotation marks.
//! @details
//!					See README.rst in the repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef MCLIDE_STRING_SPLIT_H
#define MCLIDE_STRING_SPLIT_H

//===============================================================================================//
//==================================== FORWARD DECLARATION ======================================//
//===============================================================================================//

namespace MbeddedNinja
{
	namespace MClideNs
	{
		class StringSplit;
	}
}

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// none

namespace MbeddedNinja
{
	namespace MClideNs
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

	} // namespace MClide
} // namespace MbeddedNinja

#endif	// #ifndef MCLIDE_STRING_SPLIT_H

// EOF
