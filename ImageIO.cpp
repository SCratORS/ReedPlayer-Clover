#include "ImageIO.h"
#include <memory.h>
#include <iostream>
std::vector<unsigned char> ImageIO::loadFromMemoryRGBA32(const unsigned char * data, const size_t size, Rect rect, size_t & width, size_t & height)
{
	std::vector<unsigned char> rawData;
	width = rect.width;
	height = rect.height;
	FIMEMORY * fiMemory = FreeImage_OpenMemory((BYTE *)data, size);
	if (fiMemory != nullptr) {
		//detect the filetype from data
		FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromMemory(fiMemory);
		if (format != FIF_UNKNOWN && FreeImage_FIFSupportsReading(format))
		{
			//file type is supported. load image
			FIBITMAP * fiBitmap = FreeImage_LoadFromMemory(format, fiMemory);
			if (fiBitmap != nullptr)
			{
				//loaded. convert to 32bit if necessary
				FIBITMAP * fiConverted = nullptr;
				if (FreeImage_GetBPP(fiBitmap) != 32)
				{
					FIBITMAP * fiConverted = FreeImage_ConvertTo32Bits(fiBitmap);
					if (fiConverted != nullptr)
					{
						//free original bitmap data
						FreeImage_Unload(fiBitmap);
						fiBitmap = fiConverted;
					}
				}
				if (fiBitmap != nullptr)
				{
					size_t image_width = FreeImage_GetWidth(fiBitmap);
					size_t image_height = FreeImage_GetHeight(fiBitmap);
					if (!width) width = image_width;
					if (!height) height = image_height;
					unsigned int pitch = FreeImage_GetPitch(fiBitmap);
					//loop through scanlines and add all pixel data to the return vector
					//this is necessary, because width*height*bpp might not be == pitch
					unsigned char * tempData = new unsigned char[width * height * 4];
					unsigned topLine = image_height - rect.top - height;
					for (size_t i = topLine; i < topLine+height; i++)
					{
						const BYTE * scanLine = FreeImage_GetScanLine(fiBitmap, i);
						memcpy(tempData + ((i-topLine) * width * 4), scanLine+(rect.left*4), width * 4);
					}
					//convert from BGRA to RGBA
					for(size_t i = 0; i < width*height; i++)
					{
						RGBQUAD bgra = ((RGBQUAD *)tempData)[i];
						RGBQUAD rgba;
						rgba.rgbBlue = bgra.rgbRed;
						rgba.rgbGreen = bgra.rgbGreen;
						rgba.rgbRed = bgra.rgbBlue;
						rgba.rgbReserved = bgra.rgbReserved;
						((RGBQUAD *)tempData)[i] = rgba;
					}
					rawData = std::vector<unsigned char>(tempData, tempData + width * height * 4);
					//free bitmap data
					FreeImage_Unload(fiBitmap);
					delete[] tempData;
				}
			}
		}
		//free FIMEMORY again
		FreeImage_CloseMemory(fiMemory);
	}
	return rawData;
}

void ImageIO::flipPixelsVert(unsigned char* imagePx, const size_t& width, const size_t& height)
{
	unsigned int temp;
	unsigned int* arr = (unsigned int*)imagePx;
	for(size_t y = 0; y < height / 2; y++)
	{
		for(size_t x = 0; x < width; x++)
		{
			temp = arr[x + (y * width)];
			arr[x + (y * width)] = arr[x + (height * width) - ((y + 1) * width)];
			arr[x + (height * width) - ((y + 1) * width)] = temp;
		}
	}
}
