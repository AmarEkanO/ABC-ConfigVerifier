#include "LETable.h"

bool tableOrder::operator()(const LE& lhs, const LE& rhs) const
{
	return lhs.getLeName() < rhs.getLeName();
}

InvalidLineNumberException::InvalidLineNumberException(string message)
	: exception(message.c_str())
{
}

UninitializedLeException::UninitializedLeException(string message)
	:exception(message.c_str())
{
}

DuplicateLeException::DuplicateLeException(string message)
	:exception(message.c_str())
{
}

NonExistentLeException::NonExistentLeException(string message)
	:exception(message.c_str())
{
}

LETable::LETable()
{
	leTable.clear();
}

LETable::~LETable()
{
}

void LETable::add(int lineNumber, LE le)
{
	if(!le.hasName())
		throw UninitializedLeException("Attempt to add uninitialized LE");

	if(lineNumber < 1)
		throw InvalidLineNumberException("Attempt to add invalid line number");

	for(map<LE,int>::iterator it = leTable.begin(); it != leTable.end(); it++)
	{
		if(le == it->first)
			throw DuplicateLeException("Attempt to add duplicate LE");
	}

	leTable[le] = lineNumber;
}

int LETable::getLineNumber(LE le)
{
	for(map<LE,int>::iterator it = leTable.begin(); it != leTable.end(); it++)
	{
		if(le == it->first)
			return it->second;
	}

	throw NonExistentLeException("Attempt to access non-existent LE");
}

bool LETable::leExists(LE le)
{
	for(map<LE,int>::iterator it = leTable.begin(); it != leTable.end(); it++)
	{
		if(le == it->first)
			return true;
	}

	return false;
}

int LETable::leCount()
{
	return leTable.size();
}

vector<LE> LETable::getLeList()
{
	vector<LE> leList;
	for(map<LE,int>::iterator it = leTable.begin(); it != leTable.end(); it++)
		leList.push_back(it->first);
	
	return leList;
}
