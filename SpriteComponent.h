#pragma once
#include <json/json.h>
#include "Component.h"
#include <eigen3/Eigen/Dense>

#include "platform.h"
#include GLHEADER

#include "Sprite.h"
#include "utils.h"

class SpriteComponent: public Component
{
public:
    SpriteComponent(Json::Value json);
    ~SpriteComponent();
    void update(int deltaTime);
    void render(const Eigen::Affine3f& parentTrans);
    Point getSize();
private:
    struct Vertex
    {
        Eigen::Vector2f pos;
        Eigen::Vector2f tex;
    } mVertices[6];

    int blendMode = 0;
    Eigen::Vector4f color = Eigen::Vector4f(1.0,1.0,1.0,1.0);
    bool visible = true;
    bool hFlip = false;
    int magFilterMode = 1;
    int minFilterMode = 1;
    std::string spriteId = "";
    bool vFlip = false;
    int viewDepth = 0;
    int layer = 0;
    Eigen::Vector2f size = Eigen::Vector2f(0.0,0.0);
    unsigned int mColorShift = 0xFFFFFFFF;
    GLubyte colors[6*4];

    Sprite * sprite = NULL;

    void updateVertices();
    void updateColor();
    void buildGLColorArray(GLubyte* ptr, unsigned int color, unsigned int vertCount);
    void setColor4bArray(GLubyte* array, unsigned int color);

};