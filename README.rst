==============================================================
Clide (Command Line Interface Development Environment) Library
==============================================================

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/03/19
- Last Modified: 2013/07/04
- Version: v1.4.0.0
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

Two functionally identical parts to Clide exist, one written in C++ for an embedded system,
and the other part written in C# for running on a PC.

Uses a both human readable and computer readable format (UNIX command-line style)
for easy implementation and debugging. Automatically generates UNIX-style help text
which is useful if system is being controlled by a human (see below).

Useful for working with and controlling embedded systems.

An example message takes the format of

::

	set-speed -rpm 2000\n

where set-speed is the command name, "-rpm" is an optional argument that specifies
that the value is in rpm, "2000" is a non-optional parameter which specifies the
speed, and "\n" is the new-line character which signifies the end of a message
(which is normally inserted automatically by command-lines when enter is pressed).

Uses dynamic memory allocation for creating commands/options/parameters e.t.c
Command data is stored in a contiguous block

All text is case-sensitive. It is recommended to use lower-case only to
follow the UNIX command-line style.

Special support for the "help" command, and `-h`, `--help` flags for every registered
command. No special support other UNIX commands such as `man`, `whatis` or `info`
'help' is a special command which can be implemented by calling
RegisterHelpCmd()

Internal Dependencies
=====================

These are all included in the repository.

- Clide-Config.h						-> Configuration file.
- Clide-Rx.c, .h						-> Receieve object.
- Clide-Tx.c, .h						-> Transmit object.
- Clide-Cmd.c, .h						-> Command object.
- Clide-Param.c, .h						-> Parameter object.
- Clide-Option.c, .h					-> Option object.
- Clide-Port.c, .h 						-> Contains port-specfic code. Change this to fit application.
- MemMang.c, .h 						-> Higher-level memory management functions
- PowerString-Split.h					-> Higher-level string manipulation routines.

External Dependencies
=====================
- <stdio.h> 	-> snprintf()
- <stdlib.h> 	-> realloc(), malloc(), calloc(), free()
- <cctype>		-> isalnum()
- <getopt.h>	-> getopt()

PACKET DECODING PROCESS (RX)
=============================

- Remove all non-alphanumeric characters from the start of the packet
- Split packet into separate arguments
- Make sure received command is registered
- Extract options and values (if present), execute option callback functions
- Check all parameters are present
- Execute parameter callback functions
- Execute command callback function

ISSUES
====

- See GitHub Issues

LIMITATIONS
===========

- Maximum number of commands: 256
- Maximum number of parameters or options per command: 256
- Maximum string length of a command name, option name/value, parameter value: clideMAX_STRING_LENGTH

Usage
=====


**Includes**

::

	using namespace Clide;

**Clide Objects**

::
	
	// Create RX Clide object
	Clide::Rx rxController;
	
**Callback Functions**

::
	
	// Create call-back function that is automatically called when
	// registered command is recieved
	bool SetSpeedCmd(Clide::Cmd* cmd)
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
	
**Main Loop**

::
	
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