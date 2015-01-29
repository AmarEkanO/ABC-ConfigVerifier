/*
** Contains tests for LeName Rule
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "LeNameRule.h"

TEST(LeNameRule_tests, test_for_valid_LE_names)
{
	LeNameRule leName;

	EXPECT_EQ(true,leName.passes(" [App=EDC, Name=EDCRMT]"));
	EXPECT_EQ(true,leName.passes("[  App=EDC, Name=EDCRMT]"));
	EXPECT_EQ(true,leName.passes("[App = EDC, Name = EDCRMT]"));
	EXPECT_EQ(true,leName.passes("[ App=EDC,Name=EDCRMT ]"));
	EXPECT_EQ(true,leName.passes("[ App=EDC,Name=EDCRMT ] ; commnet"));
	EXPECT_EQ(true,leName.passes("[App=EDC,Name=EDCRMT]"));
	EXPECT_EQ(true,leName.passes("[App=MHE, Name=DSBBEP];"));
	EXPECT_EQ(true,leName.passes("[App=MHE, Name=DSBBEP]  ; "));
	EXPECT_EQ(true,leName.passes("[App=MHE, Name=DSBBEP]  ; comments and more comments"));
	EXPECT_EQ(true,leName.passes("[APP=EDC,Name=EDCRMT]"));
}

TEST(LeNameRule_tests, test_for_invalid_LE_names)
{
	LeNameRule leName;

	EXPECT_EQ(false, leName.passes("[Name=ED,App=EDCRM]"));
	EXPECT_EQ(false,leName.passes("[]"));
	EXPECT_EQ(false,leName.passes("[App=,Name=]"));
	EXPECT_EQ(false,leName.passes("[ApP=TEST,NamE=LEEEEEEEEE]"));
	EXPECT_EQ(false,leName.passes("[App=API, Name=DEV000][App=API, Name=DEV000]"));
	EXPECT_EQ(false,leName.passes("[App=API, Name=DEV000]App=API, Name=DEV000]"));
}

TEST(LeNameRule_tests, given_a_valid_le_name_it_should_return_correct_name_and_app)
{
	LeNameRule leName;

	EXPECT_EQ(true, leName.passes("[App=API, Name=DEV000  ]"));
	EXPECT_EQ("API", leName.getApp());
	EXPECT_EQ("DEV000", leName.getName());
}


TEST(LeNameRule_tests, when_an_instance_is_created_name_and_app_should_be_empty)
{
	LeNameRule leName;

	EXPECT_EQ(true, leName.getApp().empty());
	EXPECT_EQ(true, leName.getName().empty());
}

TEST(LeNameRule_tests, given_an_invalid_le_name_it_should_return_empty_name_and_app)
{
	LeNameRule leName;

	EXPECT_EQ(false, leName.passes("[ApP=TEST,NamE=LEEEEEEEEE]"));
	EXPECT_EQ(true, leName.getName().empty());
	EXPECT_EQ(true, leName.getApp().empty());
}

TEST(LeNameRule_tests, parsing_an_invalid_le_name_after_a_successful_match)
{
	LeNameRule leName;

	EXPECT_EQ(true, leName.passes("[App=API, Name=DEV000]"));
	EXPECT_EQ("API", leName.getApp());
	EXPECT_EQ("DEV000", leName.getName());

	EXPECT_EQ(false, leName.passes("[App=DI, ;Name=TRACN]"));
	EXPECT_EQ(true, leName.getApp().empty());
	EXPECT_EQ(true, leName.getName().empty());
}