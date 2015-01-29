#ifndef LE_H
#define LE_H

#include <vector>
#include "Property.h"

using namespace std;

class NonExistentPropertyException : public exception
{
public:
	NonExistentPropertyException(string);
};

class LE
{
public:
	explicit LE();
	virtual ~LE();
	virtual bool hasName() const;
	virtual string getLeName() const;
	virtual void setName(string, string);
	virtual int propertyCount() const;
	virtual void addProperty(Property);
	virtual void clearProperties();
	virtual Property getProperty(string);
	virtual int getPropertyIndex(Property);
	virtual bool operator==(const LE&) const;

private:
	string app;
	string name;
	vector<Property> properties;
};

#endif