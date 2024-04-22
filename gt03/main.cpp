#include "core/common.h"
#include "core/display.h"
#include "core/keyboard.h"
#include "screens/splashscreen.h"

#define HIGHSCORESIZE (FLASH_PAGE_SIZE/4)
#define FLASH_TARGET_OFFSET (1536 * 1024)

Screen *screen;

uint32_t highscores[64];
bool shouldSwitchScreen;
uint8_t newScreenId, newOption;

void highScoreHandler(uint32_t highscore) {
	printf("HSHandler");
    highscores[0] = 64;highscores[1] = 128;
    highscores[screen->screenId] = highscore;

}
/*
void readHighScoreData() {
    const uint32_t* flash_target_contents = (const uint32_t *) (XIP_BASE + FLASH_TARGET_OFFSET);
    for (int i = 0; i < HIGHSCORESIZE; i++)
        highscores[i] = flash_target_contents[i];
    if(highscores[0] != 64 || highscores[1] != 128)
        for (int i = 0; i < HIGHSCORESIZE; i++)
            highscores[i] = 0;
}
*/
void backHandler(int8_t menu, uint8_t option) {
	printf("BackHandler");

    newScreenId = menu;
    newOption = option;
    shouldSwitchScreen = true;
}

int main(int argc, char *argv[]) {
    set_sys_clock_khz(266 * 1000, true);
    sleep_ms(50);

    stdio_init_all();
    sleep_ms(1000);

    printf("[Main] Starting\n");
    srand((unsigned int)time(0));

    Display *display = new Display();
    display->initDMAChannel();
    display->initSequence();
    display->clear(Color(255, 255, 255));
    display->update();

    KeyBoard *keyboard = new KeyBoard();
	screen = new SplashScreen(*backHandler, *highScoreHandler, 0, 1);

 
    timetype lastUpdate = getTime();
    bool close = false;
    while (!close) {
        uint16_t deltaTimeMS = getTimeDiffMS(lastUpdate);
        lastUpdate = getTime();

        screen->update(deltaTimeMS);
        keyboard->checkKeyState(screen);
        screen->draw(display);

        display->update();

    }

    return EXIT_SUCCESS;
}