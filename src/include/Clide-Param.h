//!
//! @file 		Clide-Param.h
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/04/02
//! @brief 		 
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

#ifndef CLIDE_PARAM_H
#define CLIDE_PARAM_H

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

//! @brief		Holds all parameter variables
//! @details	Object of this type is created when RegisterParam() is called.
class Param
{
	private:
		//! @brief		Common code for constructors
		void Init(bool (*callBackFunc)(char *paramVal), const char* description);
	public:
	
		//===============================================================================================//
		//======================================== CONSTRUCTOR ==========================================//
		//===============================================================================================//
		
		//! @brief		1st overloaded constructor
		//! @details	Automatically sets the function pointer to NULL
		Param(const char* description);
		
		//! @brief		2nd overloaded constructor
		Param(bool (*callBackFunc)(char *paramVal), const char* description);
		
		
		//! Description of a parameter. Used with the "-h", "--help" flags.
		char* description;
		//! String value of parameter. 
		//! Parameters have no names
		char value[clideMAX_STRING_LENGTH];
		//! Optional callback function for when parameter is discovered.
		//! Function is called before the callback function for the command that it 
		//! was sent in is called.
		bool (*callBackFunc)(char* paramVal);
};

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


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_H

// EOF
