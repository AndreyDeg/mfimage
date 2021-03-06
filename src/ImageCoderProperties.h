#pragma once
#include <cstdint>
#include <array>
#include <vector>

typedef enum TIFF_Compression {
	/** No compression */
	NONE = 1,
	/** CCIT modified Huffmann RLE -- MIGHT NOT WORK WITH ALL IMAGE TYPES */
	CCIT_RLE = 2,
	/** CCIT Fax Group 3 (T.4) -- MIGHT NOT WORK WITH ALL IMAGE TYPES */
	CCIT_FAX_G3 = 3,
	/** CCIT Fax Group 4 (T.6) -- MIGHT NOT WORK WITH ALL IMAGE TYPES */
	CCIT_FAX_G4 = 4,
	/** LZW compression */
	LZW = 5,
	/** JPEG DCT compression -- LOSSY !!! */
	JPEG = 7,
	/** Adobe Deflate */
	ADOBE_DEFLATE = 8,
	/** Deflate */
	DEFLATE=32946,
	/** CCIT modified Huffmann RLE with word alignment -- MIGHT NOT WORK WITH ALL IMAGE TYPES*/
	CCIT_RLE_W = 32771,
	/** Packbits (Macintosh RLE) */
	PACKBITS=32773,
	/** Thunderscan RLE */
	THUNDERSCAN_RLE=32809,
	/** LZMA2 */
	LZMA=34925
} TIFF_Compression;

typedef enum BMP_RenderingIntent {
	/** Saturation (LCS_GM_BUSINESS) */
	SATURATION = 1,
	/** Relative Colorimetric (LCS_GM_GRAPHICS) */
	REL_COLORIMETERIC = 2,
	/** Perceptual (LCS_GM_IMAGES) */
	PERCEPTUAL = 4,
	/** Absolute Colorimetric (LCS_GM_ABS_COLORIMETRIC) */
	ABS_COLORIMETRIC = 8
} BMP_RenderingIntent;



typedef struct ImageCoderProperties {
public:
	bool     embeddedIccProfile    = false;  // R - true if file contained embedded ICC profile
	bool     colorSpaceIsSRGB      = false;	 // RW - true if color space is/shall be marked as SRGB 
	bool     hasColorDescription   = false;  // R - true if file contained gamma, whitepoint or chroma description
	double   gamma                 = 0.0;    // RW - file gamma
	std::array<double,2>   whitepoint;    // R - whitepoint
	std::vector<double>    chromaticPrimaries;    // R - chromatic primaries - typically 6
	std::array<double,2>   offsetInches;    // R - position offset in inches
	std::array<int32_t,2>  offsetPixels;    // R - position offset in píxels
	
	// flags on how to read/write the file
	bool     applyHalftoneHintsOnRead = true;       // W - obey halft tone hints during read (TIFF)
	bool     writeSeparatedPlanes     = false;      // W - Write file in planar order ? Tiff only
	uint32_t compression              = TIFF_Compression::NONE;          // W - compression type, encoder specific (currently only tiff)
	double   quality                  = 0.9;        // W - quality for lossy compressions (Jpeg, Jpeg2000)
	bool     embedTimestamp           = true;       // W - write metainfo on when the file was written (TIFF, ?)
	bool     embedOtherInfo           = true;       // W - write software version and such to file (TIFF, ?)
	uint32_t defaultRenderingIntent   = BMP_RenderingIntent::REL_COLORIMETERIC;	// W - default rendering intent (currently only BMP)
	bool     createColorProfileForImpliciteColorSpace = false; // W - if things like chromatic primaries are given, automatically create a color profile // NOT IMPLEMENTED
	bool     createGrayProfileForImpliciteColorSpace  = false; // W - same as above for gray images // NOT IMPLEMENTED
	bool     createLabProfile  = true; // W - same as above for L*a*b* images (littlecms v4 profile with given white point)
} ImageCoderProperties;
