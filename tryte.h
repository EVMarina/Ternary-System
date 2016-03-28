#ifndef TRYTE_H
#define TRYTE_H

#include "converter.h"

class Tryte
{
public:
    Tryte(int trit[9]);
    Tryte();
private:
    enum{ T = -1, O, I};
private:
    int trit[9];

};

#endif // TRYTE_H
