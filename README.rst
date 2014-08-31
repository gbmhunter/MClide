==============================================================
ClideCpp
==============================================================

--------------------------------------------------------------
Clide (CommandLineInterfaceDE) Library
--------------------------------------------------------------

.. image:: https://api.travis-ci.org/mbedded-ninja/ClideCpp.png?branch=master   
	:target: https://travis-ci.org/mbedded-ninja/ClideCpp

- Author: gbmhunter <gbmhunter@gmail.com> (http://www.mbedded.ninja)
- Created: 2012-03-19
- Last Modified: 2014-08-31
- Version: v9.1.3.0
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

Two functionally identical Clide projects exist, this one written in C++ for an embedded system (clide-cpp),
and the other one (Cs-Clide) written in C# for running on a PC (clide-cs).

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

There will be a time when you need to be able to use negative numbers. Unfortunately, it just happens that the negative sign is usually used to signify an option (e.g. :code:`-r`). Clide supports negative numbers, along with spaces-within-parameters, by adding the ability to enclose a parameter/option in quotes. Inside the quotes, and special characters are just treated as normal characters, allowing you to do things like:

:code:`set "-123"`

which will treat -123 as a single parameter, not the options 1, 2, 3. 

Portable (Platform Agnostic)
----------------------------

Clide can be used with ease on both Linux and embedded systems. All platform-specific operations are handled via callbacks that you provide the functionality for (e.g. printing to the command line and printing debug information). These callbacks exist in Print.hpp/.cpp.

Clide does not use RTTI (e.g. :code:`dynamic_cast()`), allowing it to be used on a larger range of embedded systems.

Clide is not dependant on the :code:`getopt_long()` function from the standard C-library, it has it's own version.

Easy Including
--------------

Before writing code using Clide as a library, you only need to include the single header file called :code:`Clide.hpp` which is found in :code:`api/`.

Easy To Experiment With
-----------------------

Clide comes with a Makefle with automatic dependcy tracking and example code which is automatically built on running the command :code:`make` from the root directory of the repo.

Once compiled, this example code can be run by typing :code:`example/example.elf`. A few example commands with associated parameter and options have been registered for you to experiment with.

Automatic Help Generation With Command Grouping
-----------------------------------------------

Automatic support for the "help" command, and :bash:`-h`, :bash:`--help` flags for every other registered command. Help descriptions are saved as member variables of the respective command/option/parameter objects. No special support other UNIX commands such as :bash:`man`, :bash:`whatis` or :bash:`info`. 

To enable automatic help generation, just set the macro :code:`clide_ENABLE_AUTO_HELP` to 1 in :code:`Clide-Config.hpp`.

Sometimes, you do not wish to display all available commands to the user. clide-cpp supports command group, in where you can assign each command to specific groups. The help command supports a "-g groupName" option, which will only print help for commands registered in that group.

E.g.

:bash:`help -g user` will print all user commands
:bash:`help -g dev` will print all developer commands

and

:bash:`help` (with no group option) will print all the commands in the default group (which is assignable through :bash:`Rx.defaultCmdGroup`). 

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
- Callback functions are called at the correct time

Event-driven Callback Support
-----------------------------

Clide leverages the :code:`slotmachine-cpp` library to provide event-driven callbacks. :code:`slotmachine-cpp` supports callbacks to methods (instance functions), without Clide having any previous knowledge about the class (type agnostic).

List of events supported by callbacks:

- Command recognised
- Command not recognised
- Help command requested
- Command-line printing
- Debug printing
- Error printing

Callbacks are generated in the following manner:

::

	#include "../api/Clide.hpp"

	// Class with a method to use as callback
	class CallbackClass
	{
	public:
		void Callback(Cmd *cmd)
		{
			this->_methodCallbackCalled = true;
	
		}
	
		bool _methodCallbackCalled;
	
	};

	CallbackClass myCallbackClass;

	// Create command, creating a callback to the method in the class above
	Cmd cmdTest(
		"test",
		SlotMachine::CallbackGen<CallbackClass, void, Cmd*>(&myCallbackClass, &CallbackClass::Callback),
		"A test command.");
		
	// Now the method myCallbackCallback.Callback() will be called when the command "test" is received!

Exceptions
----------

O.K., so clide-cpp uses exceptions, but you say it's meant for embedded systems? I choose to use exceptions after I ran into the problem with the fact a object constructor could fail, and you can't return an error code. It was either implement exceptions or use the 'zombie object' approach. I choose exceptions because they a better suited to solve the problem. If you have an issue with this, please let me know (create a GitHub issue).

Installation
============

1. Clone the git repo onto your local storage.

2. Run :code:`make all` to compile and run unit tests. Do not worry about Clide error messages being printed when unit tests are run, the unit tests are designed to specifically cause errors to test the response.

3. To include clide-cpp into your embedded (or otherwise) firmware/software project, copy the repo into your project folder (or other suitable place), include the file :code:`api/Clide.hpp` from your C++ code, and make sure all the .cpp files in :code:`src/` are built and linked as part of the project.


Dependencies
============

The following table lists all of clide-cpp's dependencies.

====================== ==================== ======================================================================
Dependency             Delivery             Usage
====================== ==================== ======================================================================
<stdio.h>              Standard C library   snprintf()
<stdlib.h> 	           Standard C library   realloc(), malloc(), calloc(), free()
<cctype>               Standard C++ library isalnum()
<vector>               Standard C++ library std::vector, for holding vectors of commands, parameters and options.
<string>               Standard C++ library std::string for command, parameter and option names/descriptions.
"SlotMachine.hpp"      /lib/slotmachine-cpp Method callback functionality
"UnitTest++"           /test/UnitTest++     Unit test framework for Clide.
====================== ==================== ======================================================================

Packet Decoding Process (RX)
============================

When :code:`Rx.Run()` is called...

- Remove all non-alphanumeric characters from the start of the packet
- Split packet into separate arguments
- Make sure received command is registered. If so, set :code:`cmdReceived = TRUE`. It not, return :code:`FALSE`.
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
- Maximum string length of a command name, option name/value, parameter value: :code:`clide_MAX_STRING_LENGTH`

Usage
=====

This is a basic example. See :code:`example/` or :code:`test/` for more examples. In :code:`main.c` add...

::

	#include "api/Clide.hpp"

	using namespace Clide;

	// Create RX Clide object
	Rx rxController;
	
	// Create call-back function that is automatically called when
	// registered command is recieved
	bool SetSpeedCallback(Cmd* cmd)
	{
		// Extract parameter from received command (this will be 100 if following code below)
		float speed = atof(cmd->paramA[0]->value);
		
		// Call some function to do stuff with parameter
		Motor.SetSpeed(speed);
	}
	
	int main()
	{
		// Create command
		Cmd setSpeedCmd("set-speed", &SetSpeedCallback, "Sets the speed.");
		
		// Create Parameter
		Param speed("The desired speed.");
		
		// Register parameter with command
		setSpeedCmd.RegisterParam(&speed);
		
		// Register command with RX controller
		rxController.RegisterCmd(&setSpeedCmd);	
		
		// Run rx controller. This will call the callback SetSpeedCallback above.
		rxController.Run("set-speed 100");	
	}
	
	
FAQ
===

1. 	I call :code:`Clide::Rx::Run()`, and no errors occur, but nothing happens. 

	You probably have not set-up the callbacks. The crucial one to set-up is :code:`Clide::Print::AssignCallbacks(...)`, which is called every time a message needs to be printed back to the command-line.
	
	Here is an example::
	
		Clide::Print::AssignCallbacks(
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintDebug),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintCmdLine),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintError));

2. 	I keep getting weird characters appear in the terminal from text sent from Clide.

	Your terminal probably doesn't support special formatting characters. Set :code:`clide_ENABLE_ADV_TEXT_FORMATTING` to 0 in :code:`Clide.Config.hpp` to disable the special formatting characters.
	
3.	I get the error :code:'Clide::Print::DebugPrintingLevel' is not a class or namespace. 

	You are not compiling C++11, which you need to do, in order to support enum classes. Add the compiler flag :code`-std=c++11` or :code:`-std=c++0x` to your build process.
	
4.	The first element of the :code:`argv` is not working correctly.

	Make sure you have set :code:`Rx::ignoreFirstArgvElement` to :code:`true` or :code:`false` depending on your application. This variable defaults to :code:`true` which is suitable for most standard operation systems (including Windows and Linux) which pass in the called program name and path as the first :code:`argv` element. 


Changelog
=========

========= ========== ===================================================================================================
Version    Date       Comment
========= ========== ===================================================================================================
v9.1.3.0  2014/08/31 Attempt three at calling './build.sh' from TravisCI config file.
v9.1.2.0  2014/08/31 Attempt two at calling './build.sh' from TravisCI config file.
v9.1.1.0  2014/08/31 Changed TravisCI script variable to call './build.sh' instead of make, closes #162.
v9.1.0.0  2014/08/31 Added 'build.sh' to handle the downloading of dependencies. Currently downloads UnitTest++ and slotmachine-cpp and correctly adds compiler flags for the build to work correctly. Some values still hardcoded into build.sh, this is only a first draft. Removed dependencies from 'test/' and 'lib/' as these are now downloaded automatically by this script.
v9.0.0.0  2014/08/30 First commit in work to update Makefile so it automatically downloads/builds dependencies.
v8.10.2.0 2014/08/30 Renamed 'Clide-Cpp' to 'ClideCpp', closes #159. Changed all references of 'www.cladlab.com' to 'www.mbedded.ninja', closes #160.
v8.10.1.0 2014/05/16 Added comments to 'FindOptionBy..()' functions, closes #156. Removed unused and undefined function declarations. Updated FAQ 1 in README to reflect the new way of assigning callbacks, closes #118.
v8.10.0.0 2014/05/16 Added ability to supress the printing of the help header, with the long option '--no-header' to the 'help' command, closes #155. Made internal commands use functions that find options by name rather than numeral indexing, closes #154.
v8.9.0.0  2014/05/16 You can now find options by short or long name using the functions 'Cmd::GetOptionByShortName()' and 'Cmd::GetOptionByLongName' respectively, closes #153. Added '/test/OptionSearchByShortNameTests.cpp' and '/test/OptionSearchByLongNameTests.cpp'.
v8.8.15.0 2014/04/07 Rx::Run2() now prints message to command line if argc/argv are 0/empty, closes #146.
v8.8.14.0 2014/04/07 Example code now does not print debug info. Added 'Type help to see a list...' info to the 'Received command contained no alpha-numeric...' error message, closes #145. Fixed code getting trapped in loop with blank message when running example code, closes #144.
v8.8.13.0 2014/04/07 'Num. of received parameters does not match...' error now prints values, closes #140. Stopped example code from printing debug info, closes #141. Set clide_ENABLE_AUTO_HELP to 1, closes #142. Fixed segmentation fault when running help from example code program, closes #143.
v8.8.12.0 2014/04/03 Clide::Param::value is now a std::string, closes #138. Removed command/option/parameter name/description length restrictions, closes #139. Adjusted unit tests accordingly.
v8.8.11.0 2014/04/03 Clide::Option::value is now a std::string, closes #137.
v8.8.10.0 2014/04/03 Clide::Option's long name is now a std::string, closes #136. Fixed relevant unit tests and code in core files.
v8.8.9.1  2014/04/02 Added code formatting to more text in the README. Fixed bullet points under the section Event-Driven Callback Support in README, closes #128.
v8.8.9.0  2014/04/02 Converted more of the const char* variables in Clide to std::string's, closes #135. Removed some more count variables that can be replaced with std::vector.size().
v8.8.8.0  2014/04/02 Converted some of the const char* variables in Clide::Cmd and Clide::Option to std::string's.
v8.8.7.0  2014/04/02 Removed all count variables that could be replaced with vector.size() instead, closes #134.
v8.8.6.0  2014/04/02 Removed all refereneces to Clide::MemMang, now uses std::vector and new operator, closes #133. Added <vector> as a dependency in README.
v8.8.5.0  2014/04/02 paramA, optionA, and cmdGroupA variables in Clide::Rx are now of type std::vector, closes #132.
v8.8.4.0  2014/04/02 Added unit tests for making sure Clide will work as part of a class, closes #131.
v8.8.3.0  2014/04/02 Added ignoreFirstArgvElement variable to Rx class, closes #129. Edited unit tests accordingly. Added info about this to README.
v8.8.2.0  2014/04/01 Got rid of access to _argPtr[0] thru [4] in Clide::Rx which could access invalid memory, closes #126. Stopped empty argc/argv from crashing Clide, closes #127. Added unit test for empty argc/argv, closes #125.
v8.8.1.0  2014/03/26 Replaced all config_DEBUG... macros with clide_ENABLE_DEBUG_CODE, closes #120. Rx::Run(int argc, char* argv[]) now returns a boolean, closes #122. Got rid of tempBuff variable in Rx::Run(), closes #123.
v8.8.0.0  2014/03/26 Added Clide::Rx::Run(int argc, char* argv[]) function which supports standard main variables as the input, closes #119. Added appropriate unit tests. Clide::Rx::Run() underwent serious modifications to allow for this. Added ability to turn on and off debug printing while running unit tests from test/main.cpp.
v8.7.5.0  2014/03/26 Fixed example code so that it didn't use private Clide::Print variables and cause compiler errors, closes #117. Added -std=c++0x compiler flag to example code build in the Makefile.
v8.7.4.1  2014/03/26 Added info to README about enum class errors.
v8.7.4.0  2014/03/21 Improved Print class by encapsulating all printing calls into functions, and providing a dynamic way of enabling/disabling them, rather than using macros in Config.hpp.
v8.7.3.0  2014/03/21 Fixed bug which caused a segmentation fault by setting functionCallback to NULL if not provided to Cmd constructor. Converted the end-of-command character from a macro in Config.hpp to a variable in RxBuff, which is provided in the constructor. Modified existing unit tests accordingly and added new unit tests for specifically testing that the end-of-command char works.
v8.7.2.0  2014/03/21 Added Cmd constructor that accepts a method callback (used to only accept function callbacks). Updated FunctionAndMethodCallbackTests.cpp to reflect this. Added an example in README showing how to use these.
v8.7.1.0  2014/03/21 Added unit tests for function and method callbacks in test/FunctionAndMethodCallbackTests.cpp.
v8.7.0.0  2014/03/20 Added support for callbacks to methods (member functions) when a command is recognised, using the Cmd::methodCallback variable. Haven't tested it or added unit tests yet.
v8.6.3.0  2014/03/20 Renamed RxBuff::Write() to RxBuff::WriteString() and added RxBuff::WriteChar() for writing single characters to the buffer. Simarly renamed test/RxBuff.cpp to RxBuffStringTests.cpp and created RxBuffCharTests.cpp. Small update to README.
v8.6.2.2  2014/01/24 Fixed up the example in the README, removed help command, closes #116.
v8.6.2.1  2014/01/24 Added new info to FAQ in README. 
v8.6.2.0  2014/01/24 'Command not recognised' error now prints the unrecognised message, closes #20.
v8.6.1.0  2014/01/24 Added ability to silence the 'Command not recognised' error, closes #115. Fixed failing 'Long description' unit test by adding try/catch block.
v8.6.0.0  2014/01/24 Added exception throwing to Clide::Cmd()'s constructor. Fixes error with too-long command descriptions, closes #105. Added check for malloc() NULL when help option is created in 'Clide::Cmd' constructor, closes #114. Added info about exceptions to README.
v8.5.4.0  2014/01/24 Removed multiple definition of STR() macro, by putting it in a new file, 'Preprocessor.hpp', closes #112. Removed namespaces from preprocessor macros, closes #113. Makefile now prints less useless messages. Removed verbose_flag variable in Rx::Run(), closes #60. Added data type postfixed to relevanant macros in 'Config.hpp', closes #26. Made all 'Config.hpp' macros have the same name format, closes #75.
v8.5.3.0  2014/01/24 Tidyed up help printing code. Added unit tests for wacky (empty and large strings) command, parameter and option descriptions, closes #106. Corrected header guard in Print.hpp, closes #108. Separated debug and error messages (created separate callback for error messages), closes #107. Added malloc() NULL detection when registering option with command, closes #109. Removed text 'Debug' when running the unit tests as part of 'make', closes #110. Stopped Clide from printing tons of info to stdout when running unit tests, closes #111.
v8.5.2.0  2014/01/22 Fixed example code so that Clide now prints to stdout, stopped working after Clide was switched to callbacks, closes #104. Fixed padding when help is printed (now uses padding and truncation if required, columns align correctly), closes #103.
v8.5.1.0  2014/01/22 Changed 'filter: in group ...' to 'Showing commands for user group: ...' which is more explanatory, closes #101.
v8.5.0.0  2014/01/22 Added callback (generalHelpRequestedCallback) for when the 'help' command is called, to the Comm class, closes #98. Updated git submodule 'slotmachine-cpp'. Renamed Port.hpp/.cpp to Print.hpp/.cpp, and changed port-specific print functions into callbacks, to make code more platform-agnostic, closes #99. Updated title in README and added sub-title, closes #100.
v8.4.0.0  2014/01/21 Moved all files from 'src/include/' to 'include/', and created 'api/Clide.hpp' (old 'IncludeJustMe.hpp' file) to conform to new file structure standard, closes #97.
v8.3.1.0  2014/01/16 Updated the slotmachine-cpp sub-repo URL in .gitmodules from SSH to HTTPS, in an attempt to fix the error TravisCI had while trying to download it.
v8.3.0.0  2014/01/16 Added git submodule slotmachine-cpp to 'lib/slotmachine-cpp'. This library adds method-capable callback functionality to C++, closes #95. Repalced C-style unrecognised command callback with Slotmachine callback. Added info about callbacks to the README.
v8.2.4.0  2014/01/14 Renamed code files to follow new convention (i.e. got rid of the 'Clide' prefix), closes #94.
v8.2.3.0  2014/01/14 Changed 'Error' to 'ERROR' in 'Clide: Error: Num. of received param...' in 'src/Clide-Rx.cpp', closes #64.
v8.2.2.0  2014/01/14 'Rx::Run()' now does not modify the input command message, which is safer and less bug-prone, closes #91. This also allows string literals to be passed to 'Rx::Run()'. Added unit test to test string literal input feature ('test/StringLiteralAsInputToRxRun.cpp'), closes #93.
v8.2.1.0  2014/01/14 Stopped clide-cpp calling command callback function if callback was NULL (prevents crashing), closes #90. Added unit test(s) for this feature ('test/NullCallbackTests'), closes #92.
v8.2.0.0  2014/01/13 Added unit test that makes sure the unrecognised command callback function is not called if the command is recognised.
v8.1.0.0  2014/01/13 Added assignable call-back function variable to the Rx class for when there is an unrecognised command. You can use this to do your own event handling. It also passes a 'char*' to the unrecognised command. Added unit test file 'NotRecognisedCmdCallbackTests.cpp' for making sure the callback works as expected.
v8.0.0.0  2014/01/13 Added logging funnctionality to clide-cpp. Currently added to only the 'Clide::Rx' class. Added unit tests for logging functionality ('LoggingTests.cpp'). Added the '-std=c++0x' compiler flag to the Makefile so that I can use 'enum class xxx' (strongly-typed enumerations).
v7.0.1.0  2014/01/10 Added 'const' qualifier to input variable to 'RxBuff::Write()'. Improved comments to 'Rx::Run()' in 'Clide-Rx.hpp'.
v7.0.0.0  2014/01/09 Added new 'RxBuff' class as a front-end input buffer for the 'Rx' engine. Characters can be written to the RxBuff, and RxBuff will call Rx::Go() automatically when it detects the end-of-command character, and clear the buffer, ready for more input. Added unit test file for this feature (test/RxBuff.cpp). Also fixed recent dates in the README changelog. Started using new naming scheme (dropping the Clide from the start of the filename). Modified Makefile for automatic dependency generation for 'test/' folder.
v6.0.2.0  2014/01/07 Deleted unneeded, commented-out code. Fixed bug 'Command groups it belongs to' bug by replacing fixed 0 index with x variable, closes #89.
v6.0.1.0  2014/01/07 Added support for a default command group, closes #84. Added command group info to the README, closes #85. Added filter info to help text (e.g. which group is being displayed). Added units tests for help commands in new 'ClideTest-Help.cpp', closes #86.
v6.0.0.0  2014/01/07 Added the idea of 'command groups'. Commands can be assigned groups that they belong to, which will then enable you to print specialised help for particular groups (e.g. 'help -g user' only prints help for user commands). New 'CmdGroup' object in 'Clide-CmdGroups.hpp/.cpp'. Basic help group functionality added, although needs tidying up and added support for a default group if none provided.
v5.4.7.0  2014/01/06 Removed calls to 'getenv()' from 'Clide-GetOpt.cpp', as this does not make sense in an embedded environment. Change 'UartDebug()' call to 'UartComms()' in PSoC port functions in 'Clide-Port.cpp'.
v5.4.6.0  2013/12/20 Added FAQ section to README. Fixed issue with 'parentComm' variable in Cmd constructor. Got rid of memory allocation for string literals (in cmd, param and option classes), as we can just take a pointer to the string literal which will remain in memory for the duration of the program anyway. /test/ directory now visible in eclipse project.
v5.4.5.0  2013/12/19 Made Clide::Tx inherit from Clide::Comm (as Clide::Rx does), and removed unecessary functions from Clide::Tx. Moved many duplicate Tx/Rx functions/variables into the Clide::Comm class. Added info about negative number, spaces support and easy experimenting in the README.
v5.4.4.0  2013/12/19 Made commands printed in help text bold if advanced formatting is enabled.
v5.4.3.0  2013/12/19 Added prompt to user about tryping 'help' if they enter an invalid command, if automatic help is enabled. Modified formatting of help text.
v5.4.2.0  2013/12/19 Fixed issue with example code not being able to loop indefinetly by adding 'cin.ignore()' after 'cin.get()'. Now use Ctrl-C to exit.
v5.4.1.0  2013/12/19 Replaced all references to 'test' in the /example/ folder code to 'example'. Added second example command. Split description section of README into smaller sub-sections. Removed the helpEnabled variable, as this was not being used (help is enabled with the macro '#clide_ENABLE_AUTO_HELP' instead).
v5.4.0.0  2013/12/19 Added automatic dependency generation for clideLib in Makefile. Fixed incorrect comment text in Makefile. Removed unused function 'Rx::RegisterHelpCommand()'. Fixed issue with example code not being recompiled with Clide library changes by removing pipe in Makefile recipe.
v5.3.0.0  2013/12/18 Removed unused 'Rx::Init()' function. Added '\n's onto the end of '\r's that were by themselves. Initialised Rx::helpEnabled to true in constructor. Added 'Clide::Comm' class which will serve as a base class for both 'Clide::Tx' and 'Clide::Rx'. Added 'help' command functionality, which is automatically added to Clide::Rx if the macro '#clide_ENABLE_AUTO_HELP' is set to 1.
v5.2.2.0  2013/12/18 Changed advanced text formatting macro name. Added info about advanced text formatting to README.
v5.2.1.0  2013/12/18 Defined text colours as macros in 'Clide-Config.hpp'. Changed header row colour from gold to yellow.
v5.2.0.0  2013/12/16 Added support for coloured text output if the terminal allows it. Set clide_ENABLE_TEXT_FORMATTING to 1 in Clide-Config.hpp to enable this feature.
v5.1.0.0  2013/12/16 Tidyed up the help command text that is printed when the '-h' or '--help' options are used, especially so it looks nice in a Linux terminal.
v5.0.0.0  2013/12/16 Added example folder to repo, with example Clide program designed to be run from Linux terminal. Added example build commands to Makefile. Tidyed 'make clean' code by adding dependencies.
v4.0.3.0  2013/12/16 Removed all remaining references to '#include <getopt.h>', as clide-cpp now has built-in `getopt()` function. Closes #78, closes #73.
v4.0.2.0  2013/12/10 Fixed TravisCI 'build passing/failing' image link in README.
v4.0.1.0  2013/12/10 Added fall-back printf options to Clide-Port.hpp. Added '@created' and '@last-modified' tags to code file title blocks, removed ambiguos '@date' tag. Improved '@brief' tag descriptions.
v4.0.0.8  2013/12/10 Added more installation information to the README.
v4.0.0.7  2013/12/10 4th attempt at fixing 'External Dependencies' section in README.
v4.0.0.6  2013/12/10 3rd attempt at fixing 'External Dependencies' section in README.
v4.0.0.5  2013/12/10 2nd attempt at fixing 'External Dependencies' section in README.
v4.0.0.4  2013/12/10 Attempt at fixing External Dependencies section in README.
v4.0.0.3  2013/12/10 Improving inline code and external dependency section in README.
v4.0.0.2  2013/12/10 Attempt at inline code in the README.
v4.0.0.1  2013/12/10 Updated various parts of README, and improved formatting.
v4.0.0.0  2013/12/10 Added eclipse project files. Formatted Clide-Config.hpp. Disabled debug print macros except for errors.
v3.2.0.0  2013/08/25 Added .travis.yml file in root directory for Travis CI compatibility. Added Travis CI build status image to top of README.
v3.1.4.0  2013/07/12 Added unit test for an empty command.
v3.1.3.0  2013/07/12 Removed getopt() reference from Clide-MemMang.cpp.
v3.1.2.0  2013/07/12 Added unit tests for multiple spaces between arguments in a command (ClideTest-MultipleSpacesBetweenArguments.cpp).
v3.1.1.0  2013/07/11 Added compiler warning if no port-specific functions are defined in Clide-Port.cpp functions.
v3.1.0.0  2013/07/11 Added Clide-IncludeJustMe.hpp, which is a single header file the user can include to use the Clide library. Added note about it to README. Replaced all Clide includes in unit test files with the single include.
v3.0.1.0  2013/07/10 Removed reference to <getopt.h> in Clide-Rx.hpp.
v3.0.0.0  2013/07/10 Added own getopt() function (the Clide-GetOpt class), no longer dependant on C library for it.
v2.2.0.0  2013/07/09 Added continue if getopt_long() returned '?' character. Added Makefile command 'make clean-clide'.
v2.1.1.0  2013/07/09 Fixed non-portable use of '%u' in snprintf() in Rx::ValidateCmd(). Fixed other non-portable uses of snprint() and added more port-specific defines in Clide-Port.h. Removed RX code from Clide::Tx class. Added double braces around initialisers for two Rx::Run() variables. Changed optint to (optint - 1) when printing option which caused '?' to be returned from getopt_long(). Added unit tests for quotes and negative numbers.
v2.1.0.0  2013/07/09 Added unit tests for multiple Clide::Rx.Run() calls (ClideTest-MultipleRxRunCalls.cpp). Fixed long option index bug in Rx::BuildLongOptionStruct(). Fixed bug in getopt_long() reporting incorrect options by setting optint = 0 before run (explained in getopt.h). Fixed bug in Rx::ValidateOption() variable 'val' being initialised to 0, which was what was checked for after calling strcmp to see if there was a match.
v2.0.0.0  2013/07/08 Long options are now supported in the command-line interface (now used getopt_long). Various code to Option class and RX decoding has been added/changed to support this. Added Clide-Global.h. Deleted internal dependency section in README (not useful). Added mention of POSIX.2 standard in README. Fixed unit test that was failing (strcpy() was being passed a NULL). Added new Makefile option clean-ut, which just cleans the unit test code. Added unit tests for long options.
v1.6.4.0  2013/07/05 Added 'SpasticInput' unit tests. Added Doxygen '@brief' tags to documentation in `Clide-Cmd.h`. Added more documentation. Added C++ check to Clide-Port.cpp. Added port-specific code for PSoC5/5LP `printf()` functions in `Clide-Port.hpp`. Renamed namespace in Clide-MemMang from 'MemMang' to 'Clide'. Put MemMang functions inside a class. Added unit tests for commands with both parameters and options. 1 unit test currently failing.
v1.6.3.0  2013/07/05 Grouped all unit tests into test suites.
v1.6.2.0  2013/07/05 Re-added argsPtr assignment which was removed in last commit and caused Rx.Run() to crash on every call.
v1.6.1.0  2013/07/05 Added destructor debug messages. Add macro to enable/disable automatic help generation. Removed static global variables in Rx class and put them in Rx.Run() instead. This fixed the issues with some of the unit tests failing.
v1.6.0.0  2013/07/04 Deleted un-needed @public and @private comments. Put public objects first in classes. Added cmdDetected variable to Cmd object, and info about it to README. Formatted all-caps section titles in README correctly. Made Makefile file finding more automatic. Added more unit test files. Removed port-specific UartDebug function calls. Added destructor for Cmd object that frees up allocated memory. Renamed MemMang and PowerString-Split libraries to be part of Clide.
v1.5.0.0  2013/07/04 Added first unit tests (3 of them). They run automatically when 'make all' is called.
v1.4.1.0  2013/07/04 Fixed the '.h' includes to '.hpp'. Fixed 'make clean', it is now removing the correct files.
v1.4.0.0  2013/07/04 Renamed all .c files to .cpp and .h to .hpp. Automated some of the file finding processes in the Makefile.
v1.3.0.1  2013/07/03 Forgot to save README.rst.
v1.3.0.0  2013/07/03 Made Clide compilable on Linux. Added Makefile which compiles static Clide library, static UnitTest++ library, then runs unit test code. Added own getopt() file (doesn't work yet).
v1.2.2.0  2013/07/01 Deleted unnecessary header file includes from .c files.
v1.2.1.1  2013/06/29 Indented all namespace objects by one tab in all files.
v1.2.1.0  2013/06/25 Fixed lock-up on receiving empty message. Made tempBuff in Clide-Rx.c larger. Fixed a few spelling mistakes in README.
v1.2.0.2  2013/06/08 README is now in table format.
v1.2.0.1  2013/05/29 Removed C# notes in README (now in separate repo). Fixed README formatting issue. Fixed spelling mistakes.
v1.2.0.0  2013/05/29 Removed unneeded './cpp' root folder. Added unit test library UnitTest++ to './test/UnitTest++'"
v1.1.1.0  2013/05/15 Message "...not registered with command" in Clide-Rx.c was missing the last double quote, breaking the message format standard. Fixed.
v1.1.0.0  2013/05/14 Support for options with values in C++  library.
v1.0.0.0  2013/05/14 Initial version.
========= ========== ===================================================================================================