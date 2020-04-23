#include <iostream>
#include "Shape.h"

using namespace std;

Shape::Shape(double area)
{
    area_ = area;
}
Shape::Shape(Shape &s)
{
    area_ = s.area_;
}
Shape::~Shape()
{
}
double Shape::GetArea()//获取面积
{
    return area_;
}

Rectangle::Rectangle(double l, double w) : Shape(l * w), l_(l), w_(w)
{
}
Rectangle::Rectangle(const Rectangle &rec) : Shape(rec.l_ * rec.w_), l_(rec.l_),
                                             w_(rec.w_)
{
}
Rectangle::~Rectangle()
{
}
double Rectangle::getlenth()//获取长度
{
    return l_;
}
double Rectangle ::getwidth()//获取宽度
{
    return w_;
}

Circle::Circle(double r) : Shape(3.14 * r * r), r_(r)
{
}
Circle::Circle(const Circle &c) : Shape(3.14 * c.r_ * c.r_), r_(c.r_)
{
}
Circle::~Circle()
{
}
double Circle::getr()//获取半径
{
    return r_;
}

Square::Square(double a) : Rectangle(a, a), a_(a)
{
}
Square::Square(const Square &s) : Rectangle(s.a_, s.a_), a_(s.a_)
{
}
Square::~Square()
{
}
