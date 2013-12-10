==============================================================
Clide (Command Line Interface Development Environment) Library
==============================================================

.. image:: https://travis-ci.org/gbmhunter/Cpp-Clide.png?branch=master   
	:target: https://travis-ci.org/gbmhunter/Cpp-Clide

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/03/19
- Last Modified: 2013/10/12
- Version: v4.0.0.0
- Company: CladLabs
- Project: Free Code Libraries
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

Description
===========

A command-line style communication interface designed to make it easy to send messages and
data between two micro-controllers, a microcontroller and computer, or two computers, via
a serial interface that supports ASCII characters (e.g. UART, I2C, SPI).

Two functionally identical Clide projects exist, this one written in C++ for an embedded system,
and the other one (Cs-Clide) written in C# for running on a PC.

Uses a both human readable and computer readable format (POSIX.2 command-line style, with
GNU extensions) for easy implementation and debugging. 
Automatically generates UNIX-style help text
which is useful if system is being controlled by a human (see below).

Useful for working with and controlling embedded systems.

An example message takes the format of

::

	set-speed -rpm 2000\n

where set-speed is the command name, "-rpm" is an optional argument that specifies
that the value is in rpm, "2000" is a non-optional parameter which specifies the
speed, and "\n" is the new-line character which signifies the end of a message
(which is normally inserted automatically by command-lines when enter is pressed).

Another which uses long options is:

::

	on --led1==on

Uses dynamic memory allocation for creating commands/options/parameters e.t.c
Command data is stored in a contiguous block

All text is case-sensitive. It is recommended to use lower-case only to
follow the POSIX command-line style.

Special support for the "help" command, and `-h`, `--help` flags for every registered
command. No special support other UNIX commands such as `man`, `whatis` or `info`
'help' is a special command which can be implemented by calling RegisterHelpCmd().

Supports long options (GNU extension to the POSIX.2 standard).

Clide is not dependant on the getopt_long() function from the standard C-library,
it has it's own version.

Before writing code using Clide, you only need to include the single header file called "Clide-IncludeJustMe.hpp"\
which is found in ./src/include/.

External Dependencies
=====================
- <stdio.h> 	-> snprintf()
- <stdlib.h> 	-> realloc(), malloc(), calloc(), free()
- <cctype>		-> isalnum()

Packet Decoding Process (RX)
============================

When Rx.Run() is called...

- Remove all non-alphanumeric characters from the start of the packet
- Split packet into separate arguments
- Make sure received command is registered. If so, set cmdReceived = TRUE. It not, return FALSE.
- Extract options and values (if present), execute option callback functions
- Check all parameters are present
- Execute parameter callback functions
- Execute command callback function

Issues
======

See GitHub Issues.

Limitations
===========

- Maximum number of commands: 256
- Maximum number of parameters or options per command: 256
- Maximum string length of a command name, option name/value, parameter value: clideMAX_STRING_LENGTH

Usage
=====

In main.c add...

::

	#include "./src/include/Clide-IncludeJustMe.hpp"

	using namespace Clide;

	
	// Create RX Clide object
	Rx rxController;
	
	
	// Create call-back function that is automatically called when
	// registered command is recieved
	bool SetSpeedCmd(Cmd* cmd)
	{
		// Extract parameter from received command
		float speed = atof(cmd->paramA[0]->value);
		
		// Call some function to do stuff with parameter
		Motor.SetSpeed(speed);
	}
	
	// Create call-back function for help command. The help functionality
	// is automatically provided by calling rxController.PrintHelp()
	// (prints help info to the command line, if being controlled
	// by a human).
	bool HelpCmd(Cmd* cmd)
	{
		#if(PRINT_DEBUG_COMMS_INTERFACE == 1)
			UartDebug::PutString("COMMS: Help command received.\r\n");
		#endif

		rxController.PrintHelp();

		return true;
	}
	

	
	int main()
	{
		// Create Parameter
		Param speed("The desired speed.");
		// Create command
		Cmd setSpeedCmd("set-speed", &SetSpeedCmd, "Sets the speed.");
		// Register parameter with command
		setSpeedCmd.RegisterParam(&speed);
		// Register command with RX (can also be registered with TX controller if desired).
		rxController.RegisterCmd(&setVelocityCmd);
		
		// Register help command
		Cmd help("help", &HelpCmd, "Prints help info.");
		rxController.RegisterCmd(&help);
		
		// Infinite loop
		for(;;)
		{
			char rxChar;						//!< Memory to hold incoming character
			
			// Wait indefinetly for byte to be received on rx queue of the comms UART (blocking)
			UartComms::GetChar(&rxChar);
			
			if( rxChar == '\r' )
			{
				// Line of text has been entered
				
				// Send command to Clide
				rxController.Run((char*)rxBuffer);

				// Clear the input string ready 
				// to receive the next command.
				rxBufferPos = 0;
				memset(rxBuffer, 0x00, sizeof(rxBuffer));
				
				// Clear tx buffer also
				memset(txBuffer, 0x00, sizeof(txBuffer));
				
			}
			else
			{
				// A character was entered.  It was not a new line so it is
				// placed into the input buffer.  When \n is detected,
				// the complete string will be passed to Clide.
				if( rxBufferPos < sizeof(rxBuffer))
				{
					rxBuffer[rxBufferPos] = rxChar;
					rxBufferPos++;
				}
				else
				{
					UartDebug::PutString("COMMS: Maximum input string length reached.\r\n");
				}
			}
		}
	}
	
**Port Specific Code**

::

	// Fill in port-specific code in template functions in Clide-Port.c
	CmdLinePrint(){ ... }
	DebugPrint(){ ... }
	
Changelog
=========

======== ========== ===================================================================================================
Version  Date       Comment
======== ========== ===================================================================================================
v4.0.0.0 2013/12/10 Added eclipse project files. Formatted Clide-Config.hpp. Disabled debug print macros except for errors.
v3.2.0.0 2013/08/25 Added .travis.yml file in root directory for Travis CI compatibility. Added Travis CI build status image to top of README.
v3.1.4.0 2013/07/12 Added unit test for an empty command.
v3.1.3.0 2013/07/12 Removed getopt() reference from Clide-MemMang.cpp.
v3.1.2.0 2013/07/12 Added unit tests for multiple spaces between arguments in a command (ClideTest-MultipleSpacesBetweenArguments.cpp).
v3.1.1.0 2013/07/11 Added compiler warning if no port-specific functions are defined in Clide-Port.cpp functions.
v3.1.0.0 2013/07/11 Added Clide-IncludeJustMe.hpp, which is a single header file the user can include to use the Clide library. Added note about it to README. Replaced all Clide includes in unit test files with the single include.
v3.0.1.0 2013/07/10 Removed reference to <getopt.h> in Clide-Rx.hpp.
v3.0.0.0 2013/07/10 Added own getopt() function (the Clide-GetOpt class), no longer dependant on C library for it.
v2.2.0.0 2013/07/09 Added continue if getopt_long() returned '?' character. Added Makefile command 'make clean-clide'.
v2.1.1.0 2013/07/09 Fixed non-portable use of '%u' in snprintf() in Rx::ValidateCmd(). Fixed other non-portable uses of snprint() and added more port-specific defines in Clide-Port.h. Removed RX code from Clide::Tx class. Added double braces around initialisers for two Rx::Run() variables. Changed optint to (optint - 1) when printing option which caused '?' to be returned from getopt_long(). Added unit tests for quotes and negative numbers.
v2.1.0.0 2013/07/09 Added unit tests for multiple Clide::Rx.Run() calls (ClideTest-MultipleRxRunCalls.cpp). Fixed long option index bug in Rx::BuildLongOptionStruct(). Fixed bug in getopt_long() reporting incorrect options by setting optint = 0 before run (explained in getopt.h). Fixed bug in Rx::ValidateOption() variable 'val' being initialised to 0, which was what was checked for after calling strcmp to see if there was a match.
v2.0.0.0 2013/07/08 Long options are now supported in the command-line interface (now used getopt_long). Various code to Option class and RX decoding has been added/changed to support this. Added Clide-Global.h. Deleted internal dependency section in README (not useful). Added mention of POSIX.2 standard in README. Fixed unit test that was failing (strcpy() was being passed a NULL). Added new Makefile option clean-ut, which just cleans the unit test code. Added unit tests for long options.
v1.6.4.0 2013/07/05 Added 'SpasticInput' unit tests. Added Doxygen '@brief' tags to documentation in `Clide-Cmd.h`. Added more documentation. Added C++ check to Clide-Port.cpp. Added port-specific code for PSoC5/5LP `printf()` functions in `Clide-Port.hpp`. Renamed namespace in Clide-MemMang from 'MemMang' to 'Clide'. Put MemMang functions inside a class. Added unit tests for commands with both parameters and options. 1 unit test currently failing.
v1.6.3.0 2013/07/05 Grouped all unit tests into test suites.
v1.6.2.0 2013/07/05 Re-added argsPtr assignment which was removed in last commit and caused Rx.Run() to crash on every call.
v1.6.1.0 2013/07/05 Added destructor debug messages. Add macro to enable/disable automatic help generation. Removed static global variables in Rx class and put them in Rx.Run() instead. This fixed the issues with some of the unit tests failing.
v1.6.0.0 2013/07/04 Deleted un-needed @public and @private comments. Put public objects first in classes. Added cmdDetected variable to Cmd object, and info about it to README. Formatted all-caps section titles in README correctly. Made Makefile file finding more automatic. Added more unit test files. Removed port-specific UartDebug function calls. Added destructor for Cmd object that frees up allocated memory. Renamed MemMang and PowerString-Split libraries to be part of Clide.
v1.5.0.0 2013/07/04 Added first unit tests (3 of them). They run automatically when 'make all' is called.
v1.4.1.0 2013/07/04 Fixed the '.h' includes to '.hpp'. Fixed 'make clean', it is now removing the correct files.
v1.4.0.0 2013/07/04 Renamed all .c files to .cpp and .h to .hpp. Automated some of the file finding processes in the Makefile.
v1.3.0.1 2013/07/03 Forgot to save README.rst.
v1.3.0.0 2013/07/03 Made Clide compilable on Linux. Added Makefile which compiles static Clide library, static UnitTest++ library, then runs unit test code. Added own getopt() file (doesn't work yet).
v1.2.2.0 2013/07/01 Deleted unnecessary header file includes from .c files.
v1.2.1.1 2013/06/29 Indented all namespace objects by one tab in all files.
v1.2.1.0 2013/06/25 Fixed lock-up on receiving empty message. Made tempBuff in Clide-Rx.c larger. Fixed a few spelling mistakes in README.
v1.2.0.2 2013/06/08 README is now in table format.
v1.2.0.1 2013/05/29 Removed C# notes in README (now in separate repo). Fixed README formatting issue. Fixed spelling mistakes.
v1.2.0.0 2013/05/29 Removed unneeded './cpp' root folder. Added unit test library UnitTest++ to './test/UnitTest++'"
v1.1.1.0 2013/05/15 Message "...not registered with command" in Clide-Rx.c was missing the last double quote, breaking the message format standard. Fixed.
v1.1.0.0 2013/05/14 Support for options with values in C++  library.
v1.0.0.0 2013/05/14 Initial version.
======== ========== ===================================================================================================