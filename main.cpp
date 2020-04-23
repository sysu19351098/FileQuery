#include <iostream>
#include <string>
#include <fstream>
#include "FileQuery.h"
#include "FileQuery.cpp"
#include "Shape.h"
#include "Shape.cpp"



using namespace std;

void TestTextQuery(const string filename)//TextQuery测试函数
{
    FileQuery file(filename);
    file.PrintSentencesOrdered();
    file.PrintSentencesFiltered("epoch,season");
    file.PrintWordCount();
    file.ReplaceWord("was","is");
}

void TestShape()//Shape测试函数
{
    Shape s(20.5);
    cout << "Shape-s's area =" << s.GetArea() << endl;
    Rectangle rec(4, 5);
    cout << "Rectangle-rec's lenth =" << rec.getlenth() << ",width =" << rec.getwidth() << ",area =" << rec.GetArea() << endl;
    Circle c(5);
    cout << "Circle-c's R =" << c.getr() << ",area=" << c.GetArea() << endl;
    Square a(5);
    cout << "Sqrare-a's lenth of side =" << a.getlenth ()<< ",area=" << a.GetArea() << endl;
}
int main()
{
    TestTextQuery("TwoCities.txt");
    TestShape();
    return 0;
}