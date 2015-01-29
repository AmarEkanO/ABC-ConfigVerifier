#include "LEInfo.h"

LEInfo::LEInfo(int lineNumber, LE& le)
	: lineNumber(lineNumber), le(le)
{
}

LEInfo::~LEInfo()
{
}

LE& LEInfo::getLE() const
{
	return le;
}

int LEInfo::getLineNumber() const
{
	return lineNumber;
}