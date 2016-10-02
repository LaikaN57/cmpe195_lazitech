#include <iostream>
#include <vector>

#ifndef PT_H_
#define PT_H_

class Pt
 {
 public:
	Pt();
    Pt(double a, double b);
    Pt(const Pt& pts);
    ~Pt();

    Pt& operator=(const Pt& pts);
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

   const std::vector<Pt>& Pts(double pts);

   //outputting the result
   friend std::ostream& operator<<(std::ostream& output, const Pt& pts);

    double x;
    double y;

};

#endif /* PT_H_ */
