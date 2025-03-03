#pragma once

#include <DirectXTex.h>

bool saveAsRaw(const DirectX::ScratchImage* image, const wchar_t* filename);
bool saveAsPng(const DirectX::ScratchImage* image, const wchar_t* filename);
