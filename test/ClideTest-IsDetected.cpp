//!
//! @file 		ClideTest-Param.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains test functions for Clide command isDetected flag.
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
	SUITE(CmdDetectedTests)
	{
		using namespace Clide;

		bool Callback1(Cmd *cmd)
		{
			
			return true;
		}

		TEST(BasicIsDetectedTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest1("test1", &Callback1, "Test command 1.");
			
			// Register commands
			rxController.RegisterCmd(&cmdTest1);
			
			// Create fake input buffer
			char rxBuff1[50] = "test1";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			// Make sure cmd1 is true, cmd2 is false
			CHECK_EQUAL(true, cmdTest1.isDetected);	
		}
		
		TEST(IsDetectedGetsResetTest)
		{
			Rx rxController;
			Tx txController;
			
			Cmd cmdTest1("test1", &Callback1, "Test command 1.");
			Cmd cmdTest2("test2", &Callback1, "Test command 2.");
			
			// Register commands
			rxController.RegisterCmd(&cmdTest1);
			rxController.RegisterCmd(&cmdTest2);
			
			// Create fake input buffer
			char rxBuff1[50] = "test1";
			
			// Run rx controller
			rxController.Run(rxBuff1);
			
			// Make sure cmd1 is true, cmd2 is false
			CHECK_EQUAL(true, cmdTest1.isDetected);
			CHECK_EQUAL(false, cmdTest2.isDetected);
			
			// Create input buffer
			char rxBuff2[50] = "test2";
			
			// Run rx controller
			rxController.Run(rxBuff2);
			
			// Make sure cmd1 is false, cmd2 is true
			CHECK_EQUAL(false, cmdTest1.isDetected);
			CHECK_EQUAL(true, cmdTest2.isDetected);
			
			// TEST ALL CMDS ARE CLEARED
			
			// Create bogus input buffer
			char rxBuff3[50] = "test3";
			
			// Run rx controller
			rxController.Run(rxBuff3);
			
			// Make sure cmd1 is false, cmd2 is true
			CHECK_EQUAL(false, cmdTest1.isDetected);
			CHECK_EQUAL(false, cmdTest2.isDetected);
		}
	} // SUITE(CmdDetectedTests)
} // namespace ClideTest

