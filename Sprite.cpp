#include "Sprite.h"

#include "SpriteSheetCollect.h"
#include "TextureResourceCollect.h"

extern SpriteSheetCollect * spriteSheetCollect;
extern TextureResourceCollect * textureResourceCollect;

Sprite::Sprite(std::string id):texture_id(0)
{
	const Json::Value& param = spriteSheetCollect->getParam(id);
	std::string IdTextureData = spriteSheetCollect->getTextureId(id);
	TextureResource data = textureResourceCollect->getData(IdTextureData);

	unsigned left = param["textureFrame"][0].asInt();
	unsigned top = param["textureFrame"][1].asInt();
	unsigned width = param["textureFrame"][2].asInt();
	unsigned heigth = param["textureFrame"][3].asInt();

	mTextureRect = {left, top, width, heigth};
	mTextureSize = Eigen::Vector2i(param["sourceSize"][0].asInt(), param["sourceSize"][1].asInt());
	mTexturePivot = Eigen::Vector2i(param["pivot"][0].asInt(), param["pivot"][1].asInt());

	initFromMemory((const char*)data.ptr.get(), data.length, mTextureRect);
}

Sprite::~Sprite(){
	deinit();
}

void Sprite::deinit()
{
	if(texture_id != 0)
	{
		glDeleteTextures(1, &texture_id);
		texture_id = 0;
	}
}

Eigen::Vector2i& Sprite::getSize()
{
	return mTextureSize;
}

Eigen::Vector2i& Sprite::getPivot()
{
	return mTexturePivot;
}

void Sprite::bind()
{
	if(texture_id != 0)
		glBindTexture(GL_TEXTURE_2D, texture_id);
}

bool Sprite::isInitialized()
{
	return texture_id != 0;
}

void Sprite::initFromPixels(const unsigned char* dataRGBA)
{
	deinit();
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureSize.x(), mTextureSize.y(), 0, GL_RGBA, GL_UNSIGNED_BYTE, dataRGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Sprite::initFromMemory(const char* data, size_t length, Rect rect)
{
	size_t width, height;
	std::vector<unsigned char> imageRGBA = ImageIO::loadFromMemoryRGBA32((const unsigned char*)(data), length, rect, width, height);
	if(imageRGBA.size() == 0) return;
	initFromPixels(imageRGBA.data());
}