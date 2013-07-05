//!
//! @file 		ClideTest-SpasticInput.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for stressing the input with spastic characters. The idea here
//!				is just to make sure no unexpected characters can cause Rx.Run() to crash.
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"

namespace ClideTest
{
	SUITE(SpasticInputTests)
	{
		using namespace Clide;

		static Cmd *_cmd = NULL;

		bool Callback(Cmd *cmd)
		{
			_cmd = cmd; 
			
			return true;
		}

		TEST(SpasticInputTest1)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "test !@#";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			// Just check to make sure execution gets to
			// this point
			CHECK(true);
		}
		
		TEST(SpasticInputTest2)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "!34 !@#";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			// Just check to make sure execution gets to
			// this point
			CHECK(true);
		}
		
		TEST(SpasticInputTest3)
		{
			
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest("test", &Callback, "A test command.");
			
			// Register command
			rxController.RegisterCmd(&cmdTest);
			
			// Create fake input buffer
			char rxBuff[50] = "#$^ &*()";
			
			_cmd = NULL;
			
			// Run rx controller
			rxController.Run(rxBuff);
			
			// Just check to make sure execution gets to
			// this point
			CHECK(true);
		}
		
	} // SUITE(OptionTests)
} // namespace ClideTest