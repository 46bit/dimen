#include "gd.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include "chelonian.h"

#define PI 3.14159265359

// -lgd -lpng -lz -ljpeg -lfreetype -lm

int main()
{
	// Current position and direction plus previous positions.
	float pos_dir[3] = {0, 0, 0};
	float pos_bounds[4] = {0, 0, 0, 0};
	int poses_length = 100, poses_index = 0;
	float *poses = malloc(sizeof(float) * poses_length);

	// Run commands from stdin.
	char command_buffer[20];
	while (fgets(command_buffer, 20, stdin))
	{
		// Run command.
		float old_pos[2] = {pos_dir[0], pos_dir[1]};
		cl_run_command(pos_dir, command_buffer);

		// Save new position.
		poses[poses_index++] = pos_dir[0];
		poses[poses_index++] = pos_dir[1];

		if (pos_dir[0] < pos_bounds[0]) pos_bounds[0] = pos_dir[0];
		if (pos_dir[0] > pos_bounds[1]) pos_bounds[1] = pos_dir[0];
		if (pos_dir[1] < pos_bounds[2]) pos_bounds[2] = pos_dir[1];
		if (pos_dir[1] > pos_bounds[3]) pos_bounds[3] = pos_dir[1];

		// Ensure enough position space.
		if (poses_index == poses_length) {
			// If we have no position space left, alloc double
			poses_length = poses_length << 1;
			float *newposes = malloc(sizeof(float)*poses_length);

			// Copy over existing positions
			int newposes_index;
			for (newposes_index = 0; newposes_index < poses_index; newposes_index++) {
				newposes[newposes_index] = poses[newposes_index];
			}

			// Free old positions, replace with new ones
			free(poses);
			poses = newposes;
		}
	}

	// Create image.
	int width = pos_bounds[1] - pos_bounds[0];
	int height = pos_bounds[3] - pos_bounds[2];

	float scale = (width > height) ? width : height;
	scale = 10000 / scale;

	int x_offset = (pos_bounds[0] + (width>>1)) * scale;
	int y_offset = (pos_bounds[2] + (height>>1)) * scale;

	printf("%i %f %i %f %f %i %i\n", width, width*scale, height, height*scale, scale, x_offset, y_offset);

	gdImagePtr im = gdImageCreateTrueColor(width * scale, height * scale);
	int white = gdImageColorAllocate(im, 255, 255, 255);

	// Render lines from positions.
	int poses_drawindex;
	for (poses_drawindex = 0; poses_drawindex < poses_index - 2; poses_drawindex += 2)
	{
		gdImageLine(
			im,
			-round(scale * poses[poses_drawindex+0] + x_offset),
			-round(scale * poses[poses_drawindex+1] + y_offset),
			-round(scale * poses[poses_drawindex+2] + x_offset),
			-round(scale * poses[poses_drawindex+3] + y_offset),
			white
		);
		/*printf(
			"%f,%f -> %f,%f\n",
			scale * poses[poses_drawindex+0] + x_offset,
			scale * poses[poses_drawindex+1] + y_offset,
			scale * poses[poses_drawindex+2] + x_offset,
			scale * poses[poses_drawindex+3] + y_offset
		);*/
	}

	// Save image as PNG.
	FILE *pngout = fopen("chelonian.png", "wb");
	gdImagePng(im, pngout);
	fclose(pngout);
	gdImageDestroy(im);

	return 0;
}

void cl_run_command(float *pos_dir, char *command_buffer)
{
	char command_code[3] = {command_buffer[0], command_buffer[1], 0};

	if (strcmp(command_code, "RT") == 0) {
		int arg = string_int(command_buffer+3, 18);
		cl_rt(pos_dir, &arg);
	} else if (strcmp(command_code, "LT") == 0) {
		int arg = string_int(command_buffer+3, 18);
		cl_lt(pos_dir, &arg);
	} else if (strcmp(command_code, "FD") == 0) {
		int arg = string_int(command_buffer+3, 18);
		cl_fd(pos_dir, &arg);
	} else {
		printf("UNRECOGNISED COMMAND: %s\n", command_buffer);
	}
}

void cl_rt(float *pos_dir, int *args)
{
	pos_dir[2] += PI * (float) args[0] / 180;
}

void cl_lt(float *pos_dir, int *args)
{
	pos_dir[2] -= PI * (float) args[0] / 180;
}

void cl_fd(float *pos_dir, int *args)
{
	pos_dir[0] += args[0] * sin(pos_dir[2]);
	pos_dir[1] += args[0] * cos(pos_dir[2]);
}

int string_int(char *str, int length)
{
	char *chr = str;
	int value = 0;
	for (chr = str; chr < str + length; chr++) {
		if (*chr >= '0' && *chr <= '9') {
			value = value * 10 + (*chr - '0');
		} else {
			break;
		}
	}
	return value;
}
