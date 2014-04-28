#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "gd.h"
#include "barnsley_fern.h"

float x = 0, y = 0;

int main()
{
	// Width and height of image in pixels.
	int width = 800,
		height = 800;

	gdImagePtr im = gdImageCreateTrueColor(width, height);

	// Shade image according to how frequently it was reached.
	/*int h, hues[width * height];
	for (h = 0; h < width * height; h++)
	{
		hues[h] = 0;
	}*/

	int i;
	for (i = 0; i < 100000000; i++)
	{
		render_frame();
		int sx = width * (x + 2.1820) / (2.1820 + 2.6558);
		int sy = height * (1 - y / 9.9983);

		// Shade image according to how frequently it was reached.
		//if (hues[sy * width + sx] < 255 - 19) hues[sy * width + sx] += 20;
		//int color = gdImageColorAllocate(im, hues[sy * width + sx], hues[sy * width + sx], hues[sy * width + sx]);

		int color = gdImageColorAllocate(im, 255, 255, 255);
		gdImageSetPixel(im, sx, sy, color);
	}

	// Save image as PNG.
	FILE *pngout = fopen("barnsley_fern.png", "wb");
	gdImagePng(im, pngout);
	fclose(pngout);
	gdImageDestroy(im);

	return 0;
}

void render_frame()
{
	int r = rand() % 100;
	if (r == 0)
	{
		x = 0.00;
		y = 0.16 * y;
	}
	else if (r <= 85)
	{
		x =  0.85 * x + 0.04 * y;
		y = -0.04 * x + 0.85 * y + 1.6;
	}
	else if (r == 92)
	{
		x = 0.20 * x - 0.26 * y;
		y = 0.23 * x + 0.22 * y + 1.6;
	}
	else if (r == 99)
	{
		x = -0.15 * x + 0.28 * y;
		y =  0.26 * x + 0.24 * y + 0.44;
	}
}
