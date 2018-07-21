# Bin_to_Iso
Convert Disk Image file(.bin) to Iso

# Bin File
It is Raw disk image. A disk is composed of sectors 2352 bytes each. By removing those headers and storing only data, we will have ISO or UDF file which is standard format of CD or DvD. Read more [here](https://en.wikipedia.org/wiki/CD-ROM#CD-ROM_format)

# Compilation
`g++ --static -Wall -Werror -Ofast -o Bin_to_Iso main.cpp`

# Sectors Specification
Sectors are made up in two formats depending upon whether error-correction is used or not(excluding XA extension).

## Header

| Name | Size | Possible Value |
|------|------|-----------------|
| Sync pattern | 12 bytes | 00 FF FF FF FF FF FF FF FF FF FF 00 |
| Address | 3 bytes | |
| Mode | 1 byte | 1 or 2 |

### Mode 1

| Name | Size |
|------|------|
| Data | 2048 bytes |
| Crc 32 | 4 bytes |
| Reserved | 8 bytes (zero-ed) |
| Error correction | 276 bytes |

### Mode 2

| Name | Size |
|------|------|
| Data | 2336 bytes |
