#include "imagetool.h"
#include <windows.h>
#include <wincodec.h>	// For GUID_ContainerFormatPng
#include <iostream>
#include <fstream>

bool saveAsRaw(const DirectX::ScratchImage* image, const wchar_t* filename)
{
	std::ofstream outFile(filename, std::ios::binary);
	
	const DirectX::Image* img = image->GetImage(0, 0, 0);
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

bool saveAsPng(const DirectX::ScratchImage* image, const wchar_t* filename)
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// Convert to a format compatible with WIC
	DirectX::ScratchImage converted;
	HRESULT hr;
	hr = Convert(image->GetImages(), image->GetImageCount(), image->GetMetadata(),
	DXGI_FORMAT_R8G8B8A8_UNORM, DirectX::TEX_FILTER_DEFAULT, 0.0f, converted);
	if (FAILED(hr))
	{
		wprintf(L"Failed to convert image. HRESULT: 0x%X\n", hr);
		CoUninitialize();
		return false;
	}
	
	// Save as PNG
	hr = SaveToWICFile(*converted.GetImage(0, 0, 0), DirectX::WIC_FLAGS_NONE,
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



