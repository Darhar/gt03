#include "keyboard.h"
#include "hardware/adc.h"

KeyBoard::KeyBoard() {
    printf("[Keyboard] driver loading...\n");
    for (uint8_t i = 0; i < KEY_COUNT; i++)
        this->prevKeyState[i] == false;

    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        gpio_init(pinId[i]);
        gpio_set_dir(pinId[i], GPIO_IN);
        gpio_pull_up(pinId[i]);
    }
	//set up analog for joystick 
    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    adc_gpio_init(27);	
    printf("[Keyboard] Done\n");
}

KeyBoard::~KeyBoard() {
}

void KeyBoard::checkKeyState(Screen *screen) {
	//get analog values for joystick
	adc_select_input(0);
	uint adc_x_raw = adc_read();	
	adc_select_input(1);
	uint adc_y_raw = adc_read();	

    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        bool keyState = !gpio_get(pinId[i]);
		if (i<4){
			//check joystick
			if(i == KEY_LEFT & adc_x_raw<100) {
				keyState=true;
			}
			else if(i == KEY_RIGHT & adc_x_raw>4000){ 
				keyState=true;
			}		
			if(i == KEY_DOWN & adc_y_raw<100 ){
				keyState=true;
			}
			else if (i == KEY_UP & adc_y_raw>4000){
				keyState=true;
			}		
		}
		
		if (this->prevKeyState[i] != keyState) {//if button state has changed
			if (keyState) {
				screen->keyPressed(i);
				//printf("[Keyboard] %d\n",i);
			} else
				screen->keyReleased(i);
		} else if(keyState)//if button state hasnt changed but is pressed
			screen->keyDown(i);
		this->prevKeyState[i] = keyState; 
	}	
		/**/
	//printf("x:%d,y:%d\n",adc_x_raw,adc_y_raw);

	

}
