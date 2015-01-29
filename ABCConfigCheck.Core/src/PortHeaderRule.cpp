#include<string>
#include<regex>
#include "PortHeaderRule.h"

PortHeaderRule::PortHeaderRule()
{
	processor = "";
	port = "";
	device = "";
	protocol = "";
}

bool PortHeaderRule::passes(string line)
{
	regex PortHeaderRx("^\\s*\\[\\s*Processor\\s*=\\s*(\\d+)\\s*,\\s*Port\\s*=\\s*(\\d+)\\s*,\\s*Device\\s*=\\s*([^,]*)\\s*,\\s*Protocol\\s*=\\s*([^,\\]]*)\\s*\\]\\s*(;.*)?$",regex_constants::icase);
	smatch match;

	if(regex_search(line, match, PortHeaderRx))
	{
		processor = match[1];
		port = match[2];
		device = match[3];
		protocol = match[4];
		return true;
	}
	else
	{
		processor = "";
		port = "";
		device = "";	
		protocol = "";
	}
	return false;
}

string PortHeaderRule::getDevice() const
{
	return device;
}

string PortHeaderRule::getPort() const
{
	return port;
}

string PortHeaderRule::getProcessor() const
{
	return processor;
}

string PortHeaderRule::getProtocol() const
{
	return protocol;
}