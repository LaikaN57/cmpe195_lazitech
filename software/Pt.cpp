#include "Pt.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;

Pt::Pt()
{
	x = 0;
	y = 0;
}

Pt::Pt(double a, double b)
{
	x = a;
	y = b;
}

Pt::Pt(const Pt& pts)
{
	(*this) = pts;
}

Pt::~Pt()
{

}

Pt& Pt::operator=(const Pt& pts)
{
	x = pts.x;
	y = pts.y;
	return *this;
}

Pt Pt::operator+(const Pt& pts)
{
	x = x + pts.x;
	y = y + pts.y;
    Pt pt(x, y);
    return pt;
};

Pt Pt::operator-(const Pt& pts)
{
	x = x - pts.x;
	y = y - pts.y;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator*(const Pt& pts)
{
	x = x * pts.x;
	y = y * pts.y;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator/(const Pt& pts)
{
	x = x / pts.x;
	y = y / pts.y;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator+=(const Pt& pts)
{
	x += pts.x;
	y += pts.y;
	return *this;
};

Pt Pt::operator-=(const Pt& pts)
{
	x -= pts.x;
	y -= pts.y;
	return *this;
};

Pt Pt::operator*=(const Pt& pts)
{
	x *= pts.x;
	y *= pts.y;
	return *this;
};

Pt Pt::operator/=(const Pt& pts)
{
	x /= pts.x;
	y /= pts.y;
	return *this;
};

Pt Pt::operator+(double num)
{
	x = x + num;
	y = y + num;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator-(double num)
{
	x = x - num;
	y = y - num;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator*(double num)
{
	x = x * num;
	y = y * num;
	Pt pt(x, y);
	return pt;
};

Pt Pt::operator/(double num)
{
	x = x / num;
	y = y / num;
	Pt pt(x, y);
	return pt;
};


Pt Pt::operator+=(double num)
{
	x += num;
	y += num;
	return *this;
};

Pt Pt::operator-=(double num)
{
	x -= num;
	y -= num;
	return *this;
};

Pt Pt::operator*=(double num)
{
	x *= num;
	y *= num;
	return *this;
};

Pt Pt::operator/=(double num)
{
	x /= num;
	y /= num;
	return *this;
};

std::ostream& operator<<(std::ostream& output, const Pt& pt)
{
	output << "x = " << pt.x << "  y = " << pt.y;
	return output;
}
