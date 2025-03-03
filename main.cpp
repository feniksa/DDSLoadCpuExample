#include <windows.h>
#include <wincodec.h>   // For GUID_ContainerFormatPng
#include <iostream>
#include <DirectXTex.h>
#include <fstream>
#include <filesystem>

using namespace DirectX;
using namespace std;

bool saveAsPng(const ScratchImage* image, const wchar_t* filename)
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    // Convert to a format compatible with WIC
    ScratchImage converted;
    HRESULT hr;
    hr = Convert(image->GetImages(), image->GetImageCount(), image->GetMetadata(),
                DXGI_FORMAT_R8G8B8A8_UNORM, TEX_FILTER_DEFAULT, 0.0f, converted);
    if (FAILED(hr))
    {
        wprintf(L"Failed to convert image. HRESULT: 0x%X\n", hr);
		CoUninitialize();
        return false;
    }

    // Save as PNG
    hr = SaveToWICFile(*converted.GetImage(0, 0, 0), WIC_FLAGS_NONE,
                        GUID_ContainerFormatPng, filename);
    if (FAILED(hr))
    {
        wprintf(L"Failed to save PNG file. HRESULT: 0x%X\n", hr);
		CoUninitialize();
        return false;
    }

	CoUninitialize();
	return true;
}

bool saveAsRaw(const ScratchImage* image, const wchar_t* filename)
{
	std::ofstream outFile(filename, std::ios::binary);

	const Image* img = image->GetImage(0, 0, 0);
	if (!img) {
		std::wcerr << L"Failed to retrieve image data from the DDS file." << std::endl;
		return false;
	}

    if (!outFile.is_open()) {
        std::wcerr << L"can't open file " << filename << "\n";
        return false;
    }

    const uint8_t* pixelData = img->pixels;
    //std::wcout << L"First pixel value (first byte): " << static_cast<unsigned int>(pixelData[0]) << std::endl;

    outFile.write(reinterpret_cast<const char*>(&pixelData[0]), img->slicePitch);

    outFile.close();

	return true;
}

int wmain(int argc, wchar_t* argv[])
{
	if (argc != 3) {
		std::cerr << "not enough args\n";
		return 2;
	}
	// File name of the DDS texture
	const wchar_t* filename = argv[1];

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
	std::wcout << L"Dimensions: "      << metadata.width << L" x " << metadata.height << std::endl;
	std::wcout << L"Format: "          << metadata.format << std::endl;
	std::wcout << L"MipLevels: "       << metadata.mipLevels << std::endl;

	// Access the first image from the loaded texture (for example, level 0, array slice 0)
	const Image* img = image.GetImage(0, 0, 0);
	if (!img) {
		std::wcerr << L"Failed to retrieve image data from the DDS file." << std::endl;
		return 1;
	}

	std::wcout << L"Row pitch: " << img->rowPitch << std::endl;

	std::filesystem::path path(argv[2]);
	if (path.extension() == L".png") {
		return saveAsPng(&image, argv[2]) ? 0 : 5;
	} else {
		return saveAsRaw(&image, argv[2]) ? 0 : 5;
	}

	return 0;
}