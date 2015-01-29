#include "ConfigHandler.h"

using namespace std;

ConfigHandler::ConfigHandler(const string fileName)
{
	if(fileName.empty())
		throw exception("Empty file name");

	configFile.open(fileName, ios::in);
	if(!configFile.good())
		throw exception("Unable to read file");

}

ConfigHandler::ConfigHandler(const ConfigHandler& config)
{
}

ConfigHandler::~ConfigHandler()
{
	configFile.close();
}

bool ConfigHandler::hasMoreData() const
{
	return configFile.eof() ? false : true;
}

string ConfigHandler::getLine()
{
	string s;
	if(!configFile.eof())
	{
		getline(configFile,s);
	}
	return s;
}