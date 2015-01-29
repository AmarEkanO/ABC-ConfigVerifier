#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <fstream>
#include <string>

using namespace std;

class ConfigHandler
{
public:
	explicit ConfigHandler(const string);
	virtual ~ConfigHandler();
	virtual string getLine();
	virtual bool hasMoreData() const;

private:
	explicit ConfigHandler(const ConfigHandler&);
	fstream configFile;

protected:
	//Used only for mocking purposes
	explicit ConfigHandler(){};
};

#endif