#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "hardware/vreg.h"
#include "hardware/pll.h" // don't forget to add hardware_pll to your Cmakelists.txt

#define timetype uint32_t


#include <map>
#include <string>
#include <cstring>
#include <array>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

#ifndef _GAME_TIGER_COMMON_H
#define _GAME_TIGER_COMMON_H

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

#include "intmath.h"

#include "color.h"
#include "../content/logoSprite.h"
#include "../content/alphanumfont.h"

#include "image.h"
#include "tilemap.h"

#define AUDIO_PIN 5

enum ImageType {INDEXEDCOLORS, PIXELCOLOR};
enum GameState {WAITING, PLAYING, PAUSED, LOST};

typedef struct {
    float x, y, z;
} Vector3;

struct vec3 { 
	float x; 
	float y; 
	float z; 
 
	vec3 operator+(const vec3& other) const { 
		return { x + other.x, y + other.y, z + other.z }; 
	} 
 
	vec3 operator-(const vec3& other) const { 
		return { x - other.x, y - other.y, z - other.z }; 
	} 
 
	vec3 operator-() const { 
		return { -x, -y, -z }; 
	} 
 
	vec3 operator*(const float& scalar) const { 
		return { x * scalar, y * scalar, z * scalar }; 
	} 
 
	vec3 operator/(const float& scalar) const { 
		return { x / scalar, y / scalar, z / scalar }; 
	} 
 
	float dot(const vec3& other) const { 
		return x * other.x + y * other.y + z * other.z; 
	} 
 
	float len() const { 
		return sqrtf(this->dot(*this)); 
	} 
 
	void normalize() { 
		float len = this->len(); 
		x /= len; 
		y /= len; 
		z /= len; 
	} 
}; 

float intersectSphere(vec3 origin, vec3 dir, vec3 center, float radius);
timetype getTime();
uint16_t getTimeDiffMS(timetype start);
void drawSphere(int radius, Vec2 pos, Color &c, uint8_t alpha);
// Function to calculate the dot product of two vectors
float dot(Vector3 a, Vector3 b);

// Function to normalize a vector
Vector3 normalize(Vector3 v);

double distance(int x1, int y1, int x2, int y2);
int calculateIntensity(int x, int y, int centerX, int centerY, int radius);
	
extern Color BLACKCOLOR;
extern Color WHITECOLOR;
extern Color REDCOLOR;
extern Color GREENCOLOR;

extern Image alphanumfont;
extern Image allGameSprite;
extern Image allGameAlphaSprite;
extern Image menuSprite;
extern Image logoSprite;
#endif