#include "TextureComponent.h"

#include "ImageIO.h"

#include "TextureResourceCollect.h"
#include "ResourcesCollect.h"

extern ResourcesCollect * resourcesCollect;
extern TextureResourceCollect * textureResourceCollect;

TextureComponent::TextureComponent(Json::Value node):Component(node), texture_id(0) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
			    if (paramName == "blendMode") blendMode = node[paramName].asInt();
			    else if (paramName == "visible") visible = node[paramName].asBool();
			    else if (paramName == "magFilterMode") magFilterMode = node[paramName].asInt();
			    else if (paramName == "minFilterMode") minFilterMode = node[paramName].asInt();
			    else if (paramName == "viewDepth") viewDepth = node[paramName].asInt();
			    else if (paramName == "layer") layer = node[paramName].asInt();
				else if (paramName == "textureId") textureId = node[paramName].asString();
			    else if (paramName == "horizontalWrapMode") horizontalWrapMode = node[paramName].asInt();
			    else if (paramName == "verticalWrapMode") verticalWrapMode = node[paramName].asInt();
				else if (paramName == "color") color = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(),
																		node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "size") size = Eigen::Vector2f((float)node[paramName][0].asInt(), (float)node[paramName][1].asInt());
				else if (paramName == "uvOffset") uvOffset = Eigen::Vector2f(node[paramName][0].asFloat(), node[paramName][1].asFloat());
				else if (paramName == "uvRepeat") uvRepeat = Eigen::Vector2f(node[paramName][0].asFloat(), node[paramName][1].asFloat());
				else if (paramName == "pivot") pivot = Eigen::Vector2f(node[paramName][0].asFloat(), node[paramName][1].asFloat());
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					Component::Propertie prop;
					prop.linkType = node[paramName][propertieName]["linkType"].asString();
					prop.linkId = node[paramName][propertieName]["linkId"].asString();
					properties.insert(make_pair(propertieName, prop));
				}
				else std::cout << "***WARNING(TextureComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(TextureComponent): Except in propertie: " << paramName << std::endl;
		}
	}

	if (textureId != "") {
		resource * res =  resourcesCollect->getParam(textureId);
		if (res) {
			if (res->type == "TextureResource") {
				TextureResource data = textureResourceCollect->getData(textureId);
				initFromMemory((const char*)data.ptr.get(), data.length, Rect{0, 0, 0, 0});
			} else std::cout << "***ERROR(TextureResource): Unknown type texture: " << res->type << std::endl;
		} else std::cout << "***ERROR(TextureComponent): Not found texture resource: " << textureId << std::endl;
	} else std::cout << "***WARNING(TextureComponent): TextureId is empty" << std::endl;

	updateVertices();
	updateColor();
}

void TextureComponent::initFromPixels(const unsigned char* dataRGBA)
{
	deinit();
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	if (dataRGBA) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataRGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}

void TextureComponent::initFromMemory(const char* data, size_t length, Rect rect)
{
	std::vector<unsigned char> imageRGBA = ImageIO::loadFromMemoryRGBA32((const unsigned char*)(data), length, rect, width, height);
	if(imageRGBA.size() == 0) return;
	initFromPixels(imageRGBA.data());
}

void TextureComponent::bind()
{
	if(texture_id != 0) glBindTexture(GL_TEXTURE_2D, texture_id);
}

bool TextureComponent::isInitialized()
{
	return texture_id != 0;
}

void TextureComponent::updateVertices(){
	Eigen::Vector2f topLeft(-size.x()* pivot.x() ,size.y()* pivot.y());
	Eigen::Vector2f bottomRight(size.x()* pivot.x(), -size.y()*pivot.y());
	mVertices[0].pos << topLeft.x(), topLeft.y();
	mVertices[1].pos << topLeft.x(), bottomRight.y();
	mVertices[2].pos << bottomRight.x(), topLeft.y();
	mVertices[3].pos << bottomRight.x(), topLeft.y();
	mVertices[4].pos << topLeft.x(), bottomRight.y();
	mVertices[5].pos << bottomRight.x(), bottomRight.y();
	float px, py;px = 1;py = 1;
	mVertices[0].tex << 0, py;
	mVertices[1].tex << 0, 0;
	mVertices[2].tex << px, py;
	mVertices[3].tex << px, py;
	mVertices[4].tex << 0, 0;
	mVertices[5].tex << px, 0;
}

void TextureComponent::setColor4bArray(GLubyte* array, unsigned int color)
{
	array[0] = (color & 0xff000000) >> 24;
	array[1] = (color & 0x00ff0000) >> 16;
	array[2] = (color & 0x0000ff00) >> 8;
	array[3] = (color & 0x000000ff);
}

void TextureComponent::buildGLColorArray(GLubyte* ptr, unsigned int color, unsigned int vertCount)
{
	unsigned int colorGl;
	setColor4bArray((GLubyte*)&colorGl, color);
	for(unsigned int i = 0; i < vertCount; i++)
	{
		((GLuint*)ptr)[i] = colorGl;
	}
}

void TextureComponent::updateColor()
{
	unsigned int new_color = 
		uint8_t(color[0]*0xFF) << 24 |
		uint8_t(color[1]*0xFF) << 16 |
		uint8_t(color[2]*0xFF) << 8 |
		uint8_t(color[3]*0xFF);
	mColorShift = new_color;
	buildGLColorArray(colors, mColorShift, 6);
}

TextureComponent::~TextureComponent(){
	deinit();
}

void TextureComponent::deinit()
{
	if(texture_id != 0)
	{
		glDeleteTextures(1, &texture_id);
		texture_id = 0;
	}
}

GLuint * TextureComponent::getTexture()
{
	return &texture_id;
}

void TextureComponent::setColor(int v0, int v1, int v2, int v3) 
{
	color = Eigen::Vector4f((float)v0,(float)v1,(float)v2,(float)v3);
	updateColor();
}


void TextureComponent::render(const Eigen::Affine3f& parentTrans)
{
	if (!(visible&&enabled)) return;
	glLoadMatrixf((float*) parentTrans.data());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &mVertices[0].pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
	if(isInitialized()){
		bind();
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &mVertices[0].tex);		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void TextureComponent::update(int deltaTime)
{

}
