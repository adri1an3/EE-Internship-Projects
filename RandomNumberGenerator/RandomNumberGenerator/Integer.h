/*
Adrian Jimenez
Integer.h
Random Number Generator
03/15/2025
Description: Integer class encapsulation used to
hide private information from users
*/
#pragma once
#ifndef INTEGER
#define INTEGER

class Integer {
private:
    int value;

public:
    //Overloaded Constructor
    Integer(int val) : value(val) {}

    int getValue() const {
        return value;
    }
};


#endif