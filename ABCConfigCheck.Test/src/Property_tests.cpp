/*
** Contains tests for Property
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "Property.h"

TEST(When_an_instance_of_Property_is_created, name_and_value_should_be_empty)
{
	Property prop;

	EXPECT_EQ(true, prop.getName().empty());
	EXPECT_EQ(true, prop.getValue().empty());
}

TEST(When_an_instance_of_Property_is_created, name_and_value_should_be_set_using_the_parameterized_constructor)
{
	string name = "Proc";
	string value = "0";

	Property prop(name,value);

	EXPECT_EQ(name, prop.getName());
	EXPECT_EQ(value, prop.getValue());
}

TEST(Given_two_property_instances, both_are_equal_if_their_names_are_equal)
{
	Property prop1("Port", "0");
	Property prop2("pOrT", "0");

	EXPECT_EQ(true, prop1 == prop2);
}