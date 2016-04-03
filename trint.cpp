#include "trint.h"
#include <QDebug>

Trint::Trint()
{
    this->trits.fill(O,36);
}

Trint::Trint(int num10)
{
    QVector<int> tmpNum=Converter::convert(num10);
    this->trits.fill(O,36);
    if(tmpNum.size()<=36)
    {
        for(int i=35, j=tmpNum.size()-1;i>=0;i--,j--)
        {
            if(j<0) break;
            else this->trits[i]=tmpNum[j];
        }
    }
    else
        throw "Out of size";
    qDebug()<<this->trits;
}


Trint::Trint(const Trint& num)
{
    this->trits.fill(O,36);
    this->trits=num.trits;
}

Trint Trint::operator +(const Trint& num)
{
    Trint resultTrint;
    QVector<int> resultValue;

    resultValue.fill(O,36);

    for(int i=35;i>0;i--)
    {
        if((resultValue[i]==O && num.trits[i]==I && this->trits[i]==I) ||
                (resultValue[i]==I && this->trits[i]==I && num.trits[i]==O) ||
                (resultValue[i]==I && this->trits[i]==O && num.trits[i]==I))
        {
            resultValue[i]=T;
            resultValue[i-1]=I;
        }
        else if((resultValue[i]==I && num.trits[i]==I && this->trits[i]==I))
        {
            resultValue[i]=O;
            resultValue[i-1]=I;
        }
        else if((resultValue[i]==O && num.trits[i]==T && this->trits[i]==T) ||
                (resultValue[i]==T && this->trits[i]==T && num.trits[i]==O) ||
                (resultValue[i]==T && this->trits[i]==O && num.trits[i]==T))
        {
            resultValue[i]=I;
            resultValue[i-1]=T;
        }
        else if((resultValue[i]==T && num.trits[i]==T && this->trits[i]==T))
        {
            resultValue[i]=O;
            resultValue[i-1]=T;
        }
        else
        {
            resultValue[i]=resultValue[i]+num.trits[i]+this->trits[i];
        }
    }
    if((num.trits[0]==I && this->trits[0]==I) || (num.trits[0]==T && this->trits[0]==T))
    {
        throw "Out of size!!! The result num is too big.";
        abort();
    }
    else
        resultValue[0]=num.trits[0]+this->trits[0];

    resultTrint.trits=resultValue;
    //qDebug()<<resultValue;
    return resultTrint;

}


Trint Trint::operator -(const Trint& num)
{
    Trint resultTrint;
    Trint tmpNum = num;

    resultTrint.trits=this->trits;

    //for(int i=0;i<36;i++) tmpNum.trits[i]*=-1;

    resultTrint=resultTrint+(-tmpNum);

    return resultTrint;

}

Trint Trint::operator -()
{
    Trint resultTrint;

    resultTrint.trits=this->trits;

    for(int i=0;i<36;i++) resultTrint.trits[i]*=-1;

    return resultTrint;

}

Trint Trint::operator *(const Trint& num)
{
    Trint resultTrint;

    if(72-firstPosOfNum(this->trits)-firstPosOfNum(num.trits)<36)
    {
        int count=0;
        for(int i=35;i>=firstPosOfNum(num.trits);i--)
        {
            Trint tmpTrint;
            tmpTrint.trits.fill(O,36);
            for(int j=35;j>=firstPosOfNum(this->trits);j--)
            {
                tmpTrint.trits[j]=num.trits[i]*this->trits[j];
            }
            tmpTrint=tmpTrint<<count;
            resultTrint=resultTrint+tmpTrint;
            count++;
        }
    }
    return resultTrint;

}


Trint Trint::operator /(const Trint& num)
{
    Trint resultTrint;
    Trint delitel = *this;
    Trint delimoe = num;
    Trint num0(0);
    Trint tmpTrint;

    //    int sum = sum(delitel);
    //    if(sum%2=0)
    //    {
    //        if(num.trits[34]==I && num.trits[35]==T) resultTrint=divideBy2(delitel);
    //        if(num.trits[34]==T && num.trits[35]==I) resultTrint=resultTrint-divideBy2(delitel);
    //    }

    int count(0);
    if(Tribool(delitel<num0).to_bool()) delitel=-delitel;
    if(Tribool(delimoe<num0).to_bool()) delimoe=-delimoe;
    for(int i=firstPosOfNum(delitel.trits);i<36;i++)
    {
        tmpTrint=tmpTrint<<1;
        tmpTrint.trits[35]=(delitel.trits[i]);
        count++;
        if(Tribool(tmpTrint<delimoe && tmpTrint>=num0).to_bool() || (Tribool(-tmpTrint<delimoe && tmpTrint<num0).to_bool()))
        {
            if(i==35 && Tribool(tmpTrint<delimoe).to_bool())
            {
                for(int i(1);i<=count;i++)
                {
                    resultTrint=resultTrint<<1;
                }
                qDebug()<<"***************************************************************";
                qDebug()<<"BEF_TMP: "<<tmpTrint.trits;
//                if( Tribool(tmpTrint<num0).to_bool()&& resultTrint.trits[35]==O)
//                            resultTrint.trits[35]=T;
                qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
                qDebug()<<"AFT_RES: "<<resultTrint.trits;
            }
            continue;
        }
        else
        {
            for(int i(2);i<=count;i++)
            {
                resultTrint=resultTrint<<1;
                resultTrint.trits[35]=O;
            }
            count=0;
            resultTrint=resultTrint<<1;
            tmpTrint=tmpTrint-delimoe;
            if(Tribool(tmpTrint>num0).to_bool()) resultTrint.trits[35]=I;
            else if(Tribool(tmpTrint==num0).to_bool()) resultTrint.trits[35]=I;
            else resultTrint.trits[35]=T;
            if(Tribool(tmpTrint>=delimoe).to_bool()&& firstPosOfNum(tmpTrint.trits)<=firstPosOfNum(delimoe.trits))
            {
                Trint exTrint;
                if(Tribool(tmpTrint>num0).to_bool())
                {/*
                    qDebug()<<"***************************************************************";
                    qDebug()<<"TMP: "<<tmpTrint.trits;
                    qDebug()<<"DEL: "<<delimoe.trits;*/
                    tmpTrint=tmpTrint-delimoe;
                    if(Tribool(tmpTrint>num0).to_bool()) exTrint.trits[35]=I;
                    else if(Tribool(tmpTrint==num0).to_bool()) exTrint.trits[35]=I;
                    else exTrint.trits[35]=T;
                }
                else
                {
                    tmpTrint=-tmpTrint;
                    tmpTrint=tmpTrint-delimoe;
                    if(Tribool(tmpTrint>num0).to_bool()) exTrint.trits[35]=T;
                    else if(Tribool(tmpTrint==num0).to_bool()) exTrint.trits[35]=I;
                    else exTrint.trits[35]=I;
                }
                resultTrint=resultTrint+exTrint;
            }

        }
    }
    delitel=*this;
    delimoe = num;
    if(Tribool((delitel < num0 && delimoe>num0) || (delitel >= num0 && delimoe<num0)).to_bool() )
        resultTrint=-resultTrint;
    return resultTrint;

}

Trint Trint::divideBy2(const Trint delitel)
{

    Trint resultTrint;
    //введем число 3*х, так как 3*х-2*х даст нам искомый результат
    Trint xMult3;
    //делитель представляем как 2*х, где х-искомое, и домножаем на -1
    Trint minus_xMult2;
    minus_xMult2=minus_xMult2-delitel;

    for(int i(35);i>=0;i--)
    {
        resultTrint=xMult3+minus_xMult2;
        if(i>0) xMult3.trits[i-1]=resultTrint.trits[i];
    }

    return resultTrint;
}

Trint Trint::operator <<(int count)
{
    Trint resultTrint;
    QVector<int> resultValue;

    resultValue.fill(O,36);
    for(int i=0;i<36-count;i++) resultValue[i]=this->trits[i+count];
    resultTrint.trits=resultValue;
    return resultTrint;
}

Trint Trint::operator >>(int count)
{
    Trint resultTrint;
    QVector<int> resultValue;

    resultValue.fill(O,36);
    for(int i=35;i>=0+count;i--) resultValue[i]=this->trits[i-count];
    resultTrint.trits=resultValue;
    return resultTrint;
}

Tribool Trint::operator ==(const Trint& num)
{
    //qDebug()<<(this->trits == num.trits);
    return this->trits == num.trits;
}

Tribool Trint::operator >(const Trint& num)
{
    for(int i=0;i<36;i++)
        if(this->trits[i]==num.trits[i]) continue;
        else return this->trits[i]>num.trits[i];

    return false;
}

Tribool Trint:: operator <(const Trint& num)
{
    for(int i=0;i<36;i++)
        if(this->trits[i]==num.trits[i]) continue;
        else return this->trits[i]<num.trits[i];

    return false;
}

Tribool Trint:: operator >=(const Trint& num)
{
    for(int i=0;i<36;i++)
        if(this->trits[i]==num.trits[i]) continue;
        else return this->trits[i]>num.trits[i];

    return true;
}

Tribool Trint::operator <=(const Trint& num)
{
    for(int i=0;i<36;i++)
        if(this->trits[i]==num.trits[i]) continue;
        else return this->trits[i]<num.trits[i];

    return true;
}


int Trint::firstPosOfNum(QVector<int> longNum)
{
    for(int i=0;i<longNum.size();i++)
        if(longNum[i]!=O)
            return i;
    return longNum.size();
}

int Trint::sum(QVector<int> num)
{
    int sum=0;
    for(int i=0;i<num.size();i++)
        sum+=num[i];
    return sum;
}

istream &operator>>(istream & is, Trint &tb)
{
    int num10;
    is >> num10;
    tb=num10;
    return is;
}

ostream &operator<<(ostream & os, Trint &tb)
{
    os<<Converter::convertTo10(tb.trits);
    return os;
}
