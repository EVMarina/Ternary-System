#ifndef TRIBOOL_H
#define TRIBOOL_H

#include <QVector>
#include <iostream>
#include "converter.h"

using namespace std;

class Tribool
{
public:
    Tribool();
    Tribool(bool value);
    Tribool(int value);

    void operator=(const Tribool& num);
    void operator=(const int num10);

    Tribool operator==(const Tribool& num);
    Tribool operator>(const Tribool& num);
    Tribool operator<(const Tribool& num);
    Tribool operator>=(const Tribool& num);
    Tribool operator<=(const Tribool& num);
    Tribool operator||(const Tribool& num);
    Tribool operator&&(const Tribool& num);

    friend ostream &operator<<(ostream & os, Tribool &tb);
    friend istream &operator>>(istream & is, Tribool &tb);

    bool to_bool();
private:
    enum{ T = -1, O, I};
private:
    int trit;
};

#endif // TRIBOOL_H
