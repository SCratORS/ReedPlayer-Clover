#include "platform.h"
#include GLHEADER
#include "ImageIO.h"

#include <string>
#include <eigen3/Eigen/Dense>
#include <json/json.h>

class Sprite
{
public:
	Sprite(std::string id);
	~Sprite();
	bool isInitialized();
	Eigen::Vector2i& getSize();
	Eigen::Vector2i& getPivot();
	void bind();

private:
	void deinit();
	Eigen::Vector2i mTextureSize;
	Eigen::Vector2i mTexturePivot;
	Rect mTextureRect;
	GLuint texture_id;
	void initFromMemory(const char* file, size_t length, Rect rect = {0,0,0,0});
	void initFromPixels(const unsigned char* dataRGBA);
};