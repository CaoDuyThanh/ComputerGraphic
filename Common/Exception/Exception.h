#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>
using namespace std;

class Exception{
public:
    string Message;

public:
    Exception();
    Exception(string message);
};


#endif