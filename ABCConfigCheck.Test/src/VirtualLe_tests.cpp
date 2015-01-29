/*
** Contains tests for VirtualLE
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "UtilityFunc.h"
#include "VirtualLe.h"

TEST(Given_a_virtual_le, check_should_return_true)
{
	LE le;
	Property prop("Port", "virtuaL");

	le.addProperty(prop);

	VirtualLE verifier;

	EXPECT_EQ(true, verifier.check(le));
}

TEST(Given_a_non_virtual_le, check_should_return_false)
{
	LE le;
	Property prop("Port", "4");

	le.addProperty(prop);

	VirtualLE verifier;

	EXPECT_EQ(false, verifier.check(le));
}

TEST(Given_an_le, if_no_port_property_exists_an_exception_should_be_raised)
{
	LE le;
	Property prop("Proc", "1");

	le.addProperty(prop);

	VirtualLE verifier;


	EXPECT_THROW(
	{
		verifier.check(le);
	}, NonExistentPropertyException);
}

TEST(Given_a_le_without_a_Proc_property, validate_should_return_false_and_invalid_entry_should_be_logged)
{
	LE le;
	le.setName("API","DEV000");
	int lineNumber = 10;
	VirtualLE verifier;
	LEInfo info(lineNumber,le);

	EXPECT_EQ(false, verifier.validate(info));

	string expected_entry = "Line "+to_string(lineNumber)+": "+le.getLeName() + " --> Property Proc does not exist";

	EXPECT_EQ(true, entryExists(verifier.getInvalidEntries().getEntries(), expected_entry));
}

TEST(Given_an_le_with_an_unsupported_Proc_value, isProcValid_should_return_false)
{
	Property prop("Proc", "1");
	VirtualLE verifier;

	EXPECT_EQ(false, verifier.isProcValid(prop));
}

TEST(Given_an_le_with_a_supported_Proc_value, isProcValid_should_return_true)
{
	Property prop("Proc", "0");
	VirtualLE verifier;

	EXPECT_EQ(true, verifier.isProcValid(prop));
}

TEST(Given_an_le_with_an_unsupported_cu_value, isCuValid_should_return_false)
{
	Property prop("cU", "77h");
	VirtualLE verifier;
    //Out of range test
	EXPECT_EQ(false, verifier.isCuValid(prop));
	
	prop = Property("cu", "-00h");
	EXPECT_EQ(false,verifier.isCuValid(prop));

    prop = Property("cu", "0xFFh");
	EXPECT_EQ(false, verifier.isCuValid(prop));

    // Invalid value test
	prop = Property("cu", "helloWorld");
	EXPECT_EQ(false, verifier.isCuValid(prop));

    prop = Property("cu", "0xXE");
	EXPECT_EQ(false, verifier.isCuValid(prop));

}

TEST(Given_an_le_with_a_supported_cu_value, isCuValid_should_return_true)
{
	Property prop("cu", "0x00");
	VirtualLE verifier;

	EXPECT_EQ(true, verifier.isCuValid(prop));

	prop = Property("Cu", "1");
	EXPECT_EQ(true, verifier.isCuValid(prop));

	prop = Property("cU", "02h");
	EXPECT_EQ(true, verifier.isCuValid(prop));
}

TEST(Given_an_le_with_an_unsupported_da_value, isDaValid_should_return_false)
{
	VirtualLE verifier;
	Property prop("da", "-1h");

	EXPECT_EQ(false, verifier.isDaValid(prop));

	prop = Property("DA", "0xFFF");
	EXPECT_EQ(false, verifier.isDaValid(prop));

	prop = Property("dA", "blabla");
	EXPECT_EQ(false, verifier.isDaValid(prop));

	prop = Property("da", "747");
	EXPECT_EQ(false, verifier.isDaValid(prop));
}

TEST(Given_an_le_with_a_supported_da_value, isDaValid_should_return_true)
{
	VirtualLE verifier;
	Property prop("da", "0x001h");

	EXPECT_EQ(true, verifier.isDaValid(prop));

	prop = Property("Da", "255");
	EXPECT_EQ(true, verifier.isDaValid(prop));

	prop = Property("dA", "17h");
	EXPECT_EQ(true, verifier.isDaValid(prop));

	prop = Property("da", "0x24");
	EXPECT_EQ(true, verifier.isDaValid(prop));
}

TEST(Given_an_le_with_a_unsupported_defack_value, isDefAckValid_should_return_false)
{
	VirtualLE verifier;
	Property prop("DeferredAck", "Maybe");

	EXPECT_EQ(false, verifier.isDefAckValid(prop));
}

TEST(Given_an_le_with_a_supported_defack_value, isDefAckValid_should_return_true)
{
	VirtualLE verifier;
	Property prop("DeferredAck", "YeS");

	EXPECT_EQ(true, verifier.isDefAckValid(prop));

	prop = Property("DeferredAck", "NO");

	EXPECT_EQ(true, verifier.isDefAckValid(prop));
}

TEST(Given_an_le_with_a_supported_On_Off_value, isOnOffValid_should_return_true)
{
	VirtualLE verifier;
	Property prop("On/Off", "YES");

	EXPECT_EQ(true, verifier.isOnOffValid(prop));

	prop = Property("On/OFf", "No");

	EXPECT_EQ(true, verifier.isOnOffValid(prop));
}

TEST(Given_an_le_with_an_unsupported_ON_off_value, isOnOffValid_should_return_false)
{
	VirtualLE verifier;
	Property prop("On/Off", "Maybe");

	EXPECT_EQ(false, verifier.isOnOffValid(prop));
}