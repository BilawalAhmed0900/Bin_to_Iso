#ifndef CUECLASS_HPP_XX1
#define CUECLASS_HPP_XX1

#include <fstream>	// for ifstream, ofstream
#include <string>	// for string, getline

namespace BinNamespace
{
	class Bin
	{
		std::string filename;

	public:
		Bin(const std::string Filename): filename(Filename) { } 
		~Bin() { }

		void to_iso(const std::string iso_name) const
		{
			std::ifstream bin_file(this->filename, std::ios_base::binary);
			if (bin_file.is_open() == false)
			{
				throw FileExceptions("file not found", this->filename.c_str());
			}

			std::ofstream iso_file(iso_name, std::ios_base::binary);
			if (iso_file.is_open() == false)
			{
				throw FileExceptions("file can\'t be created", iso_name.c_str());
			}

			do
			{
				Sector sector;
				bin_file.read(reinterpret_cast<char *>(&sector), sizeof(Sector));
				if (sector.sync_pattern.verify() == false)
				{
					throw NotARightBinFile();
				}

				char *ptr;
				size_t size;
				if (sector.mode == 1)
				{
					ptr = reinterpret_cast<char *>(&sector.mode1_data[0]);
					size = sizeof(Sector::mode1_data);
					
				}
				else if (sector.mode == 2)
				{
					ptr = reinterpret_cast<char *>(&sector.mode2_data[0]);
					size = sizeof(Sector::mode2_data);				
				}
				else
				{
					throw NotARightBinFile();
				}

				iso_file.write(ptr, size);
			}
			while(bin_file.gcount() > 0);

			iso_file.close();
			bin_file.close();
		}
	};
};

#endif // CUECLASS_HPP_XX1