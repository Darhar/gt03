#include "splashscreen.h"

SplashScreen::SplashScreen(void (*rcb)(int8_t menu, uint8_t option), void (*hscb)(uint32_t highscore), uint32_t highscore, uint8_t option) {
    printf("[SplashScreen] loading...\n");
    this->screenId = ScreenEnum::SPLASHSCREEN;
    this->returnCallBack = rcb;
    this->highScoreCallBack = hscb;
    this->imageAlpha = 0;
    this->accDeltaTimeMS = 0;
    this->totalDuration = 0;
    this->option = option;

    uint16_t tileWidth = 20, tileHeight = 20;
	/*
    uint8_t xCount = 4 + (DISPLAY_WIDTH / tileWidth);
    uint8_t yCount = 4 + (DISPLAY_HEIGHT / tileHeight);
	*/
    uint8_t xCount = 4;
    uint8_t yCount = 4;
    uint16_t *ts = new uint16_t[xCount*yCount];

    for (int y = 0; y < yCount; y++) {
        for (int x = 0; x < xCount; x++) {
			ts[y*xCount+x]=(x+y)%3+1;
        }
    }
    this->bgLayer = new TileMap(xCount, yCount, tileWidth, tileHeight, ts);

    TileInfo tinfo; 
    tinfo.color = Color(255, 0, 0);
    tinfo.type = COLORFILL;
    this->bgLayer->addTileInfo(1, tinfo);
    tinfo.color = Color(135, 0, 255);
    this->bgLayer->addTileInfo(2, tinfo);
    tinfo.color = Color(255, 255, 0);
    this->bgLayer->addTileInfo(3, tinfo);
     tinfo.color = Color(0,255,  255);
    this->bgLayer->addTileInfo(4, tinfo);
    printf("[SplashScreen] Done\n");
	Vec2 p0=Vec2(160, 120);
	Color cRed = Color(128,128, 255);
			
	drawSphere(10,  p0, cRed,255);
}

SplashScreen::~SplashScreen() {
    printf("[SplashScreen] Destructing\n");
}

void SplashScreen::update(uint16_t deltaTimeMS) {
	uint8_t frameQuotient; 
    this->accDeltaTimeMS += deltaTimeMS;
    frameQuotient = accDeltaTimeMS / 16;
    this->accDeltaTimeMS -= 16 * frameQuotient;
    
	
	if(this->tileMoveX >= 40){
		this->tileMoveX = 5;
	}else{
		this->tileMoveX += frameQuotient;	
	}

    this->tileMoveY = (80 * sin(this->tileMoveX * 2 * M_PI / 80))+80;
    if(this->imageAlpha < 255 - frameQuotient){
        this->imageAlpha += frameQuotient;
	}
	else{
		this->imageAlpha=0;
	}
}

void SplashScreen::draw(Display *display) {
	std::string title;
	uint16_t width;
	
	//display->clear(Color(255, 255, 255));
    //this->bgLayer->draw(display, this->tileMoveX, this->tileMoveY);

	//display->drawFillCircle(this->tileMoveX,  Vec2(160, 120), BLACKCOLOR,200);
	//display->drawFillCircle(this->tileMoveX-4,  Vec2(160, 120), WHITECOLOR,200);
	Vec2 p0=Vec2((rand() % 320), (rand() % 240));



		Color cRed = Color((rand() % 255),(rand() % 255), (rand() % 255));
		
		display->drawSphere((rand() % 30)+5,  p0, cRed,255);		


	
    //width = logoSprite.getSpriteWidth(tigerFrame);
    //logoSprite.drawSprite(display, tigerFrame, Vec2((DISPLAY_WIDTH - width)/2, 56), this->imageAlpha);
    //title = std::to_string(abs(this->tileMoveX));
    //width = alphanumfont.getTextWidth(title, 2);
    //alphanumfont.drawText(display, title, Vec2((DISPLAY_WIDTH - width)/2, 190), this->imageAlpha, 2);
}

void SplashScreen::keyPressed(uint8_t key) {
    const char c[6] = {'U', 'D', 'L', 'R', 'A', 'B'};
    printf("[SplashScreen] Key: %c\n", c[key]);
}

void SplashScreen::keyReleased(uint8_t key) {
}

void SplashScreen::keyDown(uint8_t key){
}
