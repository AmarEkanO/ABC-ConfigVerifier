/*
* Contains tests for OptionParser
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "OptionParser_test.h"
#include "OptionsParser.h"

TEST(OptionParser_Tests_Invalid_Options, No_parameters_passed)
{
	//Create test buffers
	int argc = 1;
	char* argv[] = {"test.exe"};

	EXPECT_THROW({
		MockOptionParser optionParser(argc,argv);
	},invalid_argument);
}

TEST(OptionParser_Tests_Invalid_Options, Unknown_parameters_passed)
{
	using ::testing::Return;

	int argc = 3;
	char* argv[] = {"test.exe", "-x","Unknown data", "-z", "AlienData"};

	EXPECT_NO_THROW({
		MockOptionParser optionParser(argc, argv);

		EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return(""));
		EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return(""));

		optionParser.getDevicesIni();
		optionParser.getPortsIni();

	});
}

TEST(OptionsParser_Tests_Invalid_Options, Too_many_parameter_passed)
{
	int argc = 7;
	char* argv[] = {"test.exe", "-p", "file1", "-d", "file2", "-z", "Unknown data"};

	EXPECT_THROW(
	{
		MockOptionParser optionParser(argc, argv);
	},invalid_argument);

}

TEST(OptionParser_Tests_Invalid_Options, valid_and_unknown_parameters_passed)
{
	using ::testing::Return;

	int argc = 5;
	char* argv[] = {"test.exe", "sillyoption" , "Alien data", "-p", "ports.ini" };

	EXPECT_NO_THROW({
		MockOptionParser optionParser(argc, argv);

		EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return(""));
		EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return("ports.ini"));

		optionParser.getDevicesIni();
		optionParser.getPortsIni();

	});
}

TEST(OptionParser_Tests_Invalid_Options, one_incomplete_parameter_passed)
{
	int argc = 2;
	char* argv[] = {"test.exe", "-d"};

	EXPECT_THROW(
	{
		MockOptionParser optionParser(argc, argv);
	}, invalid_argument);
}

/*TEST(OptionParser_Tests_Invalid_Options, one_valid_and_incomplete_parameters_passed)
{
	using ::testing::Return;

	int argc = 4;
	char* argv[] = {"test.exe", "-d", "some_data", "-p"};

	EXPECT_NO_THROW(
	{
		MockOptionParser optionParser(argc, argv);

		EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return("some_data"));
		EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return(""));

		optionParser.getDevicesIni();
		optionParser.getPortsIni();
	});
}
*/
TEST(OptionParser_Test_Valid_Options, only_devices_ini)
{
	using ::testing::Return;

	int argc = 3;
	char* argv[] = {"test.exe", "-d", "devices.ini"};
	EXPECT_NO_THROW({
	MockOptionParser optionParser(argc, argv);

	EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return("devices.ini"));
	EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return(""));


	optionParser.getDevicesIni();
	optionParser.getPortsIni();
	});

	
}

TEST(OptionParser_Test_Valid_Options, only_ports_ini)
{
	using ::testing::Return;

	int argc = 3;
	char* argv[] = {"test.exe", "-p", "ports.ini"};
	EXPECT_NO_THROW(
	{
	MockOptionParser optionParser(argc, argv);

	EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return("ports.ini"));
	EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return(""));

	optionParser.getPortsIni();
	optionParser.getDevicesIni();
	});
}

TEST(OptionParser_Test_Valid_Options, both_devices_and_ports_ini)
{
	using ::testing::Return;

	int argc = 5;
	char* argv[] = {"test.exe", "-p", "ports.ini", "-d", "devices.ini"};

	//EXPECT_NO_THROW(
	//{
		OptionsParser optionParser(argc, argv);

		//EXPECT_CALL(optionParser, getDevicesIni()).WillOnce(Return("devices.ini"));
		//EXPECT_CALL(optionParser, getPortsIni()).WillOnce(Return("bla"));
		
		EXPECT_EQ("ports.ini", optionParser.getPortsIni());
		EXPECT_EQ("devices.ini", optionParser.getDevicesIni());
		
//	});

}
