/*
** Contains tests for PropertyRule
*/

#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "PropertyRule.h"

TEST(PropertyRule_tests, test_for_valid_property_entries)
{
	PropertyRule property;

	EXPECT_EQ(true,property.passes("KeepAliveTime=10000	"));
	EXPECT_EQ(true,property.passes("TnTxHdrTxt=7d 40 40"));
	EXPECT_EQ(true, property.passes("TnTxHdrTxt   =  7d 40 40"));
	EXPECT_EQ(true,property.passes("	Keep Alive Time=10000 "));

	EXPECT_EQ(true,property.passes("IpHost=127. 0. 0.1"));
	EXPECT_EQ(true,property.passes(" IpHost = 127.0.0.1   "));
	EXPECT_EQ(true,property.passes("TerminalType = vt100"));
	EXPECT_EQ(true,property.passes("On/Off=Yes"));
	EXPECT_EQ(true,property.passes("\tIpHost = ssl:10.9.190.22"));
	EXPECT_EQ(true,property.passes("dsc=__AFW_to_FRONT_Arbitrator(?)"));
	EXPECT_EQ(true,property.passes("RemotePort=5202 ;This is the port on the server"));
}

TEST(PropertyRule_tests, test_for_invalid_property_entries)
{
	PropertyRule property;

	EXPECT_EQ(false, property.passes("IpHost =  ; 127.0.0.1"));
	EXPECT_EQ(false, property.passes("IpHost ;== 127.0.0.1"));
	EXPECT_EQ(false, property.passes("KeepAlive==30000"));
	EXPECT_EQ(false, property.passes("	Keep Alive =Time=10000"));
	EXPECT_EQ(false, property.passes("=test="));
	EXPECT_EQ(false, property.passes("KeepAlive ; == 1000"));
	EXPECT_EQ(false, property.passes("KeepAlive = ;1000"));

}

TEST(PropertyRule_tests, given_a_valid_property_it_should_return_correct_name_and_value)
{
	PropertyRule property;

	EXPECT_EQ(true, property.passes("KeepAlive=60000"));
	EXPECT_EQ("KeepAlive", property.getName());
	EXPECT_EQ("60000", property.getValue());
}


TEST(PropertyRule_tests, when_an_instance_is_created_name_and_value_should_be_empty)
{
	PropertyRule property;

	EXPECT_EQ(true, property.getName().empty());
	EXPECT_EQ(true, property.getValue().empty());
}

TEST(PropertyRule_tests, given_an_invalid_property_it_should_return_empty_name_and_value)
{
	PropertyRule property;

	EXPECT_EQ(false, property.passes("KeepAlive==60000"));
	EXPECT_EQ(true, property.getName().empty());
	EXPECT_EQ(true, property.getValue().empty());
}

TEST(PropertyRule_tests, parsing_an_invalid_property_after_a_successful_match)
{
	PropertyRule property;

	EXPECT_EQ(true, property.passes("Logging=Yes"));
	EXPECT_EQ("Logging", property.getName());
	EXPECT_EQ("Yes", property.getValue());

	EXPECT_EQ(false, property.passes("KeepAlive===600000"));
	EXPECT_EQ(true, property.getName().empty());
	EXPECT_EQ(true, property.getValue().empty());

}