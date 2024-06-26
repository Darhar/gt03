#include "tilemap.h"

TileMap::TileMap(uint8_t xc, uint8_t yc, uint8_t tw, uint8_t th, uint16_t* ts) {
    this->xCount = xc;
    this->yCount = yc;
    this->tileWidth = tw;
    this->tileHeight = th;
    this->tiles = ts;
    this->width = xc * tw;
    this->height = yc * th;
}

TileMap::~TileMap() {
}

void TileMap::addTileInfo(uint16_t index, TileInfo tinfo) {
    this->tileInfoList[index] = tinfo;
}

void TileMap::update(uint16_t deltaTimeMS) {
    for (auto const& x : animationFrame) {
        uint16_t frameIndex = x.second;
        animationFrame[x.first] = frameIndex+1;
    }
}

TileCollisionType TileMap::getCollisionTile(uint16_t x, uint16_t y) {
    uint16_t index = (y/this->tileHeight) * this->xCount + (x/this->tileWidth);
    uint16_t tile = this->tiles[index];
    return this->tileInfoList[tile].collisionType;
}

void TileMap::draw(Display *display, uint16_t screenx, uint16_t screeny) {
    for (int tileYIndex = 0; tileYIndex < yCount; tileYIndex++) {
		//calculate the y start corner of a tile
        int16_t ty = tileYIndex * this->tileHeight + screeny;
        if(ty + tileHeight >= 0 && ty < DISPLAY_HEIGHT) {
            for (int tileXIndex = 0; tileXIndex < xCount; tileXIndex++) {
				//calculate the x start corner of a tile 
                int16_t tx = tileXIndex * this->tileWidth + screenx;
                //int16_t tx = tileXIndex * this->tileWidth;
				
                if(tx + tileWidth >= 0 && tx < DISPLAY_WIDTH) {
                    uint16_t index = this->tiles[tileYIndex*xCount+tileXIndex];
                    TileInfo tinfo = this->tileInfoList[index];
                    if(tinfo.type == COLORFILL) {
                        display->fillRect(Rect2(tx, ty, this->tileWidth, this->tileHeight), tinfo.color);
                    } else if(tinfo.type == SPRITE) {
                        tinfo.sprite->drawSprite(display, tinfo.textureID, Vec2(tx, ty));
                    } else if(tinfo.type == ANIMATEDSPRITE) {
                        uint16_t index = tileYIndex*xCount+tileXIndex;
                        if ( animationFrame.find(index) == animationFrame.end() )
                            animationFrame[index] = 0;
                        uint16_t frameIndex = animationFrame[index];
                        if(frameIndex >= tinfo.numFrames) {
                            animationFrame[index] = 0;
                            frameIndex = 0;
                        }
                        char frame = tinfo.animationFrames[frameIndex];
                        tinfo.sprite->drawSprite(display, frame, Vec2(tx, ty));
                    }
                }
            }
        }
    }
}
