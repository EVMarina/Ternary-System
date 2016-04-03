#ifndef CONVERTER_H
#define CONVERTER_H

#include <QVector>
#include <QPair>
#include <math.h>
#include <cmath>

class Converter
{
public:
    Converter();

    static QVector<int> convert(int num10);
    static QPair<QVector<int>, int> convertFromFloat(double num10);
    static float convertTo10Float(QVector<int> num, int exp);
    static int convertTo10(QVector<int> num);
private:
    static float convertTo10Drob(QVector<int> num);
};

#endif // CONVERTER_H
