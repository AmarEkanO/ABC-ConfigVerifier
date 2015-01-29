/*
* Contains tests for PortHeader rule
*/

#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "PortHeaderRule.h"

TEST(PortHeaderRule_tests, test_for_valid_port_headers)
{
	PortHeaderRule portHeader;

	EXPECT_EQ(true,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));
	EXPECT_EQ(true,portHeader.passes("[Processor= 1, Port= 77, Device = DCP2$, Protocol=  SI3271.DLM]"));
	EXPECT_EQ(true,portHeader.passes("    [ Processor=0, Port=0, Device=DCP1$, Protocol=SI.DLL] ; comments"));
	EXPECT_EQ(true,portHeader.passes("    [ Processor=0, Port=0, Device=DCP1$, Protocol=SI.DLL] ; "));
	EXPECT_EQ(true,portHeader.passes("    [ Processor=0, Port=0, Device=DCP1$, Protocol=SI.DLL];"));
	EXPECT_EQ(true,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL] ; ;;; "));

}

TEST(PortHeaderRule_tests, test_for_invalid_port_headers)
{
	PortHeaderRule portHeader;

	EXPECT_EQ(false,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL,,]"));
	EXPECT_EQ(false,portHeader.passes("[Processor=0,,, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));
	EXPECT_EQ(false,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]]"));
	EXPECT_EQ(false,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL] \t\tadsadad"));
	EXPECT_EQ(false,portHeader.passes("[[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));
	EXPECT_EQ(false,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]asdad"));
	EXPECT_EQ(false,portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));

}

TEST(PortHeaderRule_test, given_a_valid_port_header_it_should_return_correct_values)
{
	PortHeaderRule portHeader;
	
	EXPECT_EQ(true, portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));
	EXPECT_EQ("0", portHeader.getProcessor());
	EXPECT_EQ("0", portHeader.getPort());
	EXPECT_EQ("DCP1$", portHeader.getDevice());
	EXPECT_EQ("SI3271.DLL", portHeader.getProtocol());
}

TEST(PortHeaderRule_tests, when_an_instance_is_created_properties_should_be_empty)
{
	PortHeaderRule portHeader;

	EXPECT_EQ(true, portHeader.getProcessor().empty());
	EXPECT_EQ(true, portHeader.getPort().empty());
	EXPECT_EQ(true, portHeader.getDevice().empty());
	EXPECT_EQ(true, portHeader.getProtocol().empty());
}

TEST(PortHeaderRule_tests, given_an_invalid_port_header_it_should_return_empty_values)
{
	PortHeaderRule portHeader;

	EXPECT_EQ(false, portHeader.passes("[Processor=0, Port=0, Device=DCP1$, xProtocol=SI3271.DLL]"));
	EXPECT_EQ(true, portHeader.getProcessor().empty());
	EXPECT_EQ(true, portHeader.getPort().empty());
	EXPECT_EQ(true, portHeader.getDevice().empty());
	EXPECT_EQ(true, portHeader.getProtocol().empty());
}

TEST(PortHeaderRule_tests, parsing_an_invalid_port_header_after_a_successful_match)
{
	PortHeaderRule portHeader;

	EXPECT_EQ(true, portHeader.passes("[Processor=0, Port=0, Device=DCP1$, Protocol=SI3271.DLL]"));
	EXPECT_EQ("0", portHeader.getProcessor());
	EXPECT_EQ("0", portHeader.getPort());
	EXPECT_EQ("DCP1$", portHeader.getDevice());
	EXPECT_EQ("SI3271.DLL", portHeader.getProtocol());

	EXPECT_EQ(false, portHeader.passes("[Processor=0, Port=4, Device=NODEVICE, xProtocol=SISOCK.DLL]"));
	EXPECT_EQ(true, portHeader.getProcessor().empty());
	EXPECT_EQ(true, portHeader.getPort().empty());
	EXPECT_EQ(true, portHeader.getDevice().empty());
	EXPECT_EQ(true, portHeader.getProtocol().empty());
}