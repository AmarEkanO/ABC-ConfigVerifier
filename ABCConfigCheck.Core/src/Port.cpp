#include <string>
#include "Port.h"

using namespace std;

Port::Port()
{
	processor = port = device = protocol = "";
}

Port::~Port()
{
}

bool Port::hasHeader() const
{
	if(processor.empty() && port.empty() && device.empty() && protocol.empty())
		return false;

	return true;
}

void Port::setHeader(string processor, string port, string device, string protocol)
{
	this->processor = processor;
	this->port = port;
	this->device = device;
	this->protocol = protocol;
}

int Port::propertyCount() const
{
	return properties.size();
}

void Port::addProperty(Property prop)
{
	properties.push_back(prop);
}

void Port::clearProperties()
{
	properties.clear();
}