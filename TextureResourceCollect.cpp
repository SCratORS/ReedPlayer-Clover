#include "TextureResourceCollect.h"

auto array_deleter = [](unsigned char* p) { delete[] p; };
auto nop_deleter = [](unsigned char* p) { };

TextureResource TextureResourceCollect::getData(std::string id)
{
	return data.find(id)->second;
}

bool TextureResourceCollect::LoadResources(std::string path, std::string id)
{
	std::ifstream textureFile(path, std::ios::binary);
	if (!textureFile) return false;

	textureFile.seekg(0, textureFile.end);
	size_t size = (size_t)textureFile.tellg();
	textureFile.seekg(0, textureFile.beg);
	std::shared_ptr<unsigned char> buffer(new unsigned char[size], array_deleter);
	textureFile.read((char*)buffer.get(), size);
	textureFile.close();
	TextureResource mData = {buffer, size};
	data.insert(make_pair(id, mData));
	
	return true;
}
