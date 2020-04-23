#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
private:
    double area_;

public:
    Shape(double area);
    Shape(Shape &s);
    ~Shape();
    double GetArea();//获取面积
};

class Rectangle : public Shape
{
private:
    double l_;
    double w_;

public:
    Rectangle(double l, double w);
    Rectangle(const Rectangle &rec);
    ~Rectangle();
    double getlenth();//获取长度
    double getwidth();//获取宽度
};

class Circle : public Shape
{
private:
    double r_;

public:
    Circle(double r);
    Circle(const Circle &c);
    ~Circle();
    double getr();//获取半径
};

class Square : public Rectangle
{
private:
    double a_;

public:
    Square(double a);
    Square(const Square &s);
    ~Square();
};

#endif