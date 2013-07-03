
#include "../src/include/Clide-Cmd.h"
#include "../src/include/Clide-Param.h"
#include "../src/include/Clide-Option.h"
#include "../src/include/Clide-Port.h"
#include "../src/include/Clide-Tx.h"
#include "../src/include/Clide-Rx.h"

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