#ifndef EXCEPTION_HPP_XX1
#define EXCEPTION_HPP_XX1

#include <stdexcept> // std::runtime_error

#include <cstdio>    // sprint
#include <cstdint>   // uint32_t 
#include <cstring>   // strlen

namespace BinNamespace
{
    class FileExceptions: public std::runtime_error
	{
	private:
		const char *filename;
		char *message;
		
	public:
		FileExceptions(const char *message_of_exception, const char *filename_not_found)
			: std::runtime_error(message_of_exception), filename(filename_not_found), message(NULL)
		{
			/* runtime_error::what() + " \"" + filename + "\""\0 */
			uint32_t size_of_string = strlen(runtime_error::what()) + 2 + strlen(filename) + 1 + 1;
			message = new (std::nothrow) char[size_of_string];
			if (message != NULL)
			{
				sprintf(message, "%s \"%s\"", runtime_error::what(), filename);
			}
		}

		const char *get_filename() const
		{
			return this->filename;
		}


		virtual const char *what() const throw()
		{
			if (message != NULL)
				return message;

			return "";
		}

		~FileExceptions()
		{
			if (message != NULL)
			{
				delete[] message;
			}
		}
	};

	class NotARightBinFile: public std::runtime_error
	{
	public:
		NotARightBinFile()
			: runtime_error("Bin file doesn\'t is wrong or corrupted") { } 
	};
};

#endif // EXCEPTION_HPP_XX1