#include "converter.h"
#include <QDebug>
Converter::Converter()
{
}

QVector<int> Converter::convert(int num10)
{
    QVector<int> tmpResult;
    QVector<int> result;
    int tmpNum;

    if(num10==1 || num10==-1)
    {
        result.push_back(num10);
        return result;
    }
    if(num10==-2)
    {
        result.push_back(-1);
        result.push_back(1);
        return result;
    }
    if(num10==2)
    {
        result.push_back(1);
        result.push_back(-1);
        return result;
    }

    if(num10>=0) tmpNum=num10;
    else tmpNum=-1*num10;

    int celoe = tmpNum/3;
    int i;
    for(i=0;celoe>0;i++)
    {
        int ostatok = tmpNum%3;
        tmpResult.push_back(ostatok);
        tmpNum = celoe;
        celoe = tmpNum/3;
    }
    tmpResult.push_back(tmpNum);
    i++;
    if(i>0 && tmpNum!=num10)
    {
        for(int j=0;j<i-1;j++)
        {
            if(tmpResult[j]==2)
            {
                tmpResult[j]=-1;
                tmpResult[j+1]+=1;
            }
            else if(tmpResult[j]==3)
            {
                tmpResult[j]=0;
                tmpResult[j+1]+=1;
            }
        }
        if(tmpResult[i-1]==2)
        {
            tmpResult[i-1]=-1;
            tmpResult.push_back(1);
            i++;
        }
        else if(tmpResult[i-1]==3)
        {
            tmpResult[i-1]=0;
            tmpResult.push_back(1);
            i++;
        }

        result.resize(i);

        if(num10>=0) for(int j=0;j<i;j++) result[j]=tmpResult[i-j-1];
        else for(int j=0;j<i;j++) result[j]=(-1)*tmpResult[i-j-1];

    }

    return result;
}

QPair<QVector<int>,int > Converter::convertFromFloat(double num10)
{
    QPair<QVector<int>,int > result;
    QVector<int> drob_tmp;
    QVector<int> drob_result;
    double abs_num10 = num10;
    if(num10<0) abs_num10=-num10;
    int exp;
    int matissa = abs_num10;
    float drob_orig = abs_num10-matissa;
    float drob = abs_num10-matissa;
    if (abs_num10==0)
    {
        result.first.fill(0,1);
        result.second=0;
        return result;
    }

    for(int i(0);i<36;i++)
    {
        int cel = drob*3;
        drob_tmp.push_back(cel);
        drob = drob*3-cel;
    }
    for(int i(35);i>0;i--)
    {
        if(drob_tmp[i]==2)
        {
            drob_tmp[i]=-1;
            drob_tmp[i-1]+=1;
        }
        if(drob_tmp[i]==3)
        {
            drob_tmp[i]=0;
            drob_tmp[i-1]+=1;
        }
    }
    if(drob_tmp[0]==2 || drob_tmp[0]==3)
    {
        drob_tmp.push_back(0);
        for(int i(36);i>0;i--)
            drob_tmp[i]=drob_tmp[i-1];
        drob_tmp.pop_back();
        if(drob_tmp[1]==2) drob_tmp[1]=-1;
        if(drob_tmp[1]==3) drob_tmp[1]=0;
        drob_tmp[0]=1;

    }

    for(int i(0);i<36;i++)
    {
        drob_result.push_back(drob_tmp[i]);
        if(convertTo10Drob(drob_result)==drob_orig)
            break;
    }
    exp=-drob_result.size();

    result.first=convert(matissa)+drob_result;
    if(num10<0) for(int i(0);i<result.first.size();i++) result.first[i]*=-1;
    //qDebug()<<result.first;
    result.second=exp;
    //qDebug()<<result.second;

    return result;
}


int Converter::convertTo10(QVector<int> num)
{
    int result=0;
    for (int i = 0; i < num.size(); ++i) {
        result=result+num[i]*pow(3,num.size()-i-1);
    }
    return result;
}

float Converter::convertTo10Float(QVector<int> num,int exp)
{
    float result;
    QVector<int> cel;
    QVector<int> drob;
    for (int i = 0; i < num.size()+exp; ++i)
    {
        cel.push_back(num[i]);
    }
    for (int i = num.size()+exp; i < num.size(); ++i)
    {
        drob.push_back(num[i]);
    }
    result= convertTo10(cel)+convertTo10Drob(drob);
    return result;
}

float Converter::convertTo10Drob(QVector<int> num)
{
    float result=0;
    for (int i = -1; i >= -num.size(); --i) {
        result=result+num[-i-1]*pow(3,i);
    }
    return result;
}


