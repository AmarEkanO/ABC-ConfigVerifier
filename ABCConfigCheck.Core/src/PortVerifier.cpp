#include "PortVerifier.h"
#include "Port.h"
#include "Property.h"

PortVerifier::PortVerifier(ConfigHandler& config)
	:configHandle(config)
{
}

PortVerifier::~PortVerifier()
{
}

bool PortVerifier::isValid()
{
	WhitespaceRule whitespace;
	CommentRule comment;
	PropertyRule property;
	PortHeaderRule portHeader;

	Port port;

	bool validConfig = true;
	unsigned int lineNumber = 0;
	string currentLine;

	while(configHandle.hasMoreData())
	{
		currentLine = configHandle.getLine();
		++lineNumber;

		if(whitespace.passes(currentLine))
		{
			continue;
		}
		else if(comment.passes(currentLine))
		{
			continue;
		}
		else if(portHeader.passes(currentLine))
		{
			if(port.hasHeader())
			{
				if(port.propertyCount() > 1)
				{
					port.setHeader(portHeader.getProcessor(), portHeader.getPort(), portHeader.getDevice(), portHeader.getProtocol());
					port.clearProperties();
				}
				else
				{
					invalidEntries.addMessage(lineNumber, currentLine);
					validConfig = false;
				}
			}
			else
			{
				port.setHeader(portHeader.getProcessor(), portHeader.getPort(), portHeader.getDevice(), portHeader.getProtocol());
			}
			continue;
		}
		else if(property.passes(currentLine))
		{
			if(port.hasHeader())
			{
				Property prop(property.getName(), property.getValue());

				port.addProperty(prop);
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

	if(port.hasHeader())
	{
		if(port.propertyCount() < 1)
		{
			invalidEntries.addMessage(lineNumber, currentLine);
			validConfig = false;
		}
	}
	else
	{
		validConfig = false;
	}

	return validConfig;
}

vector<string> PortVerifier::getInvalidEntries()
{
	return invalidEntries.getEntries();
}