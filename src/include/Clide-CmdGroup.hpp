//!
//! @file 			Clide-CmdGroup.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/06
//! @last-modified 	2014/01/06
//! @brief 			The CmdGroup object is used to create "groups" that commands can belong too, which can be then be utilised to display selective help information.
//! @details
//!					See README.rst in root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_CMD_GROUP_H
#define CLIDE_CMD_GROUP_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

#include <stdint.h>
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{

	//! @brief		This class is used to create CmdGroup objects that can be assigned to commands, so that they belong to that group.
	//! @details
	class CmdGroup
	{	
		
	public:
			
		//===============================================================================================//
		//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
		//===============================================================================================//
			
		//! @brief		Constructor.
		CmdGroup(const char* name, const char* description);

		//===============================================================================================//
		//========================================= PUBLIC METHODS ======================================//
		//===============================================================================================//


		
		//===============================================================================================//
		//======================================= PUBLIC VARIABLES ======================================//
		//===============================================================================================//
			
		//! @brief		The command group name. Used for recognising the command group in command-line input.
		//! @details
		const char* name;
		
		//! @brief		The command group description.
		const char* description;


	protected:

		// none

	};


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_GROUP_H

// EOF
