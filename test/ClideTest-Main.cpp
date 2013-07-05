//!
//! @file 		ClideTest-Main.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @date 		2013/07/04
//! @brief 		Contains main entry point for unit tests.
//! @details
//!				See README.rst in root dir for more info.

#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"
#include "./UnitTest++/src/TestReporterStdout.h"

int main()
{
	return UnitTest::RunAllTests();
	
	/*
	//return UnitTest::RunAllTests(UnitTest::Test::GetTestList(), NULL, "OptionsWithValuesTests", 0);
	
	UnitTest::TestReporterStdout reporter;
	UnitTest::TestRunner runner(reporter);
	
	
	
    return runner.RunTestsIf(
		UnitTest::Test::GetTestList(),
        "OptionsWithValuesTests",
		UnitTest::True(),
        0);
	*/
}