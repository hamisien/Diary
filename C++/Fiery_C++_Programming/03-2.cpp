/*
    * Date: 2021.08.13.
    * Author: hamisien
    * Mission 03-2-1
*/ /*
#include <iostream>

using namespace std;

class Calculator
{
// private:
    int add, min, mul, div;
public:
    void Init(void);
    double Add(const double &A, const double &B);
    double Min(const double &A, const double &B);
    double Mul(const double &A, const double &B);
    double Div(const double &A, const double &B);
    void ShowOpCount(void);
};

int main(void)
{
    Calculator cal;
    cal.Init();
    cout<<"3.2 + 2.4 = "<<cal.Add(3.2, 2.4)<<endl;
    cout<<"3.5 / 1.7 = "<<cal.Div(3.5, 1.7)<<endl;
    cout<<"2.2 - 1.5 ="<<cal.Min(2.2, 1.5)<<endl;
    cout<<"4.9 / 1.2 ="<<cal.Div(4.9, 1.2)<<endl;
    cal.ShowOpCount();

    return 0;
}

void Calculator::Init(void)
{
    add = 0;
    min = 0;
    mul = 0;
    div = 0;
}

double Calculator::Add(const double &A, const double &B)
{
    add++;

    return A + B;
}

double Calculator::Min(const double &A, const double &B)
{
    min++;

    return A - B;
}

double Calculator::Mul(const double &A, const double &B)
{
    mul++;

    return A * B;
}

double Calculator::Div(const double &A, const double &B)
{
    div++;

    return A / B;
}

void Calculator::ShowOpCount(void)
{
    cout<<"덧셈: "<<add<<" 뺄셈: "<<min<<" 곱셈: "<<mul<<" 나눗셈: "<<div<<endl;
}
*/

/*
    * Date: 2021.08.13.
    * Author: hamisien
    * Mission 03-2-2
*/

#include <iostream>
#include <cstring>

using namespace std;

class Printer
{
private:
    char str[500];
public:
    void SetString(const char* p_str);
    void ShowString(void);
};

int main(void)
{
    Printer pnt;
    pnt.SetString("Hello world!");
    pnt.ShowString();

    pnt.SetString("I love C++");
    pnt.ShowString();

    return 0;
}

void Printer::SetString(const char* p_str)
{
    strcpy(str, p_str);
}

void Printer::ShowString(void)
{
    cout << str << endl;
}