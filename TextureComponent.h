#pragma once
#include <json/json.h>
#include "Component.h"
#include <eigen3/Eigen/Dense>

#include "platform.h"
#include GLHEADER

class TextureComponent: public Component
{
public:
    TextureComponent(Json::Value json);
    ~TextureComponent();
    void update(int deltaTime);
    void render(const Eigen::Affine3f& parentTrans);
    GLuint * getTexture();
    void setColor(int,int,int,int);
private:
    struct Vertex
    {
        Eigen::Vector2f pos;
        Eigen::Vector2f tex;
    } mVertices[6];

    int blendMode = 0;
    Eigen::Vector4f color = Eigen::Vector4f(1.0,1.0,1.0,1.0);
    bool visible = true;
    int magFilterMode = 1;
    int minFilterMode = 1;
    std::string textureId = "";
    int viewDepth = 0;
    int layer = 0;
    Eigen::Vector2f size = Eigen::Vector2f(0.0,0.0);
    Eigen::Vector2f pivot = Eigen::Vector2f(0.0,0.0);
    unsigned int mColorShift = 0xFFFFFFFF;
    GLubyte colors[6*4];
    GLuint texture_id;
    size_t width,height;
    int horizontalWrapMode;
    Eigen::Vector2f uvOffset = Eigen::Vector2f(0.0,0.0);
    Eigen::Vector2f uvRepeat = Eigen::Vector2f(0.0,0.0);

    int verticalWrapMode;

    void updateVertices();
    void updateColor();
    void buildGLColorArray(GLubyte* ptr, unsigned int color, unsigned int vertCount);
    void setColor4bArray(GLubyte* array, unsigned int color);
    bool isInitialized();
    void initFromMemory(const char* data, size_t length, Rect rect);
    void initFromPixels(const unsigned char* dataRGBA);
    void bind();
    void deinit();
};