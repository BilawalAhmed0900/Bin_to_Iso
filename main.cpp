#include <iostream>

#include "exceptions.hpp"
#include "structs.hpp"
#include "binclass.hpp"

#define APP_NAME "Bin_to_ISO"
#define AUTHOR_NAME "Mian Bilawal aka Dragneel1234"

#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0

#define Number_of_arguments 3

int main(int argc, char const *argv[])
{
	using namespace std;

	if (argc != Number_of_arguments)
	{
		if (argc < Number_of_arguments)
		{
			cout << "Not enough parameters" << endl;
		}
		else if (argc > Number_of_arguments)
		{
			cout << "Too many parameters" << endl;
		}	
        
        cout << endl;

        cout << APP_NAME << " " 
			<< "v" << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << "." << APP_VERSION_PATCH 
			<< " by " << AUTHOR_NAME << endl;
		cout << "Usage: " << APP_NAME << " BinFile IsoFile" << endl;
			
		return EXIT_FAILURE;
	}

	try
	{
		BinNamespace::Bin bin(argv[1]);
		bin.to_iso(argv[2]);
		return EXIT_SUCCESS;
	}
	catch(const BinNamespace::FileExceptions &e)
	{
		cout << "Exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	catch(const BinNamespace::NotARightBinFile &e)
	{
		cout << "Exception: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		cout << "Exception: Unknown exception" << endl;
		return EXIT_FAILURE;
	}
}