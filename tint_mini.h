/*
MIT No Attribution

Copyright 2022 Martinus Theodorus Johannes Helena ten Velden

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TINT_MINI_H
#define TINT_MINI_H

#define TM_FUNCTION static

#include <math.h>


struct tm_tint_t
{
	float color; //< 0.0 (red) <= color < 360.0, 60.0 == yellow, 120.0 == green, 180.0 == cyan, 240.0 == blue, 300.0 == magenta
	float saturation; //< 0.0 <= saturation <= 1.0
	float tint; //< -1.0 (black) <= tint <= +1.0 (white) <- -1.0 and +1.0 mapping is arbitrary
};
// NOTE: tm_tint_black does not require color nor saturation thus both are undefined
static const struct tm_tint_t tm_tint_black = { .tint = -1.0f };
// NOTE: tm_tint_gray does not require color thus is undefined
static const struct tm_tint_t tm_tint_gray = { .saturation = 0.0f, .tint = 0.5f };
// NOTE: tm_tint_white does not require color not saturation thus both are undefined
static const struct tm_tint_t tm_tint_white = { .tint = +1.0f };
static const struct tm_tint_t tm_tint_red = { .color = 0.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tm_tint_green = { .color = 120.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tm_tint_blue = { .color = 240.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tm_tint_darkred = { .color = 0.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tm_tint_lightred = { .color = 0.0f, .saturation = 1.0f, .tint = +0.5f };
static const struct tm_tint_t tm_tint_darkgreen = { .color = 120.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tm_tint_lightgreen = { .color = 120.0f, .saturation = 1.0f, .tint = +0.5f };
static const struct tm_tint_t tm_tint_darkblue = { .color = 240.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tm_tint_lightblue = { .color = 240.0f, .saturation = 1.0f, .tint = +0.5f };

// NOTE: e.g. for a light where adding lightens
struct tm_light_t
{
	float color; //< 0.0 <= color < 360.0
	float saturation; //< 0.0 <= saturation <= 1.0
	float brightness; //< 0.0 (black) <= brightness <= 1.0 (white)
};
static const struct tm_light_t tm_light_black = { .brightness = 0.0f };
static const struct tm_light_t tm_light_gray = { .saturation = 0.0f, .brightness = 0.5f };
static const struct tm_light_t tm_light_white = { .brightness = 1.0f };

struct tm_lightrgb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_lightrgb_t tm_lightrgb_black = { .r = 0.0f, .g = 0.0f, .b = 0.0f };
static const struct tm_lightrgb_t tm_lightrgb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_lightrgb_t tm_lightrgb_white = { .r = 1.0f, .g = 1.0f, .b = 1.0f };

struct tm_lightcmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_lightcmy_t tm_lightcmy_black = { .c = 0.0f, .m = 0.0f, .y = 0.0f };
static const struct tm_lightcmy_t tm_lightcmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_lightcmy_t tm_lightcmy_white = { .c = 1.0f, .m = 1.0f, .y = 1.0f };

// NOTE: e.g. a print on a white background where adding darkens
struct tm_print_t
{
	float color; //< 0.0 <= color <= 360.0
	float saturation; //< 0.0 <= saturation <= 1.0
	float darkness; //< 0.0 (white) <= darkness <= 1.0 (black)
};
static const struct tm_print_t tm_print_black = { .darkness = 1.0f };
static const struct tm_print_t tm_print_gray = { .saturation = 0.0f, .darkness = 0.5f };
static const struct tm_print_t tm_print_white = { .darkness = 0.0f };

struct tm_printrgb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_printrgb_t tm_printrgb_black = { .r = 1.0f, .g = 1.0f, .b = 1.0f };
static const struct tm_printrgb_t tm_printrgb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_printrgb_t tm_printrgb_white = { .r = 0.0f, .g = 0.0f, .b = 0.0f };

struct tm_printcmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_printcmy_t tm_printcmy_black = { .c = 1.0f, .m = 1.0f, .y = 1.0f };
static const struct tm_printcmy_t tm_printcmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_printcmy_t tm_printcmy_white = { .c = 0.0f, .m = 0.0f, .y = 0.0f };

//*****************************************************************************

// NOTE: tm_rgb_t is only for representing color (i.e. "saturation == 1.0f &..
//       .. tint == 0.0f")
//       ^
//       thus impossible.. e.g. dark red, light red, less saturated red
struct tm_rgb_t
{
	float r;
	float g;
	float b;
};
// NOTE: tm_cmy_t is only for representing color (i.e. "saturation == 1.0f &..
//       .. tint == 0.0f")
//       ^
//       thus impossible.. e.g. dark cyan, light cyan, less saturated cyan
struct tm_cmy_t
{
	float c;
	float m;
	float y;
};

// NOTE: if color == 0.0f.. returns { .r == 1.0f, .g = 0.0f, .b = 0.0f }
//       if color == 60.0f.. returns { .r = 0.5f, .g = 0.5f, .b = 0.0f }
//       .
//       .
//       .
// NOTE: assumes 0.0 <= color < 360.0
TM_FUNCTION struct tm_rgb_t tm_color_to_rgb(float color)
{
	struct tm_rgb_t rgb;

	// 1. calculate distance from r/g/b as..
	//    .. 0.0f == no r/g/b
	//    .. 0.5f == 50% between r-g/g-b/b-r
	//    .. 1.0f == at r/g/b
	float a = 1.0f - (fminf(color, 120.0f) / 120.0f); //< "+r"
	float b = 1.0f - ((360.0f - fmaxf(240.0f, color)) / 120.0f); //< "-r"
	//rgb.r = fmaxf(a, b);
	rgb.r = a + b;
	rgb.g = 1.0f - fabsf((fminf(color, 240.0f) - 120.0f) / 120.0f);
	rgb.b = 1.0f - fabsf((fmaxf(color, 120.0f) - 240.0f) / 120.0f);

	// 2. if r/g/b >= 0.5f.. r/g/b == 1.0f, otherwise.. r/g/b *= 2.0f
	
	rgb.r = rgb.r >= 0.5f ? 1.0f : rgb.r * 2.0f;
	rgb.g = rgb.g >= 0.5f ? 1.0f : rgb.g * 2.0f;
	rgb.b = rgb.b >= 0.5f ? 1.0f : rgb.b * 2.0f;

	return rgb;
}

//*****************************************************************************

TM_FUNCTION struct tm_light_t tm_tint_to_light(struct tm_tint_t tint)
{
	struct tm_light_t light;
	light.color = tint.color;
	light.saturation = tint.saturation;
	light.brightness = (tint.tint / 2.0f) + 0.5f;
	return light;
}
TM_FUNCTION struct tm_tint_t tm_light_to_tint(struct tm_light_t light)
{
	struct tm_tint_t tint;
	tint.color = light.color;
	tint.saturation = light.saturation;
	tint.tint = (light.brightness - 0.5f) * 2.0f;
	return tint;
}
// NOTE: not sure if 100% correct
TM_FUNCTION struct tm_lightrgb_t tm_tint_to_lightrgb(struct tm_tint_t tint)
{
	//printf("tint.color %f tint.saturation %f tint.tint %f\n", tint.color, tint.saturation, tint.tint);

	// 1. color from tint w.o. saturation nor tint

	struct tm_rgb_t rgb = tm_color_to_rgb(tint.color);
	
	//printf("rgb.r %f rgb.g %f rgb.b %f\n", rgb.r, rgb.g, rgb.b);
	
	// 2. apply saturation (i.e. lerp(rgb, lightrgb_gray, tint.saturation)..?)
	
	struct tm_lightrgb_t lightrgb;
	lightrgb.r = tint.saturation * rgb.r + (1.0f - tint.saturation) * 0.5f;
	lightrgb.g = tint.saturation * rgb.g + (1.0f - tint.saturation) * 0.5f;
	lightrgb.b = tint.saturation * rgb.b + (1.0f - tint.saturation) * 0.5f;
	
	//printf("lightrgb.r %f lightrgb.g %f lightrgb.b %f\n", lightrgb.r, lightrgb.g, lightrgb.b);
	
	// 3. apply tint
	
	// if tint.tint > 0.0f.. lerp(rgb, lightrgb_white, tint.tint)
	if(tint.tint > 0.0f)
	{
		lightrgb.r = lightrgb.r * (1.0f - tint.tint) + 1.0f * tint.tint;
		lightrgb.g = lightrgb.g * (1.0f - tint.tint) + 1.0f * tint.tint;
		lightrgb.b = lightrgb.b * (1.0f - tint.tint) + 1.0f * tint.tint;
	}
	// if tint.tint < 0.5f.. lerp(lightrgb, lightrgb_black, -tint.tint)
	if(tint.tint < 0.0f)
	{
		lightrgb.r = lightrgb.r * (1.0f - (-tint.tint));
		lightrgb.g = lightrgb.g * (1.0f - (-tint.tint));
		lightrgb.b = lightrgb.b * (1.0f - (-tint.tint));
	}
	
	//printf("lightrgb.r %f lightrgb.g %f lightrgb.b %f\n", lightrgb.r, lightrgb.g, lightrgb.b);
	
	return lightrgb;
};
TM_FUNCTION struct tm_lightrgb_t tm_light_to_lightrgb(struct tm_light_t light)
{
	struct tm_tint_t tint = tm_light_to_tint(light);
	return tm_tint_to_lightrgb(tint);
}

TM_FUNCTION struct tm_print_t tm_tint_to_print(struct tm_tint_t tint)
{
	struct tm_print_t print;
	print.color = tint.color;
	print.saturation = tint.saturation;
	print.darkness = ((-tint.tint) / 2.0f) + 0.5f;
}
TM_FUNCTION struct tm_tint_t tm_print_to_tint(struct tm_print_t print)
{
	struct tm_tint_t tint;
	tint.color = print.color;
	tint.saturation = print.saturation;
	tint.tint = -((print.darkness - 0.5f) * 2.0f);
	return tint;
}
TM_FUNCTION struct tm_printrgb_t tm_tint_to_printrgb(struct tm_tint_t tint)
{
	tint.tint = -tint.tint;
	struct tm_lightrgb_t a = tm_tint_to_lightrgb(tint); //< not actually lightrgb as above tint.tint = -tint.tint
	struct tm_printrgb_t printrgb = { .r = a.r, .g = a.g, .b = a.b };
	return printrgb;
}
TM_FUNCTION struct tm_printrgb_t tm_print_to_printrgb(struct tm_print_t print)
{
	struct tm_tint_t tint = tm_print_to_tint(print);
	return tm_tint_to_printrgb(tint);
}

TM_FUNCTION struct tm_print_t tm_light_to_print(struct tm_light_t light)
{
	struct tm_print_t print;
	print.color = light.color;
	print.saturation = light.saturation;
	print.darkness = 1.0f - light.brightness;
	return print;
}
TM_FUNCTION struct tm_printrgb_t tm_lightrgb_to_printrgb(struct tm_lightrgb_t lightrgb)
{
	struct tm_printrgb_t printrgb;
	printrgb.r = 1.0f - lightrgb.r;
	printrgb.g = 1.0f - lightrgb.g;
	printrgb.b = 1.0f - lightrgb.b;
	return printrgb;
}
TM_FUNCTION struct tm_light_t tm_print_to_light(struct tm_print_t print)
{
	struct tm_light_t light;
	light.color = print.color;
	light.saturation = print.saturation;
	light.brightness = 1.0f - print.darkness;
	return light;
}
TM_FUNCTION struct tm_lightrgb_t tm_printrgb_to_lightrgb(struct tm_printrgb_t printrgb)
{
	struct tm_lightrgb_t lightrgb;
	lightrgb.r = 1.0f - printrgb.r;
	lightrgb.g = 1.0f - printrgb.g;
	lightrgb.b = 1.0f - printrgb.b;
	return lightrgb;
}

#endif
