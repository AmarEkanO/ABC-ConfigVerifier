/*
** Contains tests for Virtual LE Table
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "LE_test.h"
#include "VirtualLETable.h"
#include "UtilityFunc.h"

using ::testing::Return;

TEST(Given_an_empty_table, table_should_be_valid_with_no_error_entries)
{
	VirtualLETable table;

	EXPECT_EQ(true, table.validateTable());

	EXPECT_EQ(0,table.getInvalidEntries().getEntries().size());
}

TEST(Given_a_table_with_a_valid_LE_pair, table_should_be_valid_with_no_error_entries)
{
	VirtualLETable table;
	MockLE le;
	MockLE le2;

	//le should return same cu, da props
	EXPECT_CALL(le, getProperty("cu"))
		.WillOnce(Return(Property("cu","0")));

	EXPECT_CALL(le, getProperty("da"))
		.WillOnce(Return(Property("da","24")));

	//le2 shoudl return the same cu, da props
	EXPECT_CALL(le2, getProperty("cu"))
		.WillOnce(Return(Property("cu", "0")));

	EXPECT_CALL(le2, getProperty("da"))
		.WillOnce(Return(Property("da","24")));

	table.addLE(LEInfo(10,le2));
	table.addLE(LEInfo(20,le));
	
	EXPECT_EQ(true, table.validateTable());
}