#include <cmath>
#include "calc.h"

Calculator::Calculator(){};

long double Calculator::add(long double x, long double y)
{
    return x + y;
}

long double Calculator::subtract(long double x, long double y)
{
    return x - y;
}

long double Calculator::multiply(long double x, long double y)
{
    return x * y;
}

long double Calculator::divide(long double x, long double y)
{
    return x / y;
}

long double Calculator::raisePower(long double x, long double exponent)
{
    return pow(x, exponent);
}

long double Calculator::areaOfCircle(long double radius)
{
    return ( M_PI * ( pow( radius, 2 ) ) );
}

