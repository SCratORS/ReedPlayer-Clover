#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
			    if (paramName == "blendMode") blendMode = node[paramName].asInt();
			    else if (paramName == "visible") visible = node[paramName].asBool();
			    else if (paramName == "hFlip") hFlip = node[paramName].asBool();
			    else if (paramName == "magFilterMode") magFilterMode = node[paramName].asInt();
			    else if (paramName == "minFilterMode") minFilterMode = node[paramName].asInt();
			    else if (paramName == "vFlip") vFlip = node[paramName].asBool();
			    else if (paramName == "viewDepth") viewDepth = node[paramName].asInt();
			    else if (paramName == "layer") layer = node[paramName].asInt();
				else if (paramName == "spriteId") spriteId = node[paramName].asString();
				else if (paramName == "color") color = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(),
																		node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "size") size = Eigen::Vector2f((float)node[paramName][0].asInt(), (float)node[paramName][1].asInt());
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					Component::Propertie prop;
					prop.linkType = node[paramName][propertieName]["linkType"].asString();
					prop.linkId = node[paramName][propertieName]["linkId"].asString();
					properties.insert(make_pair(propertieName, prop));
				}
				else std::cout << "***WARNING(SpriteComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(SpriteComponent): Except in propertie: " << paramName << std::endl;
		}
	}
	if (!spriteId.empty()) sprite = new Sprite(spriteId);
	updateVertices();
	updateColor();
}

void SpriteComponent::updateVertices(){
	Eigen::Vector2f scale(1.0,1.0);
	Eigen::Vector2f topLeft(-size.x()/2, size.y()/2);
	Eigen::Vector2f bottomRight(size.x()/2, -size.y()/2);
	if(sprite && sprite->isInitialized()){

		Eigen::Vector2i spriteSize = sprite->getSize();
		Eigen::Vector2i spritePivot = sprite->getPivot();

		scale << (spriteSize.x()?size.x() / spriteSize.x():1.0), (spriteSize.y()?size.y() / spriteSize.y():1.0);
		topLeft << -spritePivot.x() * scale.x(), spritePivot.y() * scale.y();
		bottomRight << (spriteSize.x()-spritePivot.x()) * scale.x(), -(spriteSize.y() - spritePivot.y()) * scale.y();
	}
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
	if(hFlip) for(int i = 0; i < 6; i++) mVertices[i].tex[0] = mVertices[i].tex[0] == px ? 0 : px;
	if(vFlip) for(int i = 1; i < 6; i++) mVertices[i].tex[1] = mVertices[i].tex[1] == py ? 0 : py;
}

void SpriteComponent::setColor4bArray(GLubyte* array, unsigned int color)
{
	array[0] = (color & 0xff000000) >> 24;
	array[1] = (color & 0x00ff0000) >> 16;
	array[2] = (color & 0x0000ff00) >> 8;
	array[3] = (color & 0x000000ff);
}

void SpriteComponent::buildGLColorArray(GLubyte* ptr, unsigned int color, unsigned int vertCount)
{
	unsigned int colorGl;
	setColor4bArray((GLubyte*)&colorGl, color);
	for(unsigned int i = 0; i < vertCount; i++)
	{
		((GLuint*)ptr)[i] = colorGl;
	}
}

void SpriteComponent::updateColor()
{
	unsigned int new_color = 
		uint8_t(color[0]*0xFF) << 24 |
		uint8_t(color[1]*0xFF) << 16 |
		uint8_t(color[2]*0xFF) << 8 |
		uint8_t(color[3]*0xFF);
	mColorShift = new_color;
	buildGLColorArray(colors, mColorShift, 6);
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::render(const Eigen::Affine3f& parentTrans)
{
	if (!(visible&&enabled)) return;
	glLoadMatrixf((float*) parentTrans.data());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &mVertices[0].pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
	if(sprite && sprite->isInitialized()){
		sprite->bind();
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

void SpriteComponent::update(int deltaTime)
{

}

Point SpriteComponent::getSize(){
	return {size.x(), size.y()};
}
