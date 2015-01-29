#include "OptionsParser.h"

using namespace std;

OptionsParser::OptionsParser(int argc, char* argv[])
{
	if(argc > 2 && argc <= 5)
	{
		for(int i = 1; i < argc; ++i)
		{
			string param(argv[i]);
			if(param == "-d")
				//fnDevicesIni = ++i < argc ? argv[i] : "";
					fnDevicesIni = argv[++i];
			if(param == "-p")
				//fnPortsIni = ++i < argc ? argv[i] : "";
					fnPortsIni = argv[++i];
		}

	}
	else
	{
		throw invalid_argument("Too many or too few arguments supplied");
	}
}

string OptionsParser::getDevicesIni() const
{
	return fnDevicesIni;
}

string OptionsParser::getPortsIni() const
{
	return fnPortsIni;
}