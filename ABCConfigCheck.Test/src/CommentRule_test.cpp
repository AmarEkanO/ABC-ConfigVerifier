/*
** Contains test for CommentRule
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "CommentRule.h"

TEST(CommentRule_tests, test_for_valid_comment_cases)
{
	CommentRule comment;

	EXPECT_EQ(true, comment.passes(";This is a comment"));
	EXPECT_EQ(true, comment.passes(" ; \tComment"));
	EXPECT_EQ(true, comment.passes("; This is a comment"));
	EXPECT_EQ(true, comment.passes(";;;;;;;"));
	EXPECT_EQ(true, comment.passes(" ;  Comment1\t\tComment2\t\t"));
	EXPECT_EQ(true, comment.passes(" ; c1 ; ; c2"));
}

TEST(CommentRule_tests, test_for_invalid_comment_cases)
{
	CommentRule comment;

	EXPECT_EQ(false, comment.passes("Some data ; comment"));
	EXPECT_EQ(false, comment.passes("Property=value"));
	EXPECT_EQ(false, comment.passes("[App=API, Name=DEV000]"));
}