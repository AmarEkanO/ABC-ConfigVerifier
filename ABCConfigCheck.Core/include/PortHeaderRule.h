#ifndef PORT_HEADER_RULE_H
#define PORT_HEADER_RULE_H

#include "IRule.h"

class PortHeaderRule : public IRule
{
public:
	virtual bool passes(string);
	virtual string getProcessor() const;
	virtual string getPort() const;
	virtual string getDevice() const;
	virtual string getProtocol() const;
	explicit PortHeaderRule();

private:
	string processor;
	string port;
	string device;
	string protocol;
};

#endif