
#include "../src/include/Clide-Cmd.hpp"
#include "../src/include/Clide-Param.hpp"
#include "../src/include/Clide-Option.hpp"
#include "../src/include/Clide-Port.hpp"
#include "../src/include/Clide-Tx.hpp"
#include "../src/include/Clide-Rx.hpp"

#include "./UnitTest++/src/UnitTest++.h"

using namespace Clide;

bool Callback(Cmd *cmd)
{

}

TEST(BasicTest)
{
	Cmd cmd("test", &Callback, "A test command.");
}

int main()
{
	return UnitTest::RunAllTests();
}