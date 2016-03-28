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


int Converter::convertTo10(QVector<int> num)
{
    int result=0;
    for (int i = 0; i < num.size(); ++i) {
        result=result+num[i]*pow(3,num.size()-i-1);
    }
    return result;
}


