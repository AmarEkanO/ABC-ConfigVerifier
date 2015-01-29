/*
** Contains tests for LE Table
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "LETable.h"
#include "UtilityFunc.h"

using ::testing::Return;

TEST(LETable_tests, When_an_instance_is_created_table_should_be_empty)
{
	LETable table;

	EXPECT_EQ(0,table.leCount());
}

TEST(LETable_tests, Should_be_able_to_add_a_LE_to_the_table)
{
	LETable table;
	LE le;

	le.setName("AOU", "EDCRMT");

	table.add(1,le);

	EXPECT_EQ(1, table.leCount());
}

TEST(LETable_tests, adding_a_LE_with_line_number_less_than_one_should_throw_an_exception)
{
	LETable table;
	LE le;

	le.setName("AMA", "REKANO");

	EXPECT_THROW({
		table.add(-1, le);
	}, InvalidLineNumberException);

	EXPECT_THROW({
		table.add(0, le);
	}, InvalidLineNumberException);
}

TEST(LETable_tests, LE_should_exist_in_the_table_on_being_added)
{
	LETable table;
	LE le;

	le.setName("API", "DEV000");
	table.add(1, le);
	EXPECT_EQ(1, table.leCount());

	LE search_le;
	search_le.setName("API", "DeV000");

	EXPECT_EQ(true, table.leExists(search_le));

}

TEST(LETable_tests, Searching_for_non_existent_LE_should_return_false)
{
	LETable table;
	LE le;

	le.setName("API", "DEV000");
	table.add(1, le);

	EXPECT_EQ(1, table.leCount());

	LE search_le;
	search_le.setName("DEV", "APP000");

	EXPECT_EQ(false, table.leExists(search_le));

}

TEST(LETable_tests, adding_a_duplicatie_LE_to_the_table_raises_an_exception)
{
	LETable table;
	LE le;

	le.setName("API", "DEV000");
	table.add(1, le);

	EXPECT_EQ(1, table.leCount());

	LE dup_le;
	dup_le.setName("API", "DEV000");

	EXPECT_THROW({
		table.add(10, dup_le);
	},DuplicateLeException);
}

TEST(LETable_tests, should_return_the_correct_line_number)
{
	LETable table;
	LE le;
	int lineNumber = 10;

	le.setName("API","DEV000");

	table.add(lineNumber, le);

	LE search_le;
	search_le.setName("api", "dev000");
	
	EXPECT_EQ(lineNumber, table.getLineNumber(search_le));
}

TEST(LETable_tests, adding_an_le_with_no_name_should_raise_an_exception)
{
	LETable table;
	LE le;

	EXPECT_THROW(
	{
		table.add(10, le);
	},UninitializedLeException);
}

TEST(LETable_tests, should_not_allow_adding_the_same_le_more_than_once)
{
	LETable table;
	LE le;

	le.setName("AMA", "REKANO");

	EXPECT_THROW(
	{
		table.add(10, le);
		table.add(10, le);
	}, DuplicateLeException);
}

TEST(LETable_tests, should_be_able_to_return_a_list_of_LEs)
{
	LETable table;
	const int size = 5;
	LE le[size];

	for(int i = 0; i < size; ++i)
		le[i].setName("API","DEV00"+to_string(i));

	for(int i = 0; i < size; i++)
		table.add((i+1)*2, le[i]);

	vector<LE> list  = table.getLeList();

	EXPECT_EQ(size, table.leCount());
	EXPECT_EQ(size, list.size());

	for(int i = 0; i < size; i++)
		EXPECT_EQ(le[i], list[i]);

}