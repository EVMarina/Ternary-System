#ifndef TRFLOAT_H
#define TRFLOAT_H

#include <QVector>
#include "converter.h"
#include "tribool.h"

class Trfloat
{
public:
    Trfloat();
    Trfloat(float num10);
    Trfloat(const Trfloat& num);

    Trfloat operator+(const Trfloat& num);
    Trfloat operator-(const Trfloat& num);
    Trfloat operator-();
    Trfloat operator*(const Trfloat& num);
    Trfloat operator/(const Trfloat& num);
    Trfloat operator<<(int count);
    Trfloat operator>>(int count);

    Tribool operator ==(const Trfloat& num);
    Tribool operator >(const Trfloat& num);
    Tribool operator <(const Trfloat& num);
    Tribool operator >=(const Trfloat& num);
    Tribool operator <=(const Trfloat& num);

    friend ostream &operator<<(ostream & os, Trfloat &tb);
    friend istream &operator>>(istream & is, Trfloat &tb);
private:
    enum{ T = -1, O, I};
private:
    QVector<int> matissa;
    int exp;
    int firstPosOfNum(QVector<int> longNum);
    int getRaznica(int f_E, int s_E, int f_Pos, int s_Pos);
    int getShift(int delta, int f_Pos);
    void shiftNums(Trfloat& first, Trfloat& second);
};

#endif // TRFLOAT_H
