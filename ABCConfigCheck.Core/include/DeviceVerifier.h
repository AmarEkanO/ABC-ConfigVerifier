#ifndef DEVICEVERIFIER_H
#define DEVICEVERIFIER_H

#include "ConfigHandler.h"
#include "IVerifier.h"
#include "WhitespaceRule.h"
#include "CommentRule.h"
#include "PropertyRule.h"
#include "LeNameRule.h"
#include "ErrorLog.h"
#include "LETable.h"

class InvalidConfigurationException : public exception
{
public:
	explicit InvalidConfigurationException(string);
};

class DeviceVerifier : public IVerifier
{
public:
	explicit DeviceVerifier(ConfigHandler&);
	virtual ~DeviceVerifier();
	virtual bool isValid();
	virtual vector<string> getInvalidEntries();
	virtual LETable getLeTable();
	
private:
	ConfigHandler &configHandle;
	ErrorLog invalidEntries;
	bool validConfig;
	LETable table;
};

#endif