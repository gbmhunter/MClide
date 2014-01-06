==============================================================
Clide (Command Line Interface Development Environment) Library
==============================================================

.. image:: https://api.travis-ci.org/gbmhunter/clide-cpp.png?branch=master   
	:target: https://travis-ci.org/gbmhunter/clide-cpp

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.cladlab.com)
- Created: 2012/03/19
- Last Modified: 2014/01/07
- Version: v6.0.0.0
- Company: CladLabs
- Project: Free Code Libraries
- Language: C++
- Compiler: GCC	
- uC Model: n/a
- Computer Architecture: n/a
- Operating System: n/a
- Documentation Format: Doxygen
- License: GPLv3

.. role:: bash(code)
	:language: bash

Description
===========

A command-line style communication interface designed to make it easy to send messages and
data between two micro-controllers, a microcontroller and computer, or two computers, via
a serial interface that supports ASCII characters (e.g. UART, I2C, SPI).

Two functionally identical Clide projects exist, this one written in C++ for an embedded system,
and the other one (Cs-Clide) written in C# for running on a PC.

Uses a both human readable and computer readable format (POSIX.2 command-line style, with
GNU extensions) for easy implementation and debugging. 


Useful for working with and controlling embedded systems.

Standard UNIX Style Commands (and long options)
-----------------------------------------------

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
	
All text is case-sensitive. It is recommended to use lower-case only to follow the POSIX command-line style.

Supports long options (GNU extension to the POSIX.2 standard).

Powerful
--------

Uses dynamic memory allocation for creating commands/options/parameters e.t.c. Command data is stored in a contiguous block

Negative Number And Spaces-In-Parameter Support
-----------------------------------------------

There will be a time when you need to be able to use negative numbers. Unfortunately, it just happens that the negative sign is usually used to signify an option (e.g. -r). Clide supports negative numbers, along with spaces-within-parameters, by adding the ability to enclose a parameter/option in quotes. Inside the quotes, and special characters are just treated as normal characters, allowing you to do things like:

:code:`set "-123"`

which will treat -123 as a single parameter, not the options 1, 2, 3. 

Portable
--------

Clide can be used with ease on both Linux and embedded systems.

Clide does not use RTTI (e.g. :code:`dynamic_cast()`), allowing it to be used on a larger range of embedded systems.

Clide is not dependant on the :code:`getopt_long()` function from the standard C-library, it has it's own version.

Easy Including
--------------

Before writing code using Clide as a library, you only need to include the single header file called :code:`Clide-IncludeJustMe.hpp` which is found in :code:`./src/include/`.

Easy To Experiment With
-----------------------

Clide comes with a Makefle with automatic dependcy tracking and example code which is automatically built on running the command :code:`make` from the root directory of the repo.

Once compiled, this example code can be run by typing :code:`example/example.elf`.

Automatic Help Generation
-------------------------

Automatic support for the "help" command, and :bash:`-h`, :bash:`--help` flags for every other registered command. Help descriptions are saved as member variables of the respective command/option/parameter objects. No special support other UNIX commands such as :bash:`man`, :bash:`whatis` or :bash:`info`. 

To enable automatic help generation, just set the macro :code:`clide_ENABLE_AUTO_HELP` to 1 in :code:`Clide-Config.hpp`.

Advanced Terminal Text Formatting
---------------------------------

clide-cpp supports advanced terminal text formatting (e.g. coloured, bold, underlined or italized text) by way of the `ASCII escape codes <http://en.wikipedia.org/wiki/ANSI_escape_code>`_. These codes are supported by many popular shells. They have been tested and confirmed to work with the bash shell.

To enable advanced text formatting, set the :code:`clide_ENABLE_ADV_TEXT_FORMATTING` macro in Clide-Config.hpp to 1. There are other macros in this file to control the colours.

Included Unit Tests
-------------------

Clide used the UnitTest++ library to perform unit testing. They are located under :code:`test/`. The UnitTest++ library is included with this repo.

The unit tests check for:
- Empty commands are handled safely
- Short and long options work correctly
- Parameters work correclty
- Multiple spaces between arguments are o.k.
- Spastic input is handled safely
- Negative numbers are supported wth quotes

Installation
============

1. Clone the git repo onto your local storage.

2. Run `make all` to compile and run unit tests. Do not worry about Clide error messages being printed when unit tests are run, the unit tests are designed to specifically cause errors to test the response.

3. To include clide-cpp into your embedded (or otherwise) firmware/software project, copy the repo into your project folder (or other suitable place) and include the file "Clide-IncludeJustMe.hpp" from your C++ code.


External Dependencies
=====================

The following table lists all of clide-cpp's external dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<stdio.h>              Standard C library   snprintf()
<stdlib.h> 	           Standard C library   realloc(), malloc(), calloc(), free()
<cctype>               Standard C library   isalnum()
====================== ==================== ======================================================================

Packet Decoding Process (RX)
============================

When :code:`Rx.Run()` is called...

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
- Maximum string length of a command name, option name/value, parameter value: :code:`clideMAX_STRING_LENGTH`

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
	
FAQ
===

1. I keep getting weird characters appear in the terminal from text sent from Clide.

   Your terminal probably doesn't support special formatting characters. Set :code:`clide_ENABLE_ADV_TEXT_FORMATTING` to 0 in :code:`Clide.Config.hpp`.


Changelog
=========

======== ========== ===================================================================================================
Version  Date       Comment
======== ========== ===================================================================================================
v6.0.0.0 2013/01/07 Added the idea of 'command groups'. Commands can be assigned groups that they belong to, which will then enable you to print specialised help for particular groups (e.g. 'help -g user' only prints help for user commands). New 'CmdGroup' object in 'Clide-CmdGroups.hpp/.cpp'. Basic help group functionality added, although needs tidying up and added support for a default group if none provided.
v5.4.7.0 2014/01/06 Removed calls to 'getenv()' from 'Clide-GetOpt.cpp', as this does not make sense in an embedded environment. Change 'UartDebug()' call to 'UartComms()' in PSoC port functions in 'Clide-Port.cpp'.
v5.4.6.0 2013/12/20 Added FAQ section to README. Fixed issue with 'parentComm' variable in Cmd constructor. Got rid of memory allocation for string literals (in cmd, param and option classes), as we can just take a pointer to the string literal which will remain in memory for the duration of the program anyway. /test/ directory now visible in eclipse project.
v5.4.5.0 2013/12/19 Made Clide::Tx inherit from Clide::Comm (as Clide::Rx does), and removed unecessary functions from Clide::Tx. Moved many duplicate Tx/Rx functions/variables into the Clide::Comm class. Added info about negative number, spaces support and easy experimenting in the README.
v5.4.4.0 2013/12/19 Made commands printed in help text bold if advanced formatting is enabled.
v5.4.3.0 2013/12/19 Added prompt to user about tryping 'help' if they enter an invalid command, if automatic help is enabled. Modified formatting of help text.
v5.4.2.0 2013/12/19 Fixed issue with example code not being able to loop indefinetly by adding 'cin.ignore()' after 'cin.get()'. Now use Ctrl-C to exit.
v5.4.1.0 2013/12/19 Replaced all references to 'test' in the /example/ folder code to 'example'. Added second example command. Split description section of README into smaller sub-sections. Removed the helpEnabled variable, as this was not being used (help is enabled with the macro '#clide_ENABLE_AUTO_HELP' instead).
v5.4.0.0 2013/12/19 Added automatic dependency generation for clideLib in Makefile. Fixed incorrect comment text in Makefile. Removed unused function 'Rx::RegisterHelpCommand()'. Fixed issue with example code not being recompiled with Clide library changes by removing pipe in Makefile recipe.
v5.3.0.0 2013/12/18 Removed unused 'Rx::Init()' function. Added '\n's onto the end of '\r's that were by themselves. Initialised Rx::helpEnabled to true in constructor. Added 'Clide::Comm' class which will serve as a base class for both 'Clide::Tx' and 'Clide::Rx'. Added 'help' command functionality, which is automatically added to Clide::Rx if the macro '#clide_ENABLE_AUTO_HELP' is set to 1.
v5.2.2.0 2013/12/18 Changed advanced text formatting macro name. Added info about advanced text formatting to README.
v5.2.1.0 2013/12/18 Defined text colours as macros in 'Clide-Config.hpp'. Changed header row colour from gold to yellow.
v5.2.0.0 2013/12/16 Added support for coloured text output if the terminal allows it. Set clide_ENABLE_TEXT_FORMATTING to 1 in Clide-Config.hpp to enable this feature.
v5.1.0.0 2013/12/16 Tidyed up the help command text that is printed when the '-h' or '--help' options are used, especially so it looks nice in a Linux terminal.
v5.0.0.0 2013/12/16 Added example folder to repo, with example Clide program designed to be run from Linux terminal. Added example build commands to Makefile. Tidyed 'make clean' code by adding dependencies.
v4.0.3.0 2013/12/16 Removed all remaining references to '#include <getopt.h>', as clide-cpp now has built-in `getopt()` function. Closes #78, closes #73.
v4.0.2.0 2013/12/10 Fixed TravisCI 'build passing/failing' image link in README.
v4.0.1.0 2013/12/10 Added fall-back printf options to Clide-Port.hpp. Added '@created' and '@last-modified' tags to code file title blocks, removed ambiguos '@date' tag. Improved '@brief' tag descriptions.
v4.0.0.8 2013/12/10 Added more installation information to the README.
v4.0.0.7 2013/12/10 4th attempt at fixing 'External Dependencies' section in README.
v4.0.0.6 2013/12/10 3rd attempt at fixing 'External Dependencies' section in README.
v4.0.0.5 2013/12/10 2nd attempt at fixing 'External Dependencies' section in README.
v4.0.0.4 2013/12/10 Attempt at fixing External Dependencies section in README.
v4.0.0.3 2013/12/10 Improving inline code and external dependency section in README.
v4.0.0.2 2013/12/10 Attempt at inline code in the README.
v4.0.0.1 2013/12/10 Updated various parts of README, and improved formatting.
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