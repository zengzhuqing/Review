#include <iostream>
using namespace std;
class Complex
{
    friend Complex &read(Complex &c, istream &in);
//    friend Complex add(const Complex &a, const Complex &b);
    friend void print(const Complex &a);
    public:
        Complex();
        Complex(double a, double b);
        Complex(const Complex& c);
        Complex &operator=(const Complex &c);
        Complex &operator+=(const Complex &c);
        ~Complex();
    private:
        double a;
        double b;
};
Complex &read(Complex &c, istream &in);
Complex add(const Complex &a, const Complex &b);
void print(const Complex &a);
Complex::Complex()
{
    a = 0;
    b = 0;
}
Complex::Complex(double aa, double bb):a(aa), b(bb) 
{
}
Complex::Complex(const Complex &c):a(c.a), b(c.b)
{
}
Complex &Complex::operator=(const Complex &c)
{
    a = c.a;
    b = c.b;

    return *this;
}
Complex &Complex::operator+=(const Complex &c)
{
    a += c.a;
    b += c.b;

    return *this;
}
Complex::~Complex(){} 
Complex &read(Complex &c, istream &in)
{
    in >> c.a >> c.b;

    return c;
}
Complex add(const Complex &a, const Complex &b)
{
    Complex sum = a;
    sum += b;
    //sum.a = a.a + b.a;
    //sum.b = b.a + b.b;

    return sum;
}
void print(const Complex &c)
{
    cout << c.a << " + " << c.b << 'i';
}
Complex add(const Complex &a, const Complex &b);
void print(const Complex &a);
int main()
{

    return 0;
}
