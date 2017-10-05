#include <gtest/gtest.h>
#include "utTerm.h"


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("Pause");
	return 0;
}