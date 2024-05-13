#pragma once
#include <memory>
#include <cstddef>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

struct TextureResource
{
	std::shared_ptr<unsigned char> ptr;
	size_t length;
};

class TextureResourceCollect
{
public:
	TextureResourceCollect() {};
	~TextureResourceCollect() {};

	bool LoadResources(std::string path, std::string id);
	TextureResource getData(std::string id);

private:
	std::map <std::string, TextureResource> data;
};