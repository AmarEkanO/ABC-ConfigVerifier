#include "VirtualLe.h"
#include <sstream>

bool VirtualLE::check(LE le)
{
	//Check Port value
	Property port = le.getProperty("Port");
	if(regex_search("virtual", regex(port.getValue(), regex_constants::icase)))
		return true;

	return false;
}

bool VirtualLE::validate(LEInfo& info)
{
	LE& le = info.getLE();
	int lineNumber = info.getLineNumber();
	bool validLE = true;

	//Check Proc value
	try
	{
	Property prop = le.getProperty("Proc");
	if(!isProcValid(prop))
	{
		validLE = false;
		invalidEntries.addMessage(le.getPropertyIndex(prop) + lineNumber, prop.getName() + "=" +prop.getValue(), "Unsupported Proc value; should have been 0");
	}
	
	//Check cu value range: 0-3
	prop = le.getProperty("cu");

	if(!isCuValid(prop))
	{
		validLE = false;
		invalidEntries.addMessage(le.getPropertyIndex(prop) + lineNumber, prop.getName() + "=" + prop.getValue(), "Unsupported CU value; should have been between 0 to 3");
	}

	//Check da value

	prop = le.getProperty("da");

	if(!isDaValid(prop))
	{
		validLE = false;
		invalidEntries.addMessage(le.getPropertyIndex(prop) + lineNumber, prop.getName() + "=" + prop.getValue(), "Unsupported DA value; should have been between 0 to 255");
	}

	//Check for optional parameters
	// Check for DeferredAck
	try
	{
		prop = le.getProperty("DeferredAck");

		if(!isDefAckValid(prop))
		{
			validLE = false;
			invalidEntries.addMessage(le.getPropertyIndex(prop) + lineNumber, prop.getName() + "=" + prop.getValue(), "Unsupported DeferredAck value; should have been either Yes or No");
		}
	}
	catch(NonExistentPropertyException const &ex)
	{
		//Optional parameter so ignore
	}

	//Check for On/Off
	try
	{
		prop = le.getProperty("On/Off");

		if(!isOnOffValid(prop))
		{
			validLE = false;
			invalidEntries.addMessage(le.getPropertyIndex(prop) + lineNumber, prop.getName() + "=" + prop.getValue(), "Unsupported On/Off value; should have been either Yes or No");
		}
	}
	catch(NonExistentPropertyException const &ex)
	{
		// Optional parameter so ignore
	}


	}
	catch(NonExistentPropertyException const &ex)
	{
		validLE = false;
		invalidEntries.addMessage(lineNumber, le.getLeName(), string(ex.what()));
	}

	return validLE;
}

bool VirtualLE::isDaValid(Property prop)
{
	 //Check if the value is a hex number
	regex hexValue("^0x(([0-9]|[ABCDEF])+)h?|^(([0-9]|[ABCDEF])+)h$");
	regex decValue("^(\\d+)$");
	smatch match;

	int daVal;
	stringstream ss;
	string value = prop.getValue();

	if(regex_search(value, match, hexValue))
	{
		string hexString;
		if(match[1].length() > 0)
		{
			//Get value
			hexString = match[1];
		}
		else if(match[3].length() > 0)
		{
			//get value
			hexString = match[3];
		}
		else
		{
			//Match failed to extract values
			return false;
		}

		//Convert to integer
		
		ss << hex << hexString;
		ss >> daVal;

		if(daVal >=0 && daVal <= 255)
			return true;
		else
			return false;
	}
	

	//if not check for decimal
	if(regex_search(value, match, decValue))
	{
		if(match[1].length() > 0)
		{
			ss << match[1];
			ss >> daVal;

			if(daVal >= 0 && daVal <= 255)
				return true;
		}
		else
		{
			//Match failed to extract values
			return false;
		}
	}
	

	// if both fail we have garbage
	return false;
}

bool VirtualLE::isCuValid(Property prop)
{
    //Check if the value is a hex number
	regex hexValue("^0x(([0-9]|[ABCDEF])+)h?|^(([0-9]|[ABCDEF])+)h$");
	regex decValue("^(\\d+)$");
	smatch match;

	int cuVal;
	stringstream ss;
	string value = prop.getValue();

	if(regex_search(value, match, hexValue))
	{
		string hexString;
		if(match[1].length() > 0)
		{
			//Get value
			hexString = match[1];
		}
		else if(match[3].length() > 0)
		{
			//get value
			hexString = match[3];
		}
		else
		{
			//Match failed to extract values
			return false;
		}

		//Convert to integer
		
		ss << hex << hexString;
		ss >> cuVal;

		if(cuVal >=0 && cuVal <= 3)
			return true;
		else
			return false;
	}
	

	//if not check for decimal
	if(regex_search(value, match, decValue))
	{
		if(match[1].length() > 0)
		{
			ss << match[1];
			ss >> cuVal;

			if(cuVal >= 0 && cuVal <= 3)
				return true;
		}
		else
		{
			//Match failed to extract values
			return false;
		}
	}
	

	// if both fail we have garbage
	return false;
}

bool VirtualLE::isProcValid(Property prop)
{
	if(prop.getValue() == "0")
		return true;
	return false;
}

bool VirtualLE::isDefAckValid(Property prop)
{
	string value = prop.getValue();
	if(regex_search(value, regex("^\\s*Yes|No\\s*$",regex_constants::icase)))
	{
		return true;
	}
	return false;
}

bool VirtualLE::isOnOffValid(Property prop)
{
	string value = prop.getValue();
	if(regex_search(value, regex("^\\s*Yes|No\\s*$",regex_constants::icase)))
	{
		return true;
	}
	return false;
}

ErrorLog VirtualLE::getInvalidEntries()
{
	return invalidEntries;
}