#ifndef OPTIONSPARSER_H
#define OPTIONSPARSER_H

#include<string>

using namespace std;

class OptionsParser
{
public:
	explicit OptionsParser(int, char*[]);
	string getDevicesIni() const;
	string getPortsIni() const;

private:
	string fnDevicesIni;
	string fnPortsIni;

};


#endif