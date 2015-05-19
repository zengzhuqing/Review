#include <iostream>
using namespace std;
class Complex
{
    friend istream &read(Complex &c, istream &in);
//    friend Complex add(const Complex &a, const Complex &b);
    friend ostream &print(const Complex &a, ostream &out);
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
istream &read(Complex &c, istream &in);
Complex add(const Complex &a, const Complex &b);
ostream &print(const Complex &a);
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
istream &read(Complex &c, istream &in)
{
    in >> c.a >> c.b;

    return in;
}
Complex add(const Complex &a, const Complex &b)
{
    Complex sum = a;
    sum += b;
    //sum.a = a.a + b.a;
    //sum.b = b.a + b.b;

    return sum;
}
ostream &print(const Complex &c, ostream &out)
{
    out << c.a << " + " << c.b << 'i';
}
Complex add(const Complex &a, const Complex &b);
int main()
{

    return 0;
}
