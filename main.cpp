#include <iostream>
#include <DirectXTex.h>
#include <fstream>

using namespace DirectX;
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	if (argc != 3) {
		std::cerr << "not enough args\n";
		return 2;
	}

	// File name of the DDS texture
	const wchar_t* filename = argv[1];
	std::ofstream outFile(argv[2], std::ios::binary);
	if (!outFile.is_open()) {
		std::wcerr << L"can't open file " << argv[2] << std::endl;
		return 3;
	}

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
	if (!img) {
		std::wcerr << L"Failed to retrieve image data from the DDS file." << std::endl;
		return 1;
	}

	std::wcout << L"Row pitch: " << img->rowPitch << std::endl;

	const uint8_t* pixelData = img->pixels;
	//std::wcout << L"First pixel value (first byte): " << static_cast<unsigned int>(pixelData[0]) << std::endl;

	outFile.write(reinterpret_cast<const char*>(&pixelData[0]), img->slicePitch);

	outFile.close();

	return 0;
}