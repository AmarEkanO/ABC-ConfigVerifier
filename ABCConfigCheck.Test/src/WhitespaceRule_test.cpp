/*
** Contains tests for WhitespaceRule
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "WhitespaceRule.h"


TEST(WhitespaceRule_tests, test_for_valid_cases)
{
	WhitespaceRule whitespace;

	EXPECT_EQ(true, whitespace.passes("   "));
	EXPECT_EQ(true, whitespace.passes("\n"));
	EXPECT_EQ(true, whitespace.passes("\t\t"));
	EXPECT_EQ(true, whitespace.passes(""));

}

TEST(WhitespaceRule_tests, test_for_invalid_cases)
{
	WhitespaceRule whitespace;

	EXPECT_EQ(false, whitespace.passes(" some sample text"));
	EXPECT_EQ(false, whitespace.passes(" \t\tsome text"));
	EXPECT_EQ(false, whitespace.passes("some text\t\tmoretext"));
}