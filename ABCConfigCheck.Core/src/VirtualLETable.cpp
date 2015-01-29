#include "VirtualLETable.h"

void VirtualLETable::addLE(LEInfo& leInfo)
{
	virtualLE_list.push_back(leInfo);
}

ErrorLog VirtualLETable::getInvalidEntries()
{
	return invalidEntries;
}

bool VirtualLETable::validateTable()
{
	if(virtualLE_list.size() == 0)
		return true;

	return false;
}