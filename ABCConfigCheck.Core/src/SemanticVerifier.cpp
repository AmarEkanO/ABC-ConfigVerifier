#include "SemanticVerifier.h"
#include "VirtualLe.h"
#include "VirtualLETable.h"

SemanticVerifier::SemanticVerifier(LETable& table)
	: table(table)
{
}

SemanticVerifier::~SemanticVerifier()
{
}

vector<string> SemanticVerifier::getInvalidEntries()
{
	return invalidEntries.getEntries();
}

bool SemanticVerifier::isValid()
{
	bool validConfig = true;

	//Get a list of all LE's
	vector<LE> list = table.getLeList();

	//Create a table to store virtual le's and validate them
	VirtualLETable virtTable;

    //Perform individual LE validation
	for(vector<LE>::iterator le = list.begin(); le != list.end(); ++le)
	{
		LEInfo leInfo(table.getLineNumber(*le), *le);
		try
		{
			VirtualLE virtualLE;
			//Verify for virtual LE's
			if(virtualLE.check(*le))
			{
				//Process as virtual LE
				if(virtualLE.validate(leInfo))
				{
					/*
                    * TODO
                    * If the LE was valid push it to the virt Le table
                    * validate it after table iteration finishes
                    */
					virtTable.addLE(leInfo);
				}
				else
				{
                    validConfig = false;
					/*
					* invalid entries from protocol validator should
					* be appended to the semantic verifier buffer
					*/
					invalidEntries.addMessages(virtualLE.getInvalidEntries());
				}
			}
			else
			{
				/*
				* Protocol not supported... yet
				* Log LE's to unsupported buffer
				*/
				invalidEntries.addMessage(table.getLineNumber(*le), le->getLeName(), "Cannot verify LE, unsupported protocol");
			}
		}
		catch(NonExistentPropertyException const &ex)
		{
			// LE does not have a Port property
			validConfig = false;
			invalidEntries.addMessage(table.getLineNumber(*le), le->getLeName(), string(ex.what()));
		}
	}

    /*
    * TODO
	* Now perform context validation
    * Currently only available for virtual LE's
    */
	if(virtTable.validateTable())
	{
	}

	return validConfig;
}