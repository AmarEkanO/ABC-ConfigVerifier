#include <string>
#include "LE.h"
#include <regex>

using namespace std;

NonExistentPropertyException::NonExistentPropertyException(string message)
	: exception(message.c_str())
{
}

LE::LE()
{
	app = "";
	name = "";
}

LE::~LE()
{
}

bool LE::hasName() const
{
	if(app.empty() && name.empty())
		return false;

	return true;
}

void LE::setName(string app, string name)
{
	this->app = app;
	this->name = name;
}

int LE::propertyCount() const
{
	return properties.size();
}

void LE::addProperty(Property prop)
{
	properties.push_back(prop);
}

void LE::clearProperties()
{
	properties.clear();
}

string LE::getLeName() const
{
	return app+name;
}

bool LE::operator==(const LE& le) const
{
	if(regex_search(this->getLeName(), regex(le.getLeName(), regex_constants::icase)))
		return true;

	return false;
}

Property LE::getProperty(string prop)
{
	for(vector<Property>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		if(regex_search(it->getName(), regex("^"+prop+"$", regex_constants::icase)))
		{
			return *it;
		}
	}

	throw NonExistentPropertyException("Property "+ prop +" does not exist");
}

int LE::getPropertyIndex(Property prop)
{
	return find(properties.begin(), properties.end(), prop) - properties.begin() + 1;
}