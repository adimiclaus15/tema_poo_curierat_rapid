

#ifndef COMANDA_H_INCLUDED
#define COMANDA_H_INCLUDED

#include <bits/stdc++.h>
using namespace std;

class Comanda
{
protected:
    int id;
    double masa;
    bool rece;
    pair <double,double> start;
    pair <double,double> finish;
    double livrare;//secunda cand va fi livrat
    double preluare;//secunda cand a fost preluat
    int tip;
    bool taken;
public:
    Comanda()
    {
        id=0;
        masa=0;
        rece=0;
        start.first=0;
        start.second=0;
        finish.first=0;
        finish.second=0;
        livrare=0;
        preluare=0;
        tip=0;
        taken=0;
    }
    Comanda & operator = (const Comanda &ob)
    {
        if(this!=&ob)
        {
            id=ob.id;
            masa=ob.masa;
            rece=ob.rece;
            start.first=ob.start.first;
            start.second=ob.start.second;
            finish.first=ob.finish.first;
            finish.second=ob.finish.second;
            livrare=ob.livrare;
            preluare=ob.preluare;
            tip=ob.tip;
            taken=ob.taken;

        }
        return *this;
    }
    bool operator < (const Comanda & c) const
    {
        if(tip==c.tip)
        {
            return preluare>c.preluare;
        }
        else
        {
            return tip<c.tip;
        }
    }
    double getpreluare()
    {
        return preluare;
    }
    double getXstart()
    {
        return start.first;
    }
    double getYstart()
    {
        return start.second;
    }
    int getId()
    {
        return id;
    }
    friend istream & operator >> (istream &,Comanda &);
    friend ostream & operator << (ostream &,const Comanda &);
    friend class Vehicul;
};

istream & operator >> (istream &in,Comanda &ob)
{
    in>>ob.id>>ob.preluare>>ob.livrare>>ob.start.first>>ob.start.second>>ob.finish.first>>ob.finish.second>>ob.masa>>ob.rece>>ob.tip;
    return in;
}
ostream & operator << (ostream &out,const Comanda &ob)
{
    out<<ob.id<<" "<<ob.preluare<<" "<<ob.start.first<<" "<<ob.start.second<<" "<<ob.finish.first<<" "<<ob.finish.second<<" "<<ob.masa<<" "<<ob.rece<<" "<<ob.tip<<"\n";
    return out;
}
#endif // COMANDA_H_INCLUDED
