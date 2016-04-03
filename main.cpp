#include <QDebug>
#include "trint.h"
#include "trfloat.h"
#include "tribool.h"

int main()
{
//    Trint a(26);
//    Trint b(26);
//    Trint c(0);
//    qDebug()<<((a<=b)&& (a>b));

//    Tribool bol=1;
//    Tribool q=0;
//    bol=(bol&&q);
    //bol=17;
    //cout<<bol;

//    Trint tr1= 259;
//    Trint tr2 = -10;
//    tr1=tr1/tr2;
//    //tr2=tr1+tr2;
//    cout<<tr1<<" "<<tr2;

    //Converter::convertFromFloat(1.123);
    Trfloat f1(2400.0123);
    Trfloat f2(-1200.0123);
    f2=f2/f1;
   // f2=f2<<71;
    cout<<f2;
    return 0;
}
