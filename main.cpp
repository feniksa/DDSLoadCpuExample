#include <iostream>
#include <DirectXTex.h>

using namespace DirectX;

int main()
{
	// File name of the DDS texture
	const wchar_t* filename = L"HorizonForbiddenWest.exe_SRV_frame5016_r0_4_5.dds";

	// Variables to hold texture metadata and the image data
	TexMetadata metadata = {};
	ScratchImage image;

	// Load the DDS file
	HRESULT hr = LoadFromDDSFile(filename, DDS_FLAGS_NONE, &metadata, image);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to load DDS file: " << filename << std::endl;
		return 1;
	}

	// Print out some metadata about the loaded texture
	std::wcout << L"DDS file loaded: " << filename << std::endl;
	std::wcout << L"Dimensions: " << metadata.width << L" x " << metadata.height << std::endl;
	std::wcout << L"Format: " << metadata.format << std::endl;
	std::wcout << L"MipLevels: " << metadata.mipLevels << std::endl;

	// Access the first image from the loaded texture (for example, level 0, array slice 0)
	const Image* img = image.GetImage(0, 0, 0);
	if (img)
	{
		// For example, print out the row pitch
		std::wcout << L"Row pitch: " << img->rowPitch << std::endl;

		// You can now access the pixel data via img->pixels.
		// For instance, processing the first few bytes:
		const uint8_t* pixelData = img->pixels;
		std::wcout << L"First pixel value (first byte): " << static_cast<unsigned int>(pixelData[0]) << std::endl;
	}
	else
	{
		std::wcerr << L"Failed to retrieve image data from the DDS file." << std::endl;
	}

	return 0;
}