#include "tryte.h"


Tryte::Tryte()
{
    for(int i=0;i<9;i++)
    {
        this->trit[i]=O;
    }
}

Tryte::Tryte(int trit[9])
{
    if( trit[0]<=I &&  trit[1]<=I && trit[2]<=I && trit[0]>=T && trit[1]>=T && trit[2]>=T)
    {
        for(int i=0;i<9;i++)
        {
            this->trit[i]=trit[i];
        }
    }
    else
        throw "Wrong value of trit";
}
