//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @created		2013/07/04
//! @last-modified 	2014/01/21
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.

#include <stdio.h>

#include "../api/Clide.hpp"

#include "./UnitTest++/src/UnitTest++.h"
#include "./UnitTest++/src/TestReporterStdout.h"

class Printer
{
public:
	void PrintDebug(const char* msg)
	{
		std::cout << msg;
	}

	void PrintCmdLine(const char* msg)
	{
		std::cout << msg;
	}
};

int main()
{
	Printer printer;

	Clide::Print::debugPrintCallback = SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintDebug);
	Clide::Print::cmdLinePrintCallback = SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintCmdLine);

	return UnitTest::RunAllTests();
	
	try
    {
        UnitTest::TestReporterStdout reporter;
		UnitTest::TestRunner runner(reporter);
	
	
		return runner.RunTestsIf(
			UnitTest::Test::GetTestList(),
			"ParamTests",
			UnitTest::True(),
			0);
    }
    catch(std::exception const& e)
    {
         printf("%s", e.what());
         // If you are feeling mad (not in main) you could rethrow! 
    }
	
}
