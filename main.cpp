#include <iostream>

#include "exceptions.hpp"
#include "structs.hpp"
#include "binclass.hpp"

#define APP_NAME "Bin_to_ISO"
#define AUTHOR_NAME "Mian Bilawal aka Dragneel1234"

#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0

#define NUMBER_OF_ARGUMENTS 3

std::ostream &HELP(std::ostream &stream)
{
	using namespace std;
	stream << APP_NAME << " " 
		<< "v" << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << "." << APP_VERSION_PATCH 
		<< " by " << AUTHOR_NAME << endl;
	stream << "Usage: " << APP_NAME << " BinFile IsoFile" << endl;

	return stream;
}

int main(int argc, char const *argv[])
{
	using namespace std;

	if (argc != NUMBER_OF_ARGUMENTS)
	{
		if (argc < NUMBER_OF_ARGUMENTS)
		{
			cout << "Not enough parameters" << endl;
		}
		else if (argc > NUMBER_OF_ARGUMENTS)
		{
			cout << "Too many parameters" << endl;
		}	
        
        cout << endl;
        cout << HELP;
			
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