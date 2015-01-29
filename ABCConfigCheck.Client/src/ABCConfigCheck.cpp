#include <iostream>
#include <iomanip>
#include "OptionsParser.h"
#include "ConfigHandler.h"
#include "DeviceVerifier.h"
#include "PortVerifier.h"
#include "SemanticVerifier.h"

using namespace std;

void printUsage();

int main(int argc, char* argv[])
{
	cout << "ABC Configuration Verifier starting...." << endl;
	bool validConfig = true;
	// Parse and verify commandline options
	try
	{
		OptionsParser parser(argc, argv);
		LETable leTable;

		//Create a handler for devices.ini
		if(!parser.getDevicesIni().empty())
		{
			cout << "Devices.ini: " <<parser.getDevicesIni() <<endl;
			ConfigHandler devicesConfig(parser.getDevicesIni());

			DeviceVerifier verifier(devicesConfig);
			if(verifier.isValid())
			{
				cout << "File: " << parser.getDevicesIni() << " is valid" << endl;
				leTable = verifier.getLeTable();
			}
			else
			{
				vector<string> invalidEntries = verifier.getInvalidEntries();
				for(vector<string>::iterator it = invalidEntries.begin(); it != invalidEntries.end(); it++)
				{
					cout << *it << endl;
				}
				cout << "File: " << parser.getDevicesIni() << " is invalid" << endl;
				validConfig = false;
			}
		}

		//Create a handler for ports.ini
		if(!parser.getPortsIni().empty())
		{
			cout << "Ports.ini: " << parser.getPortsIni() << endl;
			ConfigHandler portsConfig(parser.getPortsIni());

			PortVerifier verifier(portsConfig);
			if(verifier.isValid())
			{
				cout << "File: " << parser.getPortsIni() << " is valid" << endl;
			}
			else
			{
				vector<string> invalidEntries = verifier.getInvalidEntries();
				for(vector<string>::iterator it = invalidEntries.begin(); it != invalidEntries.end(); it++)
				{
					cout << *it << endl;
				}
				cout << "File: " << parser.getPortsIni() << " is invalid" << endl;
				validConfig = false;
			}
		}

		if(!validConfig)
			return EXIT_FAILURE;

		//If we reach here then then we have either a LETable or a PortTable
		SemanticVerifier verifier(leTable);

		if(verifier.isValid())
		{
			cout << "ABC configuration is valid" << endl;
		}
		else
		{
			vector<string> invalidEntries = verifier.getInvalidEntries();
			for(vector<string>::iterator it = invalidEntries.begin(); it != invalidEntries.end(); it++)
			{
				cout << *it << endl;
			}
			cout << "ABC configuration is invalid" << endl;
			return EXIT_FAILURE;
		}
		
		//If there were any entries in the verifier's buffer these are probably warnings display them
		vector<string> invalidEntries = verifier.getInvalidEntries();
		if(invalidEntries.size() > 0)
		{
			cout << "\n\t\t**** WARNINGS ****" << endl;
			for(vector<string>::iterator it = invalidEntries.begin(); it != invalidEntries.end(); it++)
			{
				cout << *it << endl;
			}
		}
		cout << "\t\t*****************\n\n" << endl;

	}
	catch(invalid_argument const &ex)
	{
		cout << "Error: " << ex.what();
		//Print usage and exit
		printUsage();
		exit(1);
	}
	catch(exception const &ex)
	{
		cout << "Error: " << ex.what();
	}
}

void printUsage()
{
	cout << "Options:"<<endl << 
		setw(20) << left << "-p <file path>" << setw(20) << right << "Path to ports.ini file" << endl <<
		setw(20) << left << "-d <file path>" << setw(20) << right << "Path to devices.ini file" << endl <<
		endl << "Examples: " << endl << 
		setw(20) << "ABCConfigCheck.exe -d \"C:\\Program Files\\Diebold\\ABC\\devices.ini\"" << endl <<
		setw(20) << "ABCConfigCheck.exe -p \"C:\\Program Files\\Diebold\\ABC\\ports.ini\"" << endl <<
		setw(40) << "ABCConfigCheck.exe -d \"devices.ini\" -p \"ports.ini\"" << endl;
}