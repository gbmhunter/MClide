//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2013-07-04
//! @last-modified 	2014-09-14
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.


//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//====== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//===== USER SOURCE =====//
#include "../api/MClideApi.hpp"

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

		void PrintError(const char* msg)
		{
			std::cout << msg;
		}
};

int main()
{

	Printer printer;

	// Set up printing
	Clide::Print::AssignCallbacks(
			MCallbacks::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintDebug),
			MCallbacks::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintCmdLine),
			MCallbacks::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintError));

	Clide::Print::enableCmdLinePrinting = false;
	Clide::Print::enableErrorPrinting = false;
	Clide::Print::enableDebugInfoPrinting = false;

	return MbeddedNinja::TestRegister::RunAllTests();
	/*
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
    }*/
	
}
