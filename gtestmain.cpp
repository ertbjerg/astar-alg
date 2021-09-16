#include "gtest/gtest.h"

TEST (sample_test_case, sample_test)
{
	ASSERT_TRUE(true);
	ASSERT_FALSE(false);
	ASSERT_EQ(1,1);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}