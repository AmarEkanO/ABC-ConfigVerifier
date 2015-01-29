#ifndef LE_TABLE_H
#define LE_TABLE_H

#include <map>
#include "LE.h"
#include <regex>

using namespace std;

class tableOrder
{
public:
	bool operator()(const LE&, const LE&) const;
};

class InvalidLineNumberException : public exception
{
public:
	explicit InvalidLineNumberException(string);
};

class UninitializedLeException : public exception
{
public:
	explicit UninitializedLeException(string);
};

class DuplicateLeException : public exception
{
public:
	explicit DuplicateLeException(string);
};

class NonExistentLeException : public exception
{
public:
	explicit NonExistentLeException(string);
};

class LETable
{
public:
	virtual void add(int, LE);
	virtual int getLineNumber(LE);
	virtual bool leExists(LE);
	virtual vector<LE> getLeList();
	virtual int leCount();
	explicit LETable();
	virtual ~LETable();

private:
	map<LE, int, tableOrder> leTable;
};
#endif