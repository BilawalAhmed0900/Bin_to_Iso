#ifndef STRUCTS_HPP_XX1
#define STRUCTS_HPP_XX1

/*
	A CD-ROM stores data in clusters each of 2,352 bytes
	It has two modes(excluding XA extension) depending on whether error-correction is added or not

	Read more here: https://en.wikipedia.org/wiki/CD-ROM#CD-ROM_format

	Data is stored in ISO 9660(known as ISO files), its extension or UDF format

	Bin file is composed of those sectors
	By removing those headers and storing only data, we will have ISO or UDF file
*/

#include <cstdint> // Fixed width integers
namespace BinNamespace
{
	#pragma pack(push, 1)
	struct Sync_pattern
	{
		uint32_t a, b, c;

		inline bool verify() const noexcept
		{
			return (a == 0xFFFFFF00) && (b == 0xFFFFFFFF) && (c == 0x00FFFFFF);
		}
	};

	struct Address
	{
		uint8_t a, b, c;

		operator int32_t() const
		{
			return a | (b << 8) | (c << 16);
		}

		operator int64_t() const
		{
			return a | (b << 8) | (c << 16);
		}
	};

	struct Sector
	{
		Sync_pattern sync_pattern; // 00 FF FF FF FF FF FF FF FF FF FF 00
		Address address;
		uint8_t mode; 

		union
		{
			// mode == 1
			struct
			{
				int8_t mode1_data[2048];
				uint32_t mode1_crc32; // of mode1_data
				int64_t mode1_reserved; // 00000000 00000000
				int8_t mode1_error_correction[276];
			};

			// mode == 2
			struct
			{
				int8_t mode2_data[2336];
			};
		};
	};
	#pragma pack(pop)
};

#endif // STRUCTS_HPP_XX1