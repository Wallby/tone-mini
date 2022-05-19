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

#define TINT_MINI_VERSION 0.1

#define TM_FUNCTION static

#include <math.h>


struct tm_tint_t
{
	float color; //< 0.0 (red) <= color < 360.0, 60.0 == yellow, 120.0 == green, 180.0 == cyan, 240.0 == blue, 300.0 == magenta
	float saturation; //< 0.0 <= saturation <= 1.0
	float tint; //< -1.0 (black) <= tint <= +1.0 (white) <- -1.0 and +1.0 mapping is arbitrary
};
// NOTE: tint_black does not require color nor saturation thus both are undefined
static const struct tm_tint_t tint_black = { .tint = -1.0f };
// NOTE: tint_gray does not require color thus is undefined
static const struct tm_tint_t tint_gray = { .saturation = 0.0f, .tint = 0.5f };
// NOTE: tint_white does not require color not saturation thus both are undefined
static const struct tm_tint_t tint_white = { .tint = +1.0f };
static const struct tm_tint_t tint_red = { .color = 0.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tint_green = { .color = 120.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tint_blue = { .color = 240.0f, .saturation = 1.0f, .tint = 0.0f };
static const struct tm_tint_t tint_darkred = { .color = 0.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tint_lightred = { .color = 0.0f, .saturation = 1.0f, .tint = +0.5f };
static const struct tm_tint_t tint_darkgreen = { .color = 120.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tint_lightgreen = { .color = 120.0f, .saturation = 1.0f, .tint = +0.5f };
static const struct tm_tint_t tint_darkblue = { .color = 240.0f, .saturation = 1.0f, .tint = -0.5f };
static const struct tm_tint_t tint_lightblue = { .color = 240.0f, .saturation = 1.0f, .tint = +0.5f };

struct tm_lighthsv_t
{
	float h; //< 0.0 <= h < 360.0
	float s; //< 0.0 <= s <= 1.0
	float v; //< 0.0 (black) <= v <= 1.0 (white)
};
static const struct tm_lighthsv_t lighthsv_black = { .v = 0.0f };
static const struct tm_lighthsv_t lighthsv_gray = { .s = 0.0f, .v = 0.5f };
static const struct tm_lighthsv_t lighthsv_white = { .v = 1.0f };

struct tm_lightrgb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_lightrgb_t lightrgb_black = { .r = 0.0f, .g = 0.0f, .b = 0.0f };
static const struct tm_lightrgb_t lightrgb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_lightrgb_t lightrgb_white = { .r = 1.0f, .g = 1.0f, .b = 1.0f };

struct tm_lightcmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_lightcmy_t lightcmy_black = { .c = 0.0f, .m = 0.0f, .y = 0.0f };
static const struct tm_lightcmy_t lightcmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_lightcmy_t lightcmy_white = { .c = 1.0f, .m = 1.0f, .y = 1.0f };

struct tm_printerhsv_t
{
	float h; //< 0.0 <= h <= 360.0
	float s; //< 0.0 <= s <= 1.0
	float v; //< 0.0 (white) <= v <= 1.0 (black)
};
static const struct tm_printerhsv_t tm_printerhsv_black = { .v = 1.0f };
static const struct tm_printerhsv_t tm_printerhsv_gray = { .s = 0.0f, .v = 0.5f };
static const struct tm_printerhsv_t tm_printerhsv_white = { .v = 0.0f };

struct tm_printerrgb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_printerrgb_t tm_printerrgb_black = { .r = 1.0f, .g = 1.0f, .b = 1.0f };
static const struct tm_printerrgb_t tm_printerrgb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_printerrgb_t tm_printerrgb_white = { .r = 0.0f, .g = 0.0f, .b = 0.0f };

struct tm_printercmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_printercmy_t tm_printercmy_black = { .c = 1.0f, .m = 1.0f, .y = 1.0f };
static const struct tm_printercmy_t tm_printercmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_printercmy_t tm_printercmy_white = { .c = 0.0f, .m = 0.0f, .y = 0.0f };

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

TM_FUNCTION struct tm_lighthsv_t tm_tint_to_lighthsv(struct tm_tint_t tint)
{
	struct tm_lighthsv_t lighthsv;
	lighthsv.h = tint.color;
	lighthsv.s = tint.saturation;
	lighthsv.v = (tint.tint / 2.0f) + 0.5f;
	return lighthsv;
}
TM_FUNCTION struct tm_tint_t tm_lighthsv_to_tint(struct tm_lighthsv_t lighthsv)
{
	struct tm_tint_t tint;
	tint.color = lighthsv.h;
	tint.saturation = lighthsv.s;
	tint.tint = (lighthsv.v - 0.5f) * 2.0f;
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
TM_FUNCTION struct tm_lightrgb_t tm_lighthsv_to_lightrgb(struct tm_lighthsv_t lighthsv)
{
	struct tm_tint_t tint = tm_lighthsv_to_tint(lighthsv);
	return tm_tint_to_lightrgb(tint);
}

TM_FUNCTION struct tm_printerhsv_t tm_tint_to_printerhsv(struct tm_tint_t tint)
{
	struct tm_printerhsv_t printerhsv;
	printerhsv.h = tint.color;
	printerhsv.s = tint.saturation;
	printerhsv.v = ((-tint.tint) / 2.0f) + 0.5f;
}
TM_FUNCTION struct tm_tint_t tm_printerhsv_to_tint(struct tm_printerhsv_t printerhsv)
{
	struct tm_tint_t tint;
	tint.color = printerhsv.h;
	tint.saturation = printerhsv.s;
	tint.tint = -((printerhsv.v - 0.5f) * 2.0f);
	return tint;
}
TM_FUNCTION struct tm_printerrgb_t tm_tint_to_printerrgb(struct tm_tint_t tint)
{
	tint.tint = -tint.tint;
	struct tm_lightrgb_t a = tm_tint_to_lightrgb(tint); //< not actually lightrgb as above tint.tint = -tint.tint
	struct tm_printerrgb_t printerrgb = { .r = a.r, .g = a.g, .b = a.b };
	return printerrgb;
}
TM_FUNCTION struct tm_printerrgb_t tm_printerhsv_to_printerrgb(struct tm_printerhsv_t printerhsv)
{
	struct tm_tint_t tint = tm_printerhsv_to_tint(printerhsv);
	return tm_tint_to_printerrgb(tint);
}

TM_FUNCTION struct tm_printerhsv_t tm_lighthsv_to_printerhsv(struct tm_lighthsv_t lighthsv)
{
	struct tm_printerhsv_t printerhsv;
	printerhsv.h = lighthsv.h;
	printerhsv.s = lighthsv.s;
	printerhsv.v = 1.0f - lighthsv.v;
	return printerhsv;
}
TM_FUNCTION struct tm_printerrgb_t tm_lightrgb_to_printerrgb(struct tm_lightrgb_t lightrgb)
{
	struct tm_printerrgb_t printerrgb;
	printerrgb.r = 1.0f - lightrgb.r;
	printerrgb.g = 1.0f - lightrgb.g;
	printerrgb.b = 1.0f - lightrgb.b;
	return printerrgb;
}
TM_FUNCTION struct tm_lighthsv_t tm_printerhsv_to_lighthsv(struct tm_printerhsv_t printerhsv)
{
	struct tm_lighthsv_t lighthsv;
	lighthsv.h = printerhsv.h;
	lighthsv.s = printerhsv.s;
	lighthsv.v = 1.0f - printerhsv.v;
	return lighthsv;
}
TM_FUNCTION struct tm_lightrgb_t tm_printerrgb_to_lightrgb(struct tm_printerrgb_t printerrgb)
{
	struct tm_lightrgb_t lightrgb;
	lightrgb.r = 1.0f - printerrgb.r;
	lightrgb.g = 1.0f - printerrgb.g;
	lightrgb.b = 1.0f - printerrgb.b;
	return lightrgb;
}

#endif
