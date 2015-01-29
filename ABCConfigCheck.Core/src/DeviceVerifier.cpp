#include "DeviceVerifier.h"
#include "LE.h"
#include "Property.h"

InvalidConfigurationException::InvalidConfigurationException(string message)
	:exception(message.c_str())
{
}

DeviceVerifier::DeviceVerifier(ConfigHandler& config)
	:configHandle(config), validConfig(false)
{
}

DeviceVerifier::~DeviceVerifier()
{
}

LETable DeviceVerifier::getLeTable()
{
	if(validConfig)
		return table;
	else
		throw InvalidConfigurationException("Attempt to retrieve LE Table of an invalid configuration");
}

bool DeviceVerifier::isValid()
{
	WhitespaceRule whitespace;
	CommentRule comment;
	PropertyRule property;
	LeNameRule leName;

	LE le;

	validConfig = true;

	unsigned int lineNumber = 0;
	string currentLine;

	while (configHandle.hasMoreData())
	{
		++lineNumber;
		currentLine = configHandle.getLine();
		

		//is the line empty?
		if(whitespace.passes(currentLine))
		{
			continue;
		}
		//is the line a comment?
		else if(comment.passes(currentLine))
		{
			continue;
		}
		//is the line an LE name?
		else if(leName.passes(currentLine))
		{
			if(le.hasName())
			{
				if(le.propertyCount() > 1)
				{
					//Add le to table
					try
					{
					table.add(lineNumber, le);
					}
					catch(DuplicateLeException const &ex)
					{
						invalidEntries.addMessage(lineNumber - le.propertyCount(), le.getLeName(), string(ex.what()));
						validConfig = false;
					}

					le.setName(leName.getApp(), leName.getName());
					le.clearProperties();
				}
				else
				{
					invalidEntries.addMessage(lineNumber, currentLine);
					validConfig = false;
				}
			}
			else
			{
				le.setName(leName.getApp(), leName.getName());
			}
			continue;
		}
		//is the line an LE property?
		else if(property.passes(currentLine))
		{
			if(le.hasName())
			{
				//Create a property
				Property prop(property.getName(), property.getValue());

				//Add property to LE
				le.addProperty(prop);
			}
			else
			{
				invalidEntries.addMessage(lineNumber, currentLine);
				validConfig = false;
			}
			continue;
		}
		else
		{
			invalidEntries.addMessage(lineNumber, currentLine);
			validConfig = false;
		}
	}

	if(le.hasName())
	{
		if(le.propertyCount() < 1)
		{
			invalidEntries.addMessage(lineNumber, currentLine);
			validConfig = false;
		}
		else
		{
			try
			{
			table.add(lineNumber - le.propertyCount(), le);
			}
			catch(DuplicateLeException const &ex)
			{
				invalidEntries.addMessage(lineNumber - le.propertyCount(), le.getLeName(),string(ex.what()));
				validConfig = false;
			}
		}
	}
	else
	{
		validConfig = false;
	}
	
	return validConfig;
}

vector<string> DeviceVerifier::getInvalidEntries()
{
	return invalidEntries.getEntries();
}
