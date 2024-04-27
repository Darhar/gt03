#include "common.h"

Color BLACKCOLOR = Color((uint16_t)0x0);
Color WHITECOLOR = Color((uint16_t)0xffff);
Color REDCOLOR = Color(255, 0, 0);
Color GREENCOLOR = Color(0, 255, 0);

Image alphanumfont = Image(
	Size2(alphanumfont_img_width, alphanumfont_img_height), 
	alphanumfont_color_count, 
	(Color*)alphanumfontPaletteColors, 
	(uint8_t*)alphanumfontPaletteAlphas, 
	(uint8_t*)alphanumfont_pixel_data, 
	(uint16_t*)alphanumfontSpriteData
);

Image logoSprite = Image(
	Size2(logoSpriteWidth, logoSpriteHeight), 
	logoSpriteColorCount, 
	(Color*)logoSpritePaletteColors, 
	(uint8_t*)logoSpritePaletteAlphas, 
	(uint8_t*)logoSpritePixelData, 
	(uint16_t*)logoSpriteSpriteData
);

void drawSphere(int radius, Vec2 pos, Color &c, uint8_t alpha) {
	float lum;
	int rad2=2*radius;
	
	vec3 light{ 1.0f, 1.0f, 1.0f }; // Light shines towards right and bottom, to inside screen. 
	light.normalize(); 
 
	for (int y = 0; y < rad2; y++) { 
		for (int x = 0; x < rad2; x++) { 
			if (distance(x, y, radius, radius) <= radius){

				vec3 normal = { (float)(x - radius), (float)(y - radius), (float)-radius }; 
				normal.normalize(); 
 
				lum = normal.dot(-light); 
				if (lum < 0) { 
					lum = 0;
				}
				printf("lum : %d\n",(int)(lum*10));

				//apply the luminance to the colour components and conver from rgb565
				Color colPix=Color(
					std::min(255, ((int)(c.Colors.red *lum) << 3)+15), 
					std::min(255, ((int)(c.Colors.green*lum) << 2)+7), 
					std::min(255, ((int)(c.Colors.blue*lum) << 3)+15)
				);
				
				/*
				this->setPixel(
					Vec2(x+pos.x-radius, y+pos.y-radius), 
					colPix, 
					alpha
				);
*/				
			} 
			else{
				printf("--\n");
				
			}
		} 
	} 	
}

timetype getTime() {
    timetype now;
    now = to_ms_since_boot(get_absolute_time());

    // printf("Time: %d\n", now);
    return now;
}

uint16_t getTimeDiffMS(timetype start) {
    timetype end = getTime();
    uint16_t timeDiffMS = 0;

    timeDiffMS = (end - start);


    // printf("Time diff: %d\n", timeDiffMS);
    return timeDiffMS;
}
// Function to calculate the dot product of two vectors
float dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to normalize a vector
Vector3 normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector3){v.x / length, v.y / length, v.z / length};
}
// Function to calculate distance between two points
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to calculate the intensity of a pixel based on its distance from the center
int calculateIntensity(int x, int y, int centerX, int centerY, int radius) {
    double dist = distance(x, y, centerX, centerY);
    double intensity = 255 * (1 - (dist / radius));
    return (int) intensity;
}

float intersectSphere(vec3 origin, vec3 dir, vec3 center, float radius) { 
	vec3 oc = origin - center; 
	float a = dir.dot(dir); 
	float b = 2.0f * oc.dot(dir); 
	float c = oc.dot(oc) - radius * radius; 
	float discriminant = b * b - 4 * a * c; 
	if (discriminant < 0.0f) { 
		return -1.0f; 
	} 
	return (-b - sqrtf(discriminant)) / (2.0f * a); 
} 

// Function to convert RGB to HSL
/*
void rgbToHsl(float r, float g, float b, float* h, float* s, float* l) {
    float maxColor = fmaxf(r, fmaxf(g, b));
    float minColor = fminf(r, fminf(g, b));

    float delta = maxColor - minColor;

    *l = (maxColor + minColor) / 2;

    if (delta == 0) {
        *h = *s = 0; // achromatic
    } else {
        *s = delta / (1 - fabsf(2 * *l - 1));

        if (r == maxColor)
            *h = (g - b) / delta + (g < b ? 6 : 0);
        else if (g == maxColor)
            *h = (b - r) / delta + 2;
        else
            *h = (r - g) / delta + 4;

        *h /= 6;
    }
}

// Function to convert HSL to RGB
void hslToRgb(float h, float s, float l, float* r, float* g, float* b) {
    if (s == 0) {
        *r = *g = *b = l; // achromatic
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        *r = hueToRgb(p, q, h + 1.0f/3.0f);
        *g = hueToRgb(p, q, h);
        *b = hueToRgb(p, q, h - 1.0f/3.0f);
    }
}

float hueToRgb(float p, float q, float t) {
    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1.0f/6.0f) return p + (q - p) * 6 * t;
    if (t < 1.0f/2.0f) return q;
    if (t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6;
    return p;
}

*/
