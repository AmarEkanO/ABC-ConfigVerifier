#ifndef VIRTUAL_LE_H
#define VIRTUAL_LE_H

#include "IProtocol.h"
#include "ErrorLog.h"

class VirtualLE : public IProtocol
{
public:
	virtual bool check(LE);
	virtual bool validate(LEInfo&);
	virtual ErrorLog getInvalidEntries();
	virtual bool isProcValid(Property);
	virtual bool isCuValid(Property);
	virtual bool isDaValid(Property);
	virtual bool isDefAckValid(Property);
	virtual bool isOnOffValid(Property);

private:
	ErrorLog invalidEntries;
};

#endif