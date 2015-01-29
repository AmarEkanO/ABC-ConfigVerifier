#include <iostream>
#include <iomanip>
#include "OptionsParser.h"
using namespace std;

void printUsage();

int main(int argc, char* argv[])
{
	cout << "ABC Configuration Verifier starting...." << endl;

	// Parse and verify commandline options
	try
	{
		OptionsParser parser(argc, argv);
		cout << "Devices.ini: " <<parser.getDevicesIni() <<endl;
		cout << "\nPorts.ini: " << parser.getPortsIni() << endl;
	}
	catch(invalid_argument const &ex)
	{
		cout << "Error: " << ex.what();
		//Print usage and exit
		printUsage();
		exit(1);
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