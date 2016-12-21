#ifndef POINT_H
#define POINT_H

typedef struct {
	uint32_t x;
	uint32_t y;
} point_t;

typedef struct {
	long double x;
	long double y;
} fpoint_t;

point_t point_add(point_t a, point_t b);
point_t point_sub(point_t a, point_t b);

fpoint_t point_add(fpoint_t a, fpoint_t b);
fpoint_t point_sub(fpoint_t a, fpoint_t b);

#endif

