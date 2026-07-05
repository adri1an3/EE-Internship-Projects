/*
Adrian Jimenez
Double.h
Random Number Generator
03/15/2025
Description: Double class encapsulation used to
hide private information from users
*/
#pragma once
#ifndef DOUBLE
#define DOUBLE

class Double {
private:
    double value;

public:
    //Overloaded Constructor
    Double(double val) : value(val) {}

    double getValue() const {
        return value;
    }

};


#endif