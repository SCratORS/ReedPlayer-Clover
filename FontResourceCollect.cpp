#include "FontResourceCollect.h"

Font::Font(std::string path) {
	std::ifstream fontFile(path, std::ios::binary);
	if (!fontFile) return;
	std::cout << "***INFO(FONT): Load Font: " << path << std::endl;
	fontFile.seekg(0, fontFile.end);
	size_t size = (size_t)fontFile.tellg();
	fontFile.seekg(0, fontFile.beg);

	fontFile.read((char*)&header, sizeof(Header));

	if (!header.sig01 == 1) return;
	
	fontFile.read((char*)&bmfHeader, sizeof(BMFHeader));
	header.header_length -= sizeof(BMFHeader);

	if (!(bmfHeader.sig[0] == 'B' && bmfHeader.sig[1] == 'M' && bmfHeader.sig[2] == 'F')) return;
	if (!(bmfHeader.version == 3)) return;
	while (header.header_length > 0) {
		fontFile.read((char*)&packed_id, sizeof(packed_id));
		fontFile.read((char*)&packed_lenght, sizeof(packed_lenght));
		header.header_length -= sizeof(packed_id);
		header.header_length -= sizeof(packed_lenght);
		switch (packed_id) {
			case 1: fontFile.read((char*)&bmfInfo, packed_lenght);
					header.header_length -= packed_lenght;
					break;
			case 2: fontFile.read((char*)&bmfCommon, packed_lenght);
					header.header_length -= packed_lenght;
					break;
			case 3: fontFile.read((char*)&bmfPages, packed_lenght);
					header.header_length -= packed_lenght;
					break;
			case 4: while (packed_lenght > 0) {
						BMFChar bmfCharsTemp;
						fontFile.read((char*)&bmfCharsTemp, sizeof(BMFChar));
						bmfChars[bmfCharsTemp.id] = bmfCharsTemp;
						packed_lenght -= sizeof(BMFChar);
						header.header_length -= sizeof(BMFChar);
					}
					break;
		}
	}
	fontFile.read((char*)&texture, sizeof(header.texture_length));
	fontFile.close();
}

std::vector<unsigned char> Font::getTextureText(std::string text){
	std::vector<unsigned char> temp = {};
	return temp;
}

Font* FontResourceCollect::getFont(std::string id)
{
	return data.find(id)->second;
}

bool FontResourceCollect::LoadResources(std::string path, std::string id)
{
	Font * fnt = new Font(path);
	data.insert(make_pair(id, fnt));
	return true;
}
