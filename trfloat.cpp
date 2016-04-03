#include "trfloat.h"
#include <QDebug>


Trfloat::Trfloat()
{
    this->matissa.fill(O,72);
    this->exp=0;
}

Trfloat::Trfloat(float num10)
{
    QVector<int> tmpNum=Converter::convertFromFloat(num10).first;
    exp = Converter::convertFromFloat(num10).second;
    this->matissa.fill(O,72);
    if(tmpNum.size()<=72)
    {
        for(int i=71, j=tmpNum.size()-1;i>=0;i--,j--)
        {
            if(j<0) break;
            else this->matissa[i]=tmpNum[j];
        }
    }
    else
        throw "Out of size";
    //qDebug()<<this->exp;
}


Trfloat::Trfloat(const Trfloat& num)
{
    this->matissa.fill(O,72);
    this->matissa=num.matissa;
    this->exp=num.exp;
}


Trfloat Trfloat::operator +(const Trfloat& num)
{
    Trfloat resultTrfloat;
    Trfloat first = *this;
    Trfloat second = num;
    QVector<int> resultValue;

    if(this->exp > num.exp) first=first<<(first.exp - second.exp);
    else
        if(this->exp < num.exp) second=second<<(second.exp - first.exp);

    resultValue.fill(O,72);

    for(int i=71;i>0;i--)
    {
        if((resultValue[i]==O && second.matissa[i]==I && first.matissa[i]==I) ||
                (resultValue[i]==I && first.matissa[i]==I && second.matissa[i]==O) ||
                (resultValue[i]==I && first.matissa[i]==O && second.matissa[i]==I))
        {
            resultValue[i]=T;
            resultValue[i-1]=I;
        }
        else if((resultValue[i]==I && second.matissa[i]==I && first.matissa[i]==I))
        {
            resultValue[i]=O;
            resultValue[i-1]=I;
        }
        else if((resultValue[i]==O && second.matissa[i]==T && first.matissa[i]==T) ||
                (resultValue[i]==T && first.matissa[i]==T && second.matissa[i]==O) ||
                (resultValue[i]==T && first.matissa[i]==O && second.matissa[i]==T))
        {
            resultValue[i]=I;
            resultValue[i-1]=T;
        }
        else if((resultValue[i]==T && second.matissa[i]==T && first.matissa[i]==T))
        {
            resultValue[i]=O;
            resultValue[i-1]=T;
        }
        else
        {
            resultValue[i]=resultValue[i]+second.matissa[i]+first.matissa[i];
        }
    }
    if((second.matissa[0]==I && first.matissa[0]==I) || (second.matissa[0]==T && first.matissa[0]==T))
    {
        throw "Out of size!!! The result num is too big.";
        abort();
    }
    else
        resultValue[0]=second.matissa[0]+first.matissa[0];

    resultTrfloat.matissa=resultValue;
    resultTrfloat.exp=first.exp;
    return resultTrfloat;
}

Trfloat Trfloat::operator -()
{
    Trfloat resultTrfloat;
    //qDebug()<<this->matissa;

    resultTrfloat.matissa=this->matissa;
    resultTrfloat.exp=this->exp;

    for(int i=0;i<72;i++) resultTrfloat.matissa[i]*=-1;

    return resultTrfloat;

}

Trfloat Trfloat::operator -(const Trfloat& num)
{
    Trfloat resultTrfloat;
    Trfloat tmpNum = num;

    resultTrfloat.matissa=this->matissa;
    resultTrfloat.exp=this->exp;

    resultTrfloat=resultTrfloat+(-tmpNum);

    return resultTrfloat;

}

Trfloat Trfloat::operator *(const Trfloat& num)
{
    Trfloat resultTrfloat;
    Trfloat first = *this;
    Trfloat second = num;
    qDebug()<<this->matissa;
    qDebug()<<this->exp;
    qDebug()<<(num.matissa);
    qDebug()<<(num.exp);

    while(firstPosOfNum(first.matissa)+firstPosOfNum(second.matissa)<=72 && (first.exp<0 || second.exp<0))
    {
        if(first.exp<0)
        {
            first=first>>1;
            first.exp++;
        }
        else if(second.exp<0)
        {
            second=second>>1;
            second.exp++;
        }
    }
    if(firstPosOfNum(first.matissa)+firstPosOfNum(second.matissa)>72)
    {
        int count=0;
        for(int i=71;i>=firstPosOfNum(num.matissa);i--)
        {
            Trfloat tmpTrfloat;
            for(int j=71;j>=firstPosOfNum(this->matissa);j--)
            {
                tmpTrfloat.matissa[j]=num.matissa[i]*this->matissa[j];
            }
            tmpTrfloat=tmpTrfloat<<count;
            tmpTrfloat.exp=0;
            resultTrfloat=resultTrfloat+tmpTrfloat;
            count++;
        }
        resultTrfloat.exp=this->exp+num.exp;
    }
    else
        throw "Numbers are too big";
    return resultTrfloat;

}


Trfloat Trfloat::operator /(const Trfloat& num)
{
    Trfloat resultTrfloat;
    Trfloat delitel = *this;
    Trfloat delimoe = num;
    Trfloat num0;
    Trfloat tmpTrfloat;

//    qDebug()<<delimoe.exp;
//    qDebug()<<delitel.exp;

//    int fnDelimoe = firstPosOfNum(delimoe.matissa);
//    int fnDelitel = firstPosOfNum(delitel.matissa);
//    int raznica = getRaznica(delitel.exp,delimoe.exp,fnDelitel,fnDelimoe);
//    delimoe.exp-=raznica;
//    delitel.exp-=raznica;
    shiftNums(delitel, delimoe);
    tmpTrfloat.exp=delimoe.exp;
    num0.exp=tmpTrfloat.exp;

    int count(0);
    if(Tribool(delitel<num0).to_bool()) delitel=-delitel;
    if(Tribool(delimoe<num0).to_bool()) delimoe=-delimoe;
    for(int i=firstPosOfNum(delitel.matissa);i<72;i++)
    {
        tmpTrfloat=tmpTrfloat<<1;
        tmpTrfloat.matissa[71]=(delitel.matissa[i]);
        count++;
        if(Tribool(tmpTrfloat<delimoe && tmpTrfloat>=num0).to_bool() || (Tribool(-tmpTrfloat<delimoe && tmpTrfloat<num0).to_bool()))
        {
            if(i==71 && Tribool(tmpTrfloat<delimoe).to_bool())
            {
                for(int i(1);i<=count;i++)
                {
                    resultTrfloat=resultTrfloat<<1;
                }
            }
            continue;
        }
        else
        {
            for(int i(2);i<=count;i++)
            {
                resultTrfloat=resultTrfloat<<1;
                resultTrfloat.matissa[71]=O;
            }
            count=0;
            resultTrfloat=resultTrfloat<<1;
            tmpTrfloat=tmpTrfloat-delimoe;
            if(Tribool(tmpTrfloat>=num0).to_bool()) resultTrfloat.matissa[71]=I;
            else resultTrfloat.matissa[71]=T;
            if(Tribool(tmpTrfloat>=delimoe).to_bool()&& firstPosOfNum(tmpTrfloat.matissa)<=firstPosOfNum(delimoe.matissa))
            {
                Trfloat exTrfloat;
                if(Tribool(tmpTrfloat>num0).to_bool())
                {
                    tmpTrfloat=tmpTrfloat-delimoe;
                    if(Tribool(tmpTrfloat>=num0).to_bool()) exTrfloat.matissa[71]=I;
                    else exTrfloat.matissa[71]=T;
                }
                else
                {
                    tmpTrfloat=-tmpTrfloat;
                    tmpTrfloat=tmpTrfloat-delimoe;
                    if(Tribool(tmpTrfloat>num0).to_bool()) exTrfloat.matissa[71]=T;
                    else if(Tribool(tmpTrfloat==num0).to_bool()) exTrfloat.matissa[71]=I;
                    else exTrfloat.matissa[71]=I;
                }
                resultTrfloat=resultTrfloat+exTrfloat;
            }
        }
    }
    int n = firstPosOfNum(resultTrfloat.matissa);
    int tmp_exp=0;
    for(int i=0;i<n;i++)
    {
        tmpTrfloat=tmpTrfloat<<1;
        if(Tribool(tmpTrfloat<delimoe).to_bool()) continue;

        resultTrfloat=resultTrfloat<<1;
        tmpTrfloat=tmpTrfloat-delimoe;
        tmp_exp--;

        if(Tribool(tmpTrfloat>num0).to_bool()) resultTrfloat.matissa[71]=I;
        else if(Tribool(tmpTrfloat==num0).to_bool()) resultTrfloat.matissa[71]=I;
        else resultTrfloat.matissa[71]=T;
        if(Tribool(tmpTrfloat>=delimoe).to_bool()&& firstPosOfNum(tmpTrfloat.matissa)<=firstPosOfNum(delimoe.matissa))
        {
            Trfloat exTrfloat;
            if(Tribool(tmpTrfloat>num0).to_bool())
            {
                tmpTrfloat=tmpTrfloat-delimoe;
                if(Tribool(tmpTrfloat>num0).to_bool()) exTrfloat.matissa[71]=I;
                else if(Tribool(tmpTrfloat==num0).to_bool()) exTrfloat.matissa[71]=I;
                else exTrfloat.matissa[71]=T;
            }
            else
            {
                tmpTrfloat=-tmpTrfloat;
                tmpTrfloat=tmpTrfloat-delimoe;
                if(Tribool(tmpTrfloat>num0).to_bool()) exTrfloat.matissa[71]=T;
                else if(Tribool(tmpTrfloat==num0).to_bool()) exTrfloat.matissa[71]=I;
                else exTrfloat.matissa[71]=I;
            }
            resultTrfloat=resultTrfloat+exTrfloat;
        }
    }
    delitel=*this;
    delimoe = num;
    if(Tribool((delitel < num0 && delimoe>num0) || (delitel >= num0 && delimoe<num0)).to_bool() )
        resultTrfloat=-resultTrfloat;
    resultTrfloat.exp=tmp_exp;
    return resultTrfloat;

}


Trfloat Trfloat::operator <<(int count)
{
    Trfloat resultTrfloat;
    QVector<int> resultValue;
    resultValue.fill(O,72);
    for(int i=0;i<72-count;i++) resultValue[i]=this->matissa[i+count];
    resultTrfloat.matissa=resultValue;
    resultTrfloat.exp=this->exp;
    return resultTrfloat;
}

Trfloat Trfloat::operator >>(int count)
{
    Trfloat resultTrfloat;
    QVector<int> resultValue;
    resultValue.fill(O,72);
   // qDebug()<<"ATTENTION"<<count;
    for(int i=71;i>=0+count;i--) resultValue[i]=this->matissa[i-count];
    resultTrfloat.matissa=resultValue;
    resultTrfloat.exp=this->exp;
    return resultTrfloat;
}


Tribool Trfloat::operator ==(const Trfloat& num)
{
    //qDebug()<<(this->trits == num.trits);
    return (this->matissa == num.matissa && this->exp==num.exp);
}

Tribool Trfloat::operator >(const Trfloat& num)
{
    Trfloat first = *this;
    Trfloat second = num;
    shiftNums(first, second);
    for(int i=0;i<72;i++)
        if(first.matissa[i]==second.matissa[i]) continue;
        else return first.matissa[i]>second.matissa[i];

    return false;
}

Tribool Trfloat:: operator <(const Trfloat& num)
{
    Trfloat first = *this;
    Trfloat second = num;
    shiftNums(first, second);
    for(int i=0;i<72;i++)
        if(first.matissa[i]==second.matissa[i]) continue;
        else return first.matissa[i]<second.matissa[i];

    return false;
}

Tribool Trfloat:: operator >=(const Trfloat& num)
{
    Trfloat first = *this;
    Trfloat second = num;
    shiftNums(first, second);
    for(int i=0;i<72;i++)
        if(first.matissa[i]==second.matissa[i]) continue;
        else return first.matissa[i]>second.matissa[i];

    return true;
}

Tribool Trfloat::operator <=(const Trfloat& num)
{
    Trfloat first = *this;
    Trfloat second = num;
    shiftNums(first, second);
    for(int i=0;i<72;i++)
        if(first.matissa[i]==second.matissa[i]) continue;
        else return first.matissa[i]<second.matissa[i];

    return true;
}


istream &operator>>(istream & is, Trfloat &tb)
{
    float num10;
    is >> num10;
    tb=num10;
    return is;
}

ostream &operator<<(ostream & os, Trfloat &tb)
{
    os<<Converter::convertTo10Float(tb.matissa,tb.exp);
    return os;
}


int Trfloat::firstPosOfNum(QVector<int> longNum)
{
    for(int i=0;i<longNum.size();i++)
        if(longNum[i]!=O)
            return i;
    return longNum.size();
}

int Trfloat::getRaznica(int f_E, int s_E, int f_Pos, int s_Pos)
{
    int raznica;
    if(f_E > s_E)
    {
        if(-s_E>f_Pos && s_Pos>=f_Pos) raznica= f_Pos;
        else
            if(-s_E>s_Pos && s_Pos<=f_Pos) raznica= s_Pos;
            else raznica = -s_E;
    }
    else
        if(f_E < s_E)
        {
            if(-f_E>f_Pos && s_Pos>=f_Pos) raznica= f_Pos;
            else
                if(-f_E>s_Pos && s_Pos<=f_Pos) raznica= s_Pos;
                else raznica = -f_E;
        }
    return raznica;
}

int Trfloat::getShift(int delta, int f_Pos)
{
    int shift;
    if(delta>f_Pos) shift= f_Pos;
    else shift = delta;/*
    qDebug()<<"DELTA:"<<delta;
    qDebug()<<"F_POS:"<<f_Pos;
    qDebug()<<"SHIFT:"<<shift;*/
    return shift;
}

void Trfloat::shiftNums(Trfloat& first, Trfloat& second)
{
    if(first.exp > second.exp)
    {
        int shift = getShift(first.exp - second.exp,firstPosOfNum(first.matissa));
        first=first<<shift;
        first.exp-=shift;
        if(first.exp!=second.exp && shift<first.exp - second.exp)
        {
            second=second>>(first.exp - second.exp-shift);
            second.exp+=shift;
        }
    }
    else
        if(first.exp < second.exp)
        {
            int shift = getShift(second.exp - first.exp,firstPosOfNum(second.matissa));
            second=second<<shift;
            second.exp-=shift;
            if(first.exp!=second.exp && shift<second.exp - first.exp)
            {
                first=first>>(second.exp - first.exp-shift);
                first.exp+=shift;
            }
        }
}

