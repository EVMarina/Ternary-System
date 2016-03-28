#include "tribool.h"

Tribool::Tribool()
{
    this->trit=O;
}

Tribool::Tribool(bool value)
{
    if(value==I)
        this->trit=value;
    else
        this->trit=T;
}


Tribool::Tribool(int value)
{
    QVector<int> tmpNum=Converter::convert(value);
    if(tmpNum.isEmpty()) this->trit=O;//this->trits.fill(U,9);
    else
        if(tmpNum[0]==I) this->trit=I;//this->trits.fill(T,9);
        else
            if(tmpNum[0]==T) this->trit=T;//this->trits.fill(F,9);
}

bool Tribool::to_bool()
{
    switch(this->trit)
    {
    case T:
        return false;
        break;
    case I:
        return true;
        break;
    case O:
        return false;
        break;
    }
}

void  Tribool::  operator=(const Tribool& num)
{
    this->trit=num.trit;
}

void  Tribool::  operator=(const int num10)
{
    QVector<int> tmpNum=Converter::convert(num10);
    if(tmpNum.isEmpty()) this->trit=O;//this->trits.fill(U,9);
    else
        if(tmpNum[0]==I) this->trit=I;//this->trits.fill(T,9);
        else
            if(tmpNum[0]==T) this->trit=T;//this->trits.fill(F,9);
}


Tribool  Tribool::  operator==(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=I;
            break;
        case I:
            result.trit=T;
            break;
        case O:
            result.trit=T;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=T;
                break;
            case I:
                result.trit=I;
                break;
            case O:
                result.trit=T;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=T;
                    break;
                case I:
                    result.trit=T;
                    break;
                case O:
                    result.trit=I;
                    break;
                }
            }
    return result;
}


Tribool  Tribool::  operator>(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=T;
            break;
        case I:
            result.trit=T;
            break;
        case O:
            result.trit=T;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=I;
                break;
            case I:
                result.trit=T;
                break;
            case O:
                result.trit=I;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=I;
                    break;
                case I:
                    result.trit=T;
                    break;
                case O:
                    result.trit=T;
                    break;
                }
            }
    return result;
}


Tribool  Tribool::  operator<(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=T;
            break;
        case I:
            result.trit=I;
            break;
        case O:
            result.trit=I;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=T;
                break;
            case I:
                result.trit=T;
                break;
            case O:
                result.trit=T;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=T;
                    break;
                case I:
                    result.trit=I;
                    break;
                case O:
                    result.trit=T;
                    break;
                }
            }
    return result;
}

Tribool  Tribool::  operator>=(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=I;
            break;
        case I:
            result.trit=T;
            break;
        case O:
            result.trit=T;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=I;
                break;
            case I:
                result.trit=I;
                break;
            case O:
                result.trit=I;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=I;
                    break;
                case I:
                    result.trit=T;
                    break;
                case O:
                    result.trit=I;
                    break;
                }
            }
    return result;
}

Tribool  Tribool::  operator<=(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=I;
            break;
        case I:
            result.trit=I;
            break;
        case O:
            result.trit=I;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=T;
                break;
            case I:
                result.trit=I;
                break;
            case O:
                result.trit=T;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=T;
                    break;
                case I:
                    result.trit=I;
                    break;
                case O:
                    result.trit=I;
                    break;
                }
            }
    return result;
}

Tribool  Tribool::  operator||(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=T;
            break;
        case I:
            result.trit=I;
            break;
        case O:
            result.trit=O;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=I;
                break;
            case I:
                result.trit=I;
                break;
            case O:
                result.trit=I;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=O;
                    break;
                case I:
                    result.trit=I;
                    break;
                case O:
                    result.trit=O;
                    break;
                }
            }
    return result;
}

Tribool  Tribool::  operator&&(const Tribool& num)
{
    Tribool result;
    if(this->trit==T)
    {
        switch(num.trit)
        {
        case T:
            result.trit=T;
            break;
        case I:
            result.trit=T;
            break;
        case O:
            result.trit=T;
            break;
        }
    }
    else
        if(this->trit==I)
        {
            switch(num.trit)
            {
            case T:
                result.trit=T;
                break;
            case I:
                result.trit=I;
                break;
            case O:
                result.trit=O;
                break;
            }
        }
    else
            if(this->trit==O)
            {
                switch(num.trit)
                {
                case T:
                    result.trit=T;
                    break;
                case I:
                    result.trit=O;
                    break;
                case O:
                    result.trit=O;
                    break;
                }
            }
    return result;
}


istream &operator>>(istream & is, Tribool &tb)
{
    int num10;
    is >> num10;
    tb=num10;
    return is;
}

ostream &operator<<(ostream & os, Tribool &tb)
{
    if(tb.trit==Tribool::T) os<<"FALSE"; else
        if(tb.trit==Tribool::I) os<<"TRUE"; else
            if(tb.trit==Tribool::O) os<<"UNKNOWN";
    return os;
}
