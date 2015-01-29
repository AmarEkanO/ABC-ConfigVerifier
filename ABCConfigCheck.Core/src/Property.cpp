#include <string>
#include "Property.h"

Property::Property()
{
	name = "";
	value = "";
}

Property::~Property()
{
}

Property::Property(string name, string value)
{
	this->name = name;
	this->value = value;
}

string Property::getName() const
{
	return name;
}

string Property::getValue() const
{
	return value;
}

bool Property::operator==(const Property& property) const
{
	if(regex_search(this->getName(), regex(property.getName(), regex_constants::icase)))
		return true;

	return false;
}