/*
** Contains tests for Port
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "Port.h"

TEST(When_an_instance_of_a_Port_is_created, has_header_should_return_false)
{
	Port port;

	EXPECT_EQ(false, port.hasHeader());
}

TEST(When_a_header_is_set, has_header_should_return_true)
{
	Port port;

	port.setHeader("0", "4", "NODEVICE", "SISOCK.DLL");

	EXPECT_EQ(true, port.hasHeader());
}

TEST(When_an_instance_of_a_Port_is_created, property_count_should_be_zero)
{
	Port port;

	EXPECT_EQ(0, port.propertyCount());
}

TEST(When_properties_are_added_to_a_Port, property_count_should_return_the_correct_value)
{
	Port port;

	const int num_of_props = 5;
	Property property[num_of_props];

	for(int i = 0; i < num_of_props; i++)
		port.addProperty(property[i]);

	EXPECT_EQ(num_of_props, port.propertyCount());
}

TEST(When_properties_are_added_to_a_Port, clear_properties_should_remove_all_properties)
{
	Port port;

	const int num_of_props = 5;
	Property property[num_of_props];

	for(int i = 0; i < num_of_props; ++i)
		port.addProperty(property[i]);

	EXPECT_EQ(num_of_props, port.propertyCount());

	port.clearProperties();

	EXPECT_EQ(0, port.propertyCount());
}