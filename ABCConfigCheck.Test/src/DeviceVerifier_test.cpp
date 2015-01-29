/*
* Contains tests for DeviceVerifier
*/

#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include <vector>
#include "DeviceVerifier_test.h"
#include "UtilityFunc.h"

using ::testing::Return;


TEST(Given_a_valid_configuration_file, there_should_be_no_invalid_entries)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("; This is a sample LE"))
		.WillOnce(Return("[App=API, Name =DEV000]"))
		.WillOnce(Return("Port=Virtual"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return(""))
		.WillOnce(Return("; Another LE"))
		.WillOnce(Return("[App=API, Name= DEV001]"))
		.WillOnce(Return("Port= New Port"))
		.WillOnce(Return("Pro c=1"))
		.WillOnce(Return("\t"))
		.WillOnce(Return("\t\t[App=API, Name=DEV002]"))
		.WillOnce(Return("Port=virtual"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("cu=01h"))
		.WillOnce(Return("da=21h"))
		.WillOnce(Return("\n"));


	EXPECT_EQ(true, verifier.isValid());
	EXPECT_EQ(0, verifier.getInvalidEntries().size());
}

TEST(Given_an_invalid_configuration_file, there_should_be_atleast_one_invalid_entry)
{

	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("This is a sample LE"))
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Port=Virtual"))
		.WillOnce(Return("P roc=0"))
		.WillOnce(Return("[API=app, DEV001=Name]"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(true, verifier.getInvalidEntries().size() > 0);
}

TEST(Given_a_configuration, an_LE_definition_with_no_properties_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Port=4"))
		.WillOnce(Return("Proc=0"));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_a_configuration, properties_without_an_associated_LE_definition_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("Cu=00"))
		.WillOnce(Return("Da=10"))
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Port=virtual"))
		.WillOnce(Return("Proc=0"));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_an_empty_configuration_file, it_should_not_be_valid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillRepeatedly(Return(""));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_an_invalid_configuration, error_buffer_must_contain_appropriate_invalid_entries)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	string faulty_LE_name = "[App=API,,Name=DEV000]";
	string faulty_LE_property = "Proc=;1233";

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("; This is a sample LE"))
		.WillOnce(Return(faulty_LE_name))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=1"))
		.WillOnce(Return("[App=API, Name=DEV001]"))
		.WillOnce(Return(faulty_LE_property))
		.WillOnce(Return("\n"))
		.WillOnce(Return("Port=4"));

	EXPECT_EQ(false, verifier.isValid());

	vector<string> invalidEntries = verifier.getInvalidEntries();
	string expected_entry1 = "Line 2: "+ faulty_LE_name;
	string expected_entry2 = "Line 6: "+ faulty_LE_property;

	EXPECT_EQ(true, entryExists(invalidEntries, expected_entry1));
	EXPECT_EQ(true, entryExists(invalidEntries, expected_entry2));

	EXPECT_EQ(4, invalidEntries.size());
}

TEST(Given_an_invalid_configuration, config_ending_with_a_le_name_but_no_properties_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=2"))
		.WillOnce(Return("[App=API, Name=DEV001]"));

	string expected_entry = "Line 4: [App=API, Name=DEV001]";

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(1, verifier.getInvalidEntries().size());
	
	EXPECT_EQ(true, entryExists(verifier.getInvalidEntries(), expected_entry));
}

TEST(Given_an_invalid_configuration, config_with_only_properties_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("Port=4"))
		.WillOnce(Return("IpHost=127.0.0.1"))
		.WillOnce(Return("RemotePort=6001"))
		.WillOnce(Return("Proc=0"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(4, verifier.getInvalidEntries().size());
}

TEST(Given_an_invalid_configuration, config_with_only_comments_and_whitespaces_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return(" "))
		.WillOnce(Return("\t   "))
		.WillOnce(Return("; This is a silly comment"))
		.WillOnce(Return("\t\t"))
		.WillOnce(Return(";This is a empty file"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(0, verifier.getInvalidEntries().size());
}

TEST(Given_an_invalid_configuration, config_with_only_a_le_name_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[App=API, Name=DEV000]"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(1, verifier.getInvalidEntries().size());
}

TEST(Retrieving_a_LE_table_without_verifying_the_config, should_raise_an_exception)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_THROW(
	{
		verifier.getLeTable();
	},InvalidConfigurationException);
}

TEST(Given_a_valid_configuration, A_parsed_LE_should_be_present_in_the_table)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	LE le;
	le.setName("API", "DEV000");

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=4"));


	EXPECT_EQ(true, verifier.isValid());

	LETable testTable = verifier.getLeTable();

	EXPECT_EQ(true, testTable.leExists(le));
}

TEST(Given_an_invalid_configuration, duplicate_le_definitions_should_be_invalid)
{
	MockConfigHandler handler;
	DeviceVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=4"))
		.WillOnce(Return("[App=API, Name=DEV000]"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=virtual"));

	string expected_entry = "Line 4: APIDEV000 --> Attempt to add duplicate LE";

	EXPECT_EQ(false, verifier.isValid());

	EXPECT_EQ(true, entryExists(verifier.getInvalidEntries(), expected_entry));

}