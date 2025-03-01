#include <cmath>
#include "calc.h"

Calculator::Calculator(){};

double Calculator::add(double x, double y)
{
    return x + y;
}

double Calculator::subtract(double x, double y)
{
    return x - y;
}

double Calculator::multiply(double x, double y)
{
    return x * y;
}

double Calculator::divide(double x, double y)
{
    return x / y;
}

double Calculator::raisePower(double x, double exponent)
{
    return pow(x, exponent);
}

double Calculator::areaOfCircle(double radius)
{
    return ( M_PI * ( pow( radius, 2 ) ) );
}

