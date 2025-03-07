#include "imagetool.h"
#include <iostream>
#include <filesystem>

struct LibraryLoader
{
	LibraryLoader() 
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	~LibraryLoader() 
	{
		CoUninitialize();
	}

	LibraryLoader(const LibraryLoader&)            = delete;
	LibraryLoader& operator=(const LibraryLoader&) = delete;
};

int wmain(const int argc, const wchar_t* argv[])
{
	if (argc != 3) {
		std::cerr << "Not enough arguments \n\nUsage: ddsloader input.dds output.png\n";
		return 1;
	}

	LibraryLoader loader;

	// File name of the DDS texture
	const wchar_t* filename = argv[1];

	// Variables to hold texture metadata and the image data
	DirectX::TexMetadata metadata = {};
	DirectX::ScratchImage image;

	// Load the DDS file
	HRESULT hr = LoadFromDDSFile(filename, DirectX::DDS_FLAGS_NONE, &metadata, image);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to load DDS file: " << filename << std::endl;
		return 2;
	}

	// Print out some metadata about the loaded texture
	std::wcout << L"DDS file loaded: " << filename << std::endl;
	std::wcout << L"Dimensions: "	   << metadata.width << L" x " << metadata.height << std::endl;
	std::wcout << L"Format: "	       << metadata.format << std::endl;
	std::wcout << L"MipLevels: "	   << metadata.mipLevels << std::endl;

	// Access the first image from the loaded texture (for example, level 0, array slice 0)
	const DirectX::Image* img = image.GetImage(0, 0, 0);
	if (!img) {
		std::wcerr << L"Failed to retrieve image data from the DDS file." << std::endl;
		return 3;
	}

	std::wcout << L"Row pitch: " << img->rowPitch << std::endl;

	const std::filesystem::path path(argv[2]);
	bool result;
	if (path.extension() == L".png") {
		result = saveAsPng(&image, argv[2]);
	} else {
		result = saveAsRaw(&image, argv[2]);
	}

	return result == true ? 0 : 4;
}
