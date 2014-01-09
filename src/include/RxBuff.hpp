//!
//! @file 			RxBuff.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2014/01/09
//! @last-modified 	2014/01/09
//! @brief 			An input buffer for the Rx engine. This can accept a stream of characters and call Rx::Go when the CR character is detected.
//! @details
//!					See README.rst in repo root dir for more info.

#ifndef __cplusplus
	#error Please build with C++ compiler
#endif

//===============================================================================================//
//======================================== HEADER GUARD =========================================//
//===============================================================================================//

#ifndef CLIDE_RX_BUFF_H
#define CLIDE_RX_BUFF_H

//===============================================================================================//
//========================================== INCLUDES ===========================================//
//===============================================================================================//

// System
#include <stdint.h>

// User
#include "Clide-Config.hpp"
#include "Clide-Param.hpp"
#include "Clide-Option.hpp"
#include "Clide-Cmd.hpp"
#include "Clide-Port.hpp"
#include "Clide-GetOpt.hpp"
#include "Clide-Comm.hpp"

//===============================================================================================//
//======================================== NAMESPACE ============================================//
//===============================================================================================//

namespace Clide
{
	//! @brief		Class deals with receiving of command-line strings and the decoding/processing of them.
	//! @details	This is one of the most important objects in the Clide library. Inherits from the Comm class.
	class RxBuff
	{
	
		public:
		
			//===============================================================================================//
			//==================================== CONSTRUCTORS/DESTRUCTOR ==================================//
			//===============================================================================================//
			
			//! @brief		Constructor
			RxBuff(Rx* rxController);
			
			//===============================================================================================//
			//======================================= PUBLIC METHODS ========================================//
			//===============================================================================================//

			//! @brief		Writes a null-terminated string of characters to the RxBuff.
			bool Write(char* characters);

		private:
			
			//===============================================================================================//
			//======================================= PRIVATE METHODS =======================================//
			//===============================================================================================//



			//===============================================================================================//
			//================================== PRIVATE VARIABLES/STRUCTURES ===============================//
			//===============================================================================================//

			//! @brief		Pointer to the rx controller RxBuff will send characters too once CR had been detected.
			Rx* rxController;

			//! @brief		Rx buffer for storing characters sent to RxBuff by Write().
			char buff[clide_RX_BUFF_SIZE];

			//! @brief		Pointer to current write location in buffer
			uint8_t buffWritePos;

	};


	// none

} // namespace Clide

#endif	// #ifndef CLIDE_RX_BUFF_H

// EOF
