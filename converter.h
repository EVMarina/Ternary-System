#ifndef CONVERTER_H
#define CONVERTER_H

#include <QVector>
#include <math.h>

class Converter
{
public:
    Converter();

    static QVector<int> convert(int num10);
    static int convertTo10(QVector<int> num);
};

#endif // CONVERTER_H
