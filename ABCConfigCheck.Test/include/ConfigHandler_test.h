/*
* Contains definition of mocked ConfigHandler
*/
#ifndef CONFIG_HANDLER_TEST_H
#define CONFIG_HANDLER_TEST_H

#include "gmock\gmock.h"
#include "ConfigHandler.h"

class MockConfigHandler : public ConfigHandler
{
public:
	MockConfigHandler(string filename): ConfigHandler(filename){}
	MockConfigHandler():ConfigHandler(){};
	MOCK_METHOD0(getLine, string());
	MOCK_CONST_METHOD0(hasMoreData, bool());
};

#endif