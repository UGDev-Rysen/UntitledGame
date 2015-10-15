#pragma once

#include <string>
#include <FreeImage.h>
#include <utils/Log.h>
#include <utils/unicitydef.h>
#include <utils/fileutils.h>


namespace u_engine {

	static BYTE* load_image(const UE_char* filename, UE_uint* width, UE_uint* height, UE_uint* bits) {

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		
		UNICITY_ASSERT(dib, "Could not load image '", filename, "'!");

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bits = FreeImage_GetBPP(dib);

		UE_int size = *width * *height * (*bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		return result;

	}

	//Broken as of dev0.0.7 :'c

	static UE_void save_image(const UE_char* filename, UE_uint* width, UE_uint* height, UE_uint* bits, const UE_char* savename) {

		BYTE* imgdata = load_image(filename, width, height, bits);

		std::ofstream file(savename, std::ios::out | std::ios::beg);
		if (file.is_open())
		{
			file << *imgdata;
			file.close();
			UNICITY_INFO("File: '", filename, "' was saved in: '", savename, "'.");
		}
		else UNICITY_ERROR("Unable to open file: ", savename);
	}


}