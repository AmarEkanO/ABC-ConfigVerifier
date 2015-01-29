/*
* Contains tests for PortVerifier
*/

#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include <vector>
#include "PortVerifier_test.h"
#include "UtilityFunc.h"

using ::testing::Return;


TEST(Given_a_valid_configuration_file, there_should_be_no_invlaid_entries)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

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
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("; Port 0 definition"))
		.WillOnce(Return("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"))
		.WillOnce(Return("PollTimeOut=60000"))
		.WillOnce(Return("Tries=3"))
		.WillOnce(Return("Syns=2"))
		.WillOnce(Return("Pads=3"))
		.WillOnce(Return("Cts=250"))
		.WillOnce(Return("\n"))
		.WillOnce(Return(""))
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL] ; Port 4 definition"))
		.WillOnce(Return("KeepAliveTime=10000"))
		.WillOnce(Return("Logging=YES"))
		.WillOnce(Return("TnTxHdrTxt=7d 40 40"));

	EXPECT_EQ(true, verifier.isValid());
	EXPECT_EQ(0, verifier.getInvalidEntries().size());
}

TEST(Given_an_invalid_port_configuration_file, there_should_be_atleast_one_invalid_entry)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[Processor=ABC, Port=10, Device=NODEV, Protocol=Lol.DLL,]"))
		.WillOnce(Return("Tries=600"))
		.WillOnce(Return(">This is some garbage<"))
		.WillOnce(Return("Cts=10"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(true, verifier.getInvalidEntries().size() > 0);
}

TEST(Given_a_configuration, a_Port_header_with_no_properties_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[Processor=ABC, Port=10, Device=NODEV, Protocol=Lol.DLL]"))
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]"))
		.WillOnce(Return("KeepAliveTime=6000"))
		.WillOnce(Return("Logging=No"));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_a_configuration, properties_without_an_associated_Port_definition_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("ConnTime=1200"))
		.WillOnce(Return("Logging=Yes"))
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]"))
		.WillOnce(Return("KeepAliveTime=100000"));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_an_empty_port_configuration_file, it_should_not_be_valid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillRepeatedly(Return(""));

	EXPECT_EQ(false, verifier.isValid());
}

TEST(Given_an_invalid_port_configuration, error_buffer_must_contain_appropriate_invalid_entries)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

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

	string faulty_port_header = "[Processor=0, Port=0, Device=NODEVICE,,Protocol=NOPROTOCOL]";
	string faulty_port_property = "Proc=;1233";

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("; This is a sample LE"))
		.WillOnce(Return(faulty_port_header))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=1"))
		.WillOnce(Return("[Processor=0, Port=0, Device=NODEVICE, Protocol=SISOCK.DLL]"))
		.WillOnce(Return(faulty_port_property))
		.WillOnce(Return("\n"))
		.WillOnce(Return("Port=4"));

	EXPECT_EQ(false, verifier.isValid());

	vector<string> invalidEntries = verifier.getInvalidEntries();
	string expected_entry1 = "Line 2: "+ faulty_port_header;
	string expected_entry2 = "Line 6: "+ faulty_port_property;

	EXPECT_EQ(true, entryExists(invalidEntries, expected_entry1));
	EXPECT_EQ(true, entryExists(invalidEntries, expected_entry2));

	EXPECT_EQ(4, invalidEntries.size());
}

TEST(Given_an_invalid_configuration, config_ending_with_a_port_header_but_no_properties_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]"))
		.WillOnce(Return("Proc=0"))
		.WillOnce(Return("Port=2"))
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]"));

	string expected_entry = "Line 4: [Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]";

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(1, verifier.getInvalidEntries().size());
	
	EXPECT_EQ(true, entryExists(verifier.getInvalidEntries(), expected_entry));
}

TEST(Given_an_invalid_port_configuration, config_with_only_properties_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

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

TEST(Given_an_invalid_port_configuration, config_with_only_comments_and_whitespaces_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

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

TEST(Given_an_invalid_port_configuration, config_with_only_a_port_header_should_be_invalid)
{
	MockConfigHandler handler;
	PortVerifier verifier(handler);

	EXPECT_CALL(handler, hasMoreData())
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));

	EXPECT_CALL(handler, getLine())
		.WillOnce(Return("[Processor=0, Port=4, Device=NODEVICE, Protocol=SISOCK.DLL]"));

	EXPECT_EQ(false, verifier.isValid());
	EXPECT_EQ(1, verifier.getInvalidEntries().size());
}