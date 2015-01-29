#ifndef PROPERTY_H
#define PROPERTY_H

#include <regex>

using namespace std;

class Property
{
public:
	explicit Property();
	explicit Property(string, string);
	virtual ~Property();
	virtual string getName() const;
	virtual string getValue() const;
	virtual bool operator==(const Property&) const;

private:
	string name;
	string value;
};

#endif