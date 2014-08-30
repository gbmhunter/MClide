//!
//! @file 			CmdGroup.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014/01/06
//! @last-modified 	2014/01/14
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
#include <string>

#include "Config.hpp"
#include "Param.hpp"
#include "Option.hpp"

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
		CmdGroup(std::string name, std::string description);

		//===============================================================================================//
		//========================================= PUBLIC METHODS ======================================//
		//===============================================================================================//


		
		//===============================================================================================//
		//======================================= PUBLIC VARIABLES ======================================//
		//===============================================================================================//
			
		//! @brief		The command group name. Used for recognising the command group in command-line input.
		//! @details
		std::string name;
		
		//! @brief		The command group description.
		std::string description;


	protected:

		// none

	};


} // namespace Clide

#endif	// #ifndef CLIDE_CMD_GROUP_H

// EOF
