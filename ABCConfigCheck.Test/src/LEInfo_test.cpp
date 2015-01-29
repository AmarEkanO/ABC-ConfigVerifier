/*
** Contains tests for LEInfo
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "LEInfo.h"

TEST(When_an_instance_is_created, get_le_and_get_line_number_should_return_correct_values)
{
	LE le;
	int line = 10;

	LEInfo info(line, le);

	EXPECT_EQ(le, info.getLE());

	EXPECT_EQ(line, info.getLineNumber());
}

TEST(When_an_instance_is_created, le_retrived_should_have_the_right_properties)
{
	LE le;
	
	Property prop("Port", "4");

	le.addProperty(prop);

	LEInfo info(10, le);

	LE& ref = info.getLE();

	EXPECT_EQ(ref, le);

	EXPECT_EQ(ref.getProperty("Port"),prop);
}