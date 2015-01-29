#ifndef PORT_H
#define PORT_H

#include<vector>
#include "Property.h"

using namespace std;

class Port
{
public:
	explicit Port();
	virtual ~Port();
	virtual bool hasHeader() const;
	virtual void setHeader(string, string, string, string);
	virtual int propertyCount() const;
	virtual void clearProperties();
	virtual void addProperty(Property);

private:
	string port;
	string protocol;
	string device;
	string processor;
	vector<Property> properties;
};

#endif