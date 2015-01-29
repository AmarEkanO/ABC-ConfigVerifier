#ifndef LE_INFO_H
#define LE_INFO_H

#include "LE.h"

class LEInfo
{
public:
	explicit LEInfo(int, LE&);
	virtual LE& getLE() const;
	virtual int getLineNumber() const;
	virtual ~LEInfo();

private:
	LEInfo();
	LE& le;
	int lineNumber;
};

#endif