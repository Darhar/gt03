#include "common.h"
#include "display.h"

#ifndef _GAME_TIGER_IMAGE_H
#define _GAME_TIGER_IMAGE_H

const std::string ref = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

typedef struct Image
{
private:
    bool hasIndexedColors;
    Color *palette;
    uint8_t *alphas;
    uint8_t *pixelData;
    uint16_t colorCount;
    uint16_t *spriteData;
    Size2 size;

    uint16_t getSpriteX(uint16_t index);
    uint16_t getSpriteY(uint16_t index);
    void draw(Display *display, Rect2 destRect, Rect2 spriteRect, uint8_t alpha, bool flipH, bool flipV);
public:

    Image(Size2 size, uint16_t colorCount, Color *palette, uint8_t *alphas, uint8_t *pixelData);
    Image(Size2 size, uint16_t colorCount, Color *palette, uint8_t *alphas, uint8_t *pixelData, uint16_t *spriteData);
    Image(Size2 size, Color *pixelData, uint16_t *spriteData);

    void drawText(Display *display, std::string text, Vec2 destPos);
    void drawText(Display *display, std::string text, Vec2 destPos, uint8_t alpha);
    void drawText(Display *display, std::string text, Vec2 destPos, uint8_t alpha, uint8_t scaleRatio);
    uint16_t getTextWidth(std::string text);
    uint16_t getTextWidth(std::string text, uint8_t scaleRatio);

    void drawSprite(Display *display, uint16_t index, Vec2 destPos, bool flipH = false, bool flipV = false);
    void drawSprite(Display *display, uint16_t index, Vec2 destPos, uint8_t alpha, bool flipH = false, bool flipV = false);
    void drawSprite(Display *display, uint16_t index, Rect2 destRect, uint8_t alpha, bool flipH = false, bool flipV = false);
    uint16_t getSpriteWidth(uint16_t index);
    uint16_t getSpriteHeight(uint16_t index);
}Image;

class Sprite
{
private:
    uint8_t xCount, yCount;
    uint8_t tileWidth, tileHeight;
    uint16_t *tiles;
    std::map<uint16_t, uint8_t> animationFrame;
public:
    uint16_t width, height;
    
    Sprite(uint8_t xc, uint8_t yc, uint8_t tw, uint8_t th, uint16_t *ts);
    ~Sprite();
    void draw(Display *display, uint16_t screenx, uint16_t screeny);
    void update(uint16_t deltaTimeMS);
};
#endif