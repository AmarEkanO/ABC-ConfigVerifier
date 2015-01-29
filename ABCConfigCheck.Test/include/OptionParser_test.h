/*
* Contains the definition of mocked OptionParser
*/
#ifndef OPTIONPARSER_TEST_H
#define OPTIONPARSER_TEST_H

#include "gmock\gmock.h"
#include "OptionsParser.h"

class MockOptionParser : public OptionsParser
{
public:
	MockOptionParser(int argc, char* argv[]):OptionsParser(argc, argv){}
	MOCK_CONST_METHOD0(getDevicesIni, string());
	MOCK_CONST_METHOD0(getPortsIni, string());
};

#endif