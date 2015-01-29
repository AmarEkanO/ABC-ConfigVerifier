#ifndef VIRTUAL_LE_TABLE_H
#define VIRTUAL_LE_TABLE_H

#include <vector>
#include "LEInfo.h"
#include "ErrorLog.h"

class VirtualLETable
{
public:
	virtual void addLE(LEInfo&);
	virtual bool validateTable();
	virtual ErrorLog getInvalidEntries();

private:
	vector<LEInfo> virtualLE_list;
	ErrorLog invalidEntries;
};

#endif