#ifndef CALC_H
#define CALC_H

class Calculator 
{
    public:
        Calculator();
        long double add(long double x, long double y);
        long double subtract(long double x, long double y);
        long double multiply(long double x, long double y);
        long double divide(long double x, long double y);
        long double raisePower(long double x, long double exponent);
        long double areaOfCircle(long double radius);
};

#endif
