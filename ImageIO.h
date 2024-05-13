#pragma once

#include <vector>
#include <FreeImage.h>
#include "platform.h"

class ImageIO
{
public:
	static std::vector<unsigned char> loadFromMemoryRGBA32(const unsigned char * data, const size_t size, Rect rect, size_t & width, size_t & height);
	static void flipPixelsVert(unsigned char* imagePx, const size_t& width, const size_t& height);
};