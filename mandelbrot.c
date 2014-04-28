#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "gd.h"
#include "mandelbrot.h"

int main()
{
	// Width and height of image in pixels.
	int width = 800,
		height = 800;
	// X and Y span covered by image, in range -1,1
	double x_min = -0.21575105,
		   x_max = -0.21575103,
		   y_min = -0.21505100,
		   y_max = -0.21505098;

	gdImagePtr im = gdImageCreateTrueColor(width, height);

	int xi = 0, yi = 0;
	double x = x_min, y = y_min;
	double x_step = (x_max - x_min) / width,
		   y_step = (y_max - y_min) / height;

	for (xi = 0; xi < width; xi++)
	{
		for (yi = 0; yi < height; yi++)
		{
			double *mb_xy = xy_mb_scale(x, y);
			int iterations = mb_xy_iterations(*(mb_xy), *(mb_xy+1));
			free(mb_xy);

			int brightness = log((double) iterations) * 85.0;
			int color = gdImageColorAllocate(im, brightness, 255, 255);
			gdImageSetPixel(im, xi, yi, color);

			y += y_step;
		}

		x += x_step;
		y = y_min;
	}

	// Save image as PNG.
	FILE *pngout = fopen("mandelbrot.png", "wb");
	gdImagePng(im, pngout);
	fclose(pngout);
	gdImageDestroy(im);

	return 0;
}

double *xy_mb_scale(double x, double y)
{
	const double mb_x_min = -2.5,
				 mb_x_max =  1.0,
				 mb_y_min = -1.0,
				 mb_y_max =  1.0;

	double *mb_xy = malloc(sizeof(double) * 2);
	mb_xy[0] = (x + 1) / 2;
	mb_xy[0] = mb_xy[0] * (mb_x_max - mb_x_min) + mb_x_min;
	mb_xy[1] = (y + 1) / 2;
	mb_xy[1] = mb_xy[1] * (mb_y_max - mb_y_min) + mb_y_min;
	return mb_xy;
}

int mb_xy_iterations(double mb_x, double mb_y)
{
	double x = 0.0, y = 0.0;
	int iteration, max_iteration = 1000;

	for (iteration = 0; iteration < max_iteration; iteration++)
	{
		double xtemp = x*x - y*y + mb_x;
		y = 2*x*y + mb_y;
		x = xtemp;

		if (x*x + y*y >= 2*2) {
			//printf("%d %f\n", iteration, x*x + y*y);
			break;
		}
	}

	return iteration;
}
