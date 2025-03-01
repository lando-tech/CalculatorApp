#ifndef CALC_H
#define CALC_H

class Calculator 
{
    public:
        Calculator();
        double add(double x, double y);
        double subtract(double x, double y);
        double multiply(double x, double y);
        double divide(double x, double y);
        double raisePower(double x, double exponent);
        double areaOfCircle(double radius);
};

#endif
