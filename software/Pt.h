#include <iostream>
#include <vector>

#ifndef PT_H_
#define PT_H_


// Point class

typedef struct {
	uint32_t x;
	uint32_t y;
} point_t;

point_t * point_add(point_t * a, point_t * b) {
	point_t sum;

	sum.x = a->x + b->x;
	sum.y = a->y + b->y;

	return &sum;
}

class Pt
 {
 public:
	Pt();
    Pt(double a, double b);
    Pt(const Pt& input);
    ~Pt();

    Pt& operator=(const Pt& input);
    Pt operator+(const Pt& pts);
    Pt operator-(const Pt& pts);
    Pt operator*(const Pt& pts);
    Pt operator/(const Pt& pts);
 	Pt operator-=(const Pt& pts);
 	Pt operator+=(const Pt& pts);
 	Pt operator*=(const Pt& pts);
 	Pt operator/=(const Pt& pts);

 	Pt operator+(double num);
 	Pt operator-(double num);
 	Pt operator*(double num);
 	Pt operator/(double num);
 	Pt operator+=(double num);
 	Pt operator-=(double num);
 	Pt operator*=(double num);
 	Pt operator/=(double num);

   //const std::vector<Pt>& Pts(double pts);

   //outputting the result
   friend std::ostream& operator<<(std::ostream& output, const Pt& pts);

    double x;
    double y;
};

#endif /* PT_H_ */
