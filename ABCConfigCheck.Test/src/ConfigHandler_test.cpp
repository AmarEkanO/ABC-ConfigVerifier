/*
* Contains tests for ConfigHandler
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "ConfigHandler_test.h"

class ConfigHandler_Test : public ::testing::Test
{
public:
	ConfigHandler_Test()
	{
		fileName = "Testfile.ini";
	}

	void SetUp()
	{
		fstream f;
		f.open(fileName, ios::out);
		f << flush;
		f.close();
	}

	void TearDown()
	{
		remove(fileName.c_str());
	}

	string fileName;
};

TEST_F(ConfigHandler_Test, Invalid_file_provided)
{
	EXPECT_THROW(
	{
		remove(fileName.c_str());
		MockConfigHandler handler(fileName);
	},exception);
}


TEST_F(ConfigHandler_Test, Valid_file_provided)
{
	EXPECT_NO_THROW(
	{
		MockConfigHandler handler(fileName);
	});
}

TEST_F(ConfigHandler_Test, File_exists_and_file_is_empty)
{
	EXPECT_NO_THROW(
	{
		ConfigHandler handler(fileName);
		EXPECT_EQ("",handler.getLine());
		EXPECT_EQ(false, handler.hasMoreData());
	});
}

TEST_F(ConfigHandler_Test, File_exists_and_file_has_data)
{
	string data = "This is a sample text";
		fstream f;
		f.open(fileName, ios::app);
		f << data << endl << flush;
		f.close();

	EXPECT_NO_THROW(
	{
		ConfigHandler handler(fileName);
		EXPECT_EQ(handler.getLine(), data);
		
	});
}

TEST_F(ConfigHandler_Test, File_exists_and_has_data_and_empty_lines)
{
	int dataLen = 6;
	string data[] = {"Line1", "", "Line2", " ", "Line3", "		"};
	fstream f(fileName, ios::app);
	for(int i = 0; i < dataLen; i++)
	{
		f << data[i] << endl << flush;
	}
	f.close();

	EXPECT_NO_THROW(
	{
		ConfigHandler handler(fileName);
		bool found = false;
		while(handler.hasMoreData())
		{
			string buffer = handler.getLine();
			
			for(int i = 0; i < dataLen; i++)
			{
				if(buffer == data[i])
					found = true;
			}
			EXPECT_EQ(true, found);
		}

		
	});
}
