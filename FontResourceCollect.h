#pragma once
#include <memory>
#include <cstddef>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#pragma pack(push)
#pragma pack(1)
struct Header{
	uint8_t sig01;
	uint16_t header_length;
	uint16_t texture_length;
};
struct BMFHeader{
	char sig[3];
	uint8_t version;
};
struct BMFInfo {
	int16_t fontSize; 
	uint8_t bitField;
	uint8_t charSet;
	uint16_t stretchH;
	uint8_t aa;
	uint8_t paddingUp;
	uint8_t paddingRight;
	uint8_t paddingDown;
	uint8_t paddingLeft;
	uint8_t spacingHoriz;
	uint8_t spacingVert;
	uint8_t outline;
	char fontName[64];
};
struct BMFCommon {
	uint16_t lineHeight; // Размер букв
	uint16_t base;	// Размер самой большой буквы (для вертикального переноса строки)
	uint16_t scaleW;
	uint16_t scaleH;
	uint16_t pages;
	uint8_t bitField;
	uint8_t alphaChnl;
	uint8_t redChnl;
	uint8_t greenChnl;
	uint8_t blueChnl;
};
struct BMFPages {
	char pageNames[64];
};
struct BMFChar {
	uint32_t id; // Код символа 
	uint16_t x;  // х текстурная координата
	uint16_t y;  // у текструная координата
	uint16_t width;  // ширина буквы
	uint16_t height; // высота
	int16_t xoffset; // сдвиг по х
	int16_t yoffset; // сдвиг по у
	int16_t xadvance;
	uint8_t  page;
	uint8_t  chnl;
};

#pragma pack(pop)

class Font {
	Header header;
	BMFHeader bmfHeader;
	BMFInfo bmfInfo;
	BMFCommon bmfCommon;
	BMFPages bmfPages;
	std::map<uint32_t, BMFChar> bmfChars;
	std::vector<unsigned char> texture;


	unsigned char packed_id;
	unsigned int  packed_lenght;

public:
	Font(std::string path);
	std::vector<unsigned char> getTextureText(std::string text);
};

class FontResourceCollect
{
public:
	FontResourceCollect() {};
	~FontResourceCollect() {};

	bool LoadResources(std::string path, std::string id);
	Font* getFont(std::string id);

private:
	std::map <std::string, Font*> data;
};