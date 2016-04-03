#ifndef TRINT_H
#define TRINT_H

#include <QVector>
#include "converter.h"
#include "tribool.h"

class Trint
{
public:
    Trint();
    Trint(int num10);
    Trint(const Trint& num);

    Trint operator+(const Trint& num);
    Trint operator-(const Trint& num);
    Trint operator-();
    Trint operator*(const Trint& num);
    Trint operator/(const Trint& num);
    Trint operator<<(int count);
    Trint operator>>(int count);

    Tribool operator ==(const Trint& num);
    Tribool operator >(const Trint& num);
    Tribool operator <(const Trint& num);
    Tribool operator >=(const Trint& num);
    Tribool operator <=(const Trint& num);

    friend ostream &operator<<(ostream & os, Trint &tb);
    friend istream &operator>>(istream & is, Trint &tb);
private:
    enum{ T = -1, O, I};
private:
    QVector<int> trits;
    int firstPosOfNum(QVector<int> longNum);
    int sum(QVector<int> num);
    Trint divideBy2(const Trint delitel);
};

#endif // TRINT_H
