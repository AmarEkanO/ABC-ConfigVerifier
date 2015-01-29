/*
** Contains tests for LE
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "LE.h"

TEST(When_an_instance_of_a_LE_is_created, has_name_should_return_false)
{
	LE le;

	EXPECT_EQ(false, le.hasName());
}

TEST(When_a_name_is_set, has_name_should_return_true)
{
	LE le;

	le.setName("API", "DEV000");

	EXPECT_EQ(true, le.hasName());
}

TEST(When_an_instance_of_a_LE_is_created, property_count_should_be_zero)
{
	LE le;

	EXPECT_EQ(0, le.propertyCount());
}

TEST(When_properties_are_added_to_a_LE, property_count_should_return_the_correct_value)
{
	LE le;

	int num_of_props = 4;
	Property property[4];

	for(int i = 0; i < num_of_props; i++)
		le.addProperty(property[i]);

	EXPECT_EQ(num_of_props, le.propertyCount());

}

TEST(When_properties_are_added_to_a_LE, clear_properties_should_remove_all_properties)
{
	LE le;

	int num_of_props = 4;
	Property property[4];

	for(int i = 0; i < num_of_props; ++i)
		le.addProperty(property[i]);

	EXPECT_EQ(num_of_props, le.propertyCount());

	le.clearProperties();

	EXPECT_EQ(0, le.propertyCount());
}

TEST(Given_two_le_instances, the_should_be_equal_if_they_have_the_same_name)
{
	LE le1;
	LE le2;

	le1.setName("API", "DEV000");
	le2.setName("api", "dev000");

	EXPECT_EQ(true, le1 == le2);
}

TEST(Given_a_LE, Get_property_should_return_the_correct_property)
{
	LE le;
	Property port("Port", "4");

	le.addProperty(port);

	Property expected("port", "4");

	EXPECT_EQ(expected, le.getProperty("porT"));
}

TEST(Given_a_LE, Retrieving_a_non_existent_property_should_raise_an_exception)
{
	LE le;
	
	EXPECT_THROW(
	{
		le.getProperty("Port");
	}, NonExistentPropertyException);
}

TEST(Given_a_LE_with_properties, get_property_index_should_return_the_correct_value)
{
	LE le;

	Property props[] = {Property("Proc","0"), Property("Port", "4"), Property("cu","00h")};

	le.addProperty(props[0]);
	le.addProperty(props[1]);
	le.addProperty(props[2]);

	Property search_prop("Port", "4");

	EXPECT_EQ(2, le.getPropertyIndex(search_prop));
}